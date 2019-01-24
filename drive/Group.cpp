#include "Group.hpp"

using namespace std;

Group::Group(std::string _name, User* founder) {
   name = _name;
   members.push_back(founder);
}

bool Group::isMember(string name) {
   for(int i=0; i<members.size(); i++)
      if(members[i]->getName() == name)
         return true;
   return false;
}

User* Group::findMember(User* user) {
   for(int i=0; i<members.size(); i++)
      if(members[i]->getName() == user->getName())
         return members[i];
   return NULL;
}

void Group::addMember(User* user) {
   if(findMember(user) != NULL)
      throw ErrorException(ERROR_ALREADY_MEMBER_GROUP);
   
   members.push_back(user);
}
