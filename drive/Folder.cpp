#include "Folder.hpp"

using namespace std;

Folder::~Folder() {
   elements.clear();
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

int Folder::getStorage() {
   int ans = 0;
   for(int i=0; i<elements.size(); i++)
      ans += elements[i]->getStorage();
   return ans;
} 

void Folder::removeElement(std::string name) {
   for(int i=0; i<elements.size(); i++)
      if(elements[i]->getName() == name) {
         delete elements[i];
         elements.erase(elements.begin() + i);
         return;
      }
}

void Folder::changeMode(std::vector<std::string> changeModeData) {
   string target = changeModeData[0];
   string changeDirection = changeModeData[1];
   string changeFeild = changeModeData[2];
   if(target == USER_SIGN) {
      if(changeDirection == PLUS_SIGN)
         permission->plusUser(changeFeild);
      else
         permission->minusUser(changeFeild);
   }
   else {
      if(changeDirection == PLUS_SIGN)
         permission->plusGroup(changeFeild);
      else
         permission->minusGroup(changeFeild);
   }

   for(int i=0; i<elements.size(); i++)
      elements[i]->setPermission(permission);
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

void Folder::listElement() {
   cout<< "---- dir list----"<< endl;
   for(int i=0; i<elements.size(); i++)
      cout<< elements[i]->getName()<< endl;
   cout<< "---- end list----"<< endl;
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