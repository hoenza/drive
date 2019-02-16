#include "User.hpp"

using namespace std;

User::User(string _name, string _password, Authority _authoirty) {
   name = _name;
   password = _password;
   currentPath = "/" + name;
   if(name == "root")
      currentPath = "/";
   authority = _authoirty;
   sourceDetail.first = NONE;
   sourceDetail.second = "";
}

void User::setCopySource(string path) {
   sourceDetail.first = COPY;
   sourceDetail.second = path;
}

void User::setMoveSource(string path) {
   sourceDetail.first = MOVE;
   sourceDetail.second = path;
}

void User::resetSourceDetail() {
   sourceDetail.first = NONE;
   sourceDetail.second = "";
}