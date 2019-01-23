#ifndef GROUP_DEFINE_
#define GROUP_DEFINE_
#include <string>
#include <vector>
#include "User.hpp"
#include "ErrorException.hpp"
class Group {
   public:
   Group(std::string _name, User* founder);
   std::string getName() {return name; }
   bool isMember(std::string name);
   void addMember(User* user);
   private:
   std::string name;
   std::vector<User*> members;

   User* findMember(User* user);

};

#endif