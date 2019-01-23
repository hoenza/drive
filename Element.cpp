#include "Element.hpp"

using namespace std;

Element::Element(string fatherPath, string _name, User* owner, Group* group) {
   name = _name;
   path = fatherPath + SLASH + name;
   permission = new Permission(owner, group);
}

Element::Element(std::string fatherPath, std::string _name, Permission* _permission) {
   name = _name;
   path = fatherPath + SLASH + name;
   permission = _permission;
}

Element::~Element() {
   delete permission;
}

void Element::info() {
   if(this->getType() == _FILE_)
      cout<< "file ";
   else
      cout<< "dir ";
   permission->printPermissionUser();
   permission->printPermissionGroup();
   permission->printUser();
   permission->printGroup();
   cout<< path<< endl;
}