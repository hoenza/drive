#ifndef FOLDER_DIFINE_
#define FOLDER_DIFINE_
#include "ErrorException.hpp"
#include "Element.hpp"
#include "File.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Folder :public Element {
   public:
   Folder(std::string fatherPath, std::string name, User* userOwner, Group* groupOwner = NULL)
      :Element(fatherPath, name, userOwner, groupOwner) {}
   Folder(std::string fatherPath, std::string name, Permission* permission)
      :Element(fatherPath, name, permission) {}
      
   Folder() {};
   Folder(Folder& fl);
   ~Folder();
   virtual void addElement(Element* newElement);
   virtual Element* goDir(std::string direction);
   virtual Type getType() {return _FOLDER_; }
   virtual void download(std::string outputName) {}
   virtual void addDirectory(Permission* permission, std::string directoryName);
   virtual int getStorage();
   virtual void removeElement(std::string name);
   void changeMode(std::vector<std::string> changeModeData);
   void setPermission(Permission* permission);
   virtual void changeOwner(User* user);
   virtual void changeGroup(Group* group);
   virtual Element* clone();
   virtual void listElement();
   virtual void replaceElement(std::string name, Element* newElement);
   private:
   std::vector<Element*> elements;

   Element* findElement(std::string name);
};

#endif