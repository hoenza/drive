#include "User.hpp"

using namespace std;

User::User(string _name, string _password, Authority _authoirty) {
   name = _name;
   password = _password;
   authority = _authoirty;
}