#include "File.hpp"
#include <iostream>
using namespace std;

File::~File() {
   data.clear();
}

void File::setData(string _data) {
   data.clear();
   
   for(int i=0; i<_data.size(); i++)
      data.push_back(_data[i]);
}

string File::download() {
   string ans;
   for(int i=0; i<data.size(); i++)
      ans.push_back(data[i]);
   return ans;
}

void File::setPermission(Permission* permission) {
   this->permission = permission;
}

Element* File::clone() {
   File* ans = new File();
   ans->name = name;
   ans->path = path;
   ans->permission = permission;
   return ans;
}

string File::getDetails() {
   string ans;
   ans += "name = " + name + "\n";
   ans += "type = Folder\n";
   ans += "owner = " + permission->printUser() + "\n";
   ans += "owner permission = " + permission->printUserPermission() + "\n";
   if(permission->printGroup().size() > 0) {
      ans += "group = " + permission->printGroup() + "\n";
      ans += "group permission = " + permission->printGroupPermission() + "\n";
   }
   ans += "file volume = " + to_string(data.size()) + "Bytes\n";
   return ans;
}