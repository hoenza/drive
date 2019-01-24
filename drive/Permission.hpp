#ifndef PERMISSION_DEFINE_
#define PERMISSION_DEFINE_
#include <iostream>
#include "User.hpp"
#include "ErrorException.hpp"
#include "Permission.hpp"
#include "User.hpp"
#include "Group.hpp"

enum permission {Read, Write, RW, Null };
class Permission {
   public:
   Permission(User* user, Group* group = NULL);
   Permission() {};
   void plusUser(std::string type);
   void minusUser(std::string type);
   void plusGroup(std::string type);
   void minusGroup(std::string type);
   permission* operator=(Permission* permission);
   void changeUser(User* _user) {user.first = _user; }
   void changeGroup(Group* _group) {group.first = _group; }
   bool hasReadPermission(std::string username);
   bool hasWritePermission(std::string username);
   void printPermissionUser();
   void printPermissionGroup();
   void printUser() {std::cout<< user.first->getName()<< " "; }
   void printGroup() {std::cout<< group.first->getName()<< " "; }
   
   private:
   std::pair<User*, permission> user;
   std::pair<Group*, permission> group;
};


#endif