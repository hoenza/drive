#ifndef ELEMENT_DEFIENE_
#define ELEMENT_DEFIENE_
#include <string>
#include <vector>
#include <map>
#include "ErrorException.hpp"
#include "Permission.hpp"

enum Type { _FOLDER_, _FILE_ };

class Element {
   public:
   Element(std::string fatherPath, std::string _name, User* owner = NULL, Group* group = NULL);
   Element(std::string fatherPath, std::string _name, Permission* _permission);   
   Element() {}
   virtual ~Element();
   std::string getName() {return name; }
   std::string getPath() {return path; }
   Permission* getPermission() {return permission; }
   virtual Type getType() = 0;
   virtual std::string getDetails() = 0;
   
   virtual void addElement(Element* newElement) = 0;
   virtual Element* goDir(std::string direction) = 0;
   virtual std::string download() = 0;
   virtual void addDirectory(Permission* permission, std::string directoryName) = 0;
   virtual void removeElement(std::string name) = 0;
   virtual void setPermission(Permission* permission) = 0;
   virtual void changeOwner(User* user) = 0;
   virtual void changeGroup(Group* group) = 0;
   virtual Element* clone() = 0;
   virtual std::vector<std::string> listNameElement() = 0;
   virtual std::vector<std::string> listPathElement() = 0;
   virtual void replaceElement(std::string name, Element* newElement) = 0;
   virtual bool hasReadPermission(std::string username) {return permission->hasReadPermission(username);
      std::cout<< "ok"<<std::endl; }
   virtual bool hasWritePermission(std::string username) {return permission->hasWritePermission(username); }
   void info();
   protected:
   std::string name;
   std::string path;
   Permission* permission;
};

#endif