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
   std::vector<Element*> getElements() {return elements; }
   virtual std::string getDetails();
   virtual void addElement(Element* newElement);
   virtual Element* goDir(std::string direction);
   virtual Type getType() {return _FOLDER_; }
   virtual std::string download() {}
   virtual void addDirectory(Permission* permission, std::string directoryName);
   virtual void removeElement(std::string name);
   void setPermission(Permission* permission);
   virtual void changeOwner(User* user);
   virtual void changeGroup(Group* group);
   virtual Element* clone();
   virtual std::vector<std::string> listNameElement();
   virtual std::vector<std::string> listPathElement();
   virtual void replaceElement(std::string name, Element* newElement);
   private:

   std::vector<Element*> elements;
   Element* findElement(std::string name);
};

#endif