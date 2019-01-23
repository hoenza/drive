#ifndef USER_DEFINE_
#define USER_DEFINE_
#include <string>
#include "ErrorException.hpp"

enum Authority { UsualUser, Supueruser, Admin };

class User {
   public:
   User(std::string _name, std::string _password, Authority _authoirty = UsualUser);
   std::string getName() {return name; }
   std::string getPassword() {return password; }
   Authority getAuthority() {return authority; }
   void setAuthority(Authority auth) {authority = auth; }
   
   private:
   std::string name;
   std::string password;
   Authority authority;
};

#endif