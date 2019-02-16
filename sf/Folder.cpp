#include "Folder.hpp"

using namespace std;

Folder::~Folder() {
   elements.clear();
}

string Folder::getDetails() {
   string ans;
   ans += "name = " + name + "\n";
   ans += "type = Folder\n";
   ans += "owner = " + permission->printUser() + "\n";
   ans += "owner permission = " + permission->printUserPermission() + "\n";
   if(permission->printGroup().size() > 0) {
      ans += "group = " + permission->printGroup() + "\n";
      ans += "group permission = " + permission->printGroupPermission() + "\n";
   }
   return ans;
}

Element* Folder::findElement(string name) {
   for(int i=0; i<elements.size(); i++)
      if(elements[i]->getName() == name)
         return elements[i];
   return NULL;
}

void Folder::addElement(Element* newElement) {
   if(findElement(newElement->getName()) != NULL)
      throw ErrorException(ERROR_ELEMENT_SAME_NAME);
   
   elements.push_back(newElement);
}

Element* Folder::goDir(std::string direction) {
   for(int i=0; i<elements.size(); i++)
      if(elements[i]->getName() == direction)
         return elements[i];
   
   return NULL;
}

void Folder::addDirectory(Permission* permission, string directoryName) {
   if(findElement(directoryName) != NULL)
      throw ErrorException(ERROR_ELEMENT_SAME_NAME);

   Folder* newFolder = new Folder(path, directoryName, permission);
   elements.push_back(newFolder);
}

void Folder::removeElement(std::string name) {
   for(int i=0; i<elements.size(); i++)
      if(elements[i]->getName() == name) {
         delete elements[i];
         elements.erase(elements.begin() + i);
         return;
      }
}

void Folder::setPermission(Permission* permission) {
   this->permission = permission;

   for(int i=0; i<elements.size(); i++)
      elements[i]->setPermission(permission);
}

void Folder::changeOwner(User* user) {
   permission->changeUser(user);
   for(int i=0; i<elements.size(); i++)
      elements[i]->setPermission(permission);
}
void Folder::changeGroup(Group* group) {
   permission->changeGroup(group);
   for(int i=0; i<elements.size(); i++)
      elements[i]->setPermission(permission);
}

Element* Folder::clone() {
   Folder* ans = new Folder();
   ans->name = name;
   ans->path = path;
   ans->permission = permission;
   for(int i=0; i<elements.size(); i++)
      ans->elements.push_back(elements[i]->clone());
   return ans;
}

vector<string> Folder::listNameElement() {
   vector<string> ans;
   for(int i=0; i<elements.size(); i++)
      ans.push_back(elements[i]->getName());
   return ans;
}

vector<string> Folder::listPathElement() {
   vector<string> ans;
   for(int i=0; i<elements.size(); i++)
      ans.push_back(elements[i]->getPath());
   return ans;
}

void Folder::replaceElement(std::string name, Element* newElement) {
   if(findElement(newElement->getName()) != NULL)
      throw ErrorException(ERROR_ELEMENT_SAME_NAME);

   for(int i=0; i<elements.size(); i++)
      if(elements[i]->getName() == name) {
         delete elements[i];
         elements[i] = newElement;
      }
}