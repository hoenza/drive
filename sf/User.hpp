#ifndef USER_DEFINE_
#define USER_DEFINE_
#include <string>
#include "ErrorException.hpp"
// #include "Element.hpp"
enum TransferType {COPY, MOVE, NONE};
enum Authority { UsualUser, Supueruser, Admin };
class User;
class User {
   public:
   User(std::string _name, std::string _password, Authority _authoirty = UsualUser);
   std::string getName() {return name; }
   std::string getPassword() {return password; }
   Authority getAuthority() {return authority; }
   void setAuthority(Authority auth) {authority = auth; }
   std::string getPath() {return currentPath; }
   void setPath(std::string path) {currentPath = path; }
   void setDefaultPath() {currentPath = "/" + name; }
   void setCopySource(std::string path);
   void setMoveSource(std::string path);
   void resetSourceDetail();
   TransferType getSourceType() {return sourceDetail.first; }
   std::string getSourcePath() {return sourceDetail.second; }
   private:
   std::string name;
   std::string password;
   std::string currentPath;
   Authority authority;
   std::pair<TransferType, std::string> sourceDetail;

};

#endif