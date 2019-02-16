#ifndef FILE_DEFINE_
#define FILE_DEFINE_
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Element.hpp"

class File :public Element {
   public:
   File(std::string fatherPath, std::string name, User* owner, Group* group = NULL)
      :Element(fatherPath, name, owner, group) {}
   File(std::string fatherPath, std::string name, Permission* permission)
      :Element(fatherPath, name, permission) {}
   File() {}
   ~File();
   
   virtual std::string getDetails();
   virtual void addElement(Element* newElement) {}
   virtual Element* goDir(std::string direction) {}
   virtual Type getType() {return _FILE_; }
   void setData(std::string _data);
   virtual std::string download();
   virtual void addDirectory(Permission* permission, std::string directoryName) {}
   virtual void removeElement(std::string name) {}
   void changeMode(std::vector<std::string> changeModeData);
   void setPermission(Permission* permission);
   virtual void changeOwner(User* user) {permission->changeUser(user); }
   virtual void changeGroup(Group* group) {permission->changeGroup(group); }
   virtual Element* clone();
   virtual std::vector<std::string> listNameElement() {}
   virtual std::vector<std::string> listPathElement() {}
   virtual void replaceElement(std::string name, Element* newElement) {}
   private:
   std::vector<char> data;
};

#endif
