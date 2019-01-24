#include "Permission.hpp"

using namespace std;

Permission::Permission(User* user, Group* group) {
   this->user = pair<User*, permission>(user, RW);
   this->group = pair<Group*, permission>(group, RW);
}

void Permission::plusUser(string type) {
   if(user.second == RW)
      return;
   if(type == READ_WRITE_SIGN)
      user.second = RW;
   else if(type == READ_SIGN && user.second == Write)
      user.second = RW;
   else if(type == WRITE_SIGN && user.second == Read)
      user.second = RW;
   else if(type == READ_SIGN && user.second == Null)
      user.second = Read;
   else if(type == WRITE_SIGN && user.second == Null)
      user.second = Write;
}

void Permission::minusUser(string type) {
   if(user.second == Null)
      return;
   if(type == READ_WRITE_SIGN)
      user.second = Null;
   else if(type == READ_SIGN && user.second == Read)
      user.second = Null;
   else if(type == WRITE_SIGN && user.second == Write)
      user.second = Null;
   else if(type == READ_SIGN && user.second == RW)
      user.second = Write;
   else if(type == WRITE_SIGN && user.second == RW)
      user.second = Read;
}

void Permission::plusGroup(string type) {
   if(group.second == RW)
      return;
   if(type == READ_WRITE_SIGN)
      group.second = RW;
   else if(type == READ_SIGN && group.second == Write)
      group.second = RW;
   else if(type == WRITE_SIGN && group.second == Read)
      group.second = RW;
   else if(type == READ_SIGN && group.second == Null)
      group.second = Read;
   else if(type == WRITE_SIGN && group.second == Null)
      group.second = Write;
   
}

void Permission::minusGroup(string type) {
   if(group.second == Null)
      return;
   if(type == READ_WRITE_SIGN)
      group.second = Null;
   else if(type == READ_SIGN && group.second == Read)
      group.second = Null;
   else if(type == WRITE_SIGN && group.second == Write)
      group.second = Null;
   else if(type == READ_SIGN && group.second == RW)
      group.second = Write;
   else if(type == WRITE_SIGN && group.second == RW)
      group.second = Read;
}

permission* Permission::operator=(Permission* permission) {
   user.first = permission->user.first;
   user.second = permission->user.second;
   group.first = permission->group.first;
   group.second = permission->group.second;
}

bool Permission::hasReadPermission(std::string username) {
   if(user.first->getName() == username && (user.second == Read || user.second == RW))
      return true;
   Group* myGroup = group.first;
   if(myGroup->isMember(username) && (group.second == Read || group.second == RW))
      return true;
   return false;
}

bool Permission::hasWritePermission(std::string username) {
   if(user.first->getName() == username && (user.second == Write || user.second == RW)) {
      return true;
   }
   Group* myGroup = group.first;
   if(myGroup->isMember(username) && (group.second == Write || group.second == RW))
      return true;
   return false;
}

void Permission::printPermissionUser() {
   if(user.second == Read)
      cout<< "read,- ";
   else if(user.second == Write)
      cout<< "-,write ";
   else if(user.second == RW)
      cout<< "read,write ";
   else
      cout<< "-,- ";
}
void Permission::printPermissionGroup() {
   if(group.second == Read)
      cout<< "read,- ";
   else if(group.second == Write)
      cout<< "-,write ";
   else if(group.second == RW)
      cout<< "read-write ";
   else
      cout<< "-,- ";
}