#include "File.hpp"
#include <iostream>
using namespace std;

File::~File() {
   data.clear();
}

void File::setData(std::vector<char> _data) {
   data.clear();
   for(int i=0; i<_data.size(); i++)
      data.push_back(_data[i]);
}

void File::download(string outputName) {
   ofstream outFile;
   outFile.open(outputName);
   for(int i=0; i<data.size(); i++)
      outFile<< data[i];
   outFile.close();
}

int File::getStorage() {
   return data.size();
}

void File::changeMode(std::vector<std::string> changeModeData) {
   string target = changeModeData[0];
   string changeDirection = changeModeData[1];
   string changeFeild = changeModeData[2];
   if(target == USER_SIGN) {
      if(changeDirection == PLUS_SIGN)
         permission->plusUser(changeFeild);
      else
         permission->minusUser(changeFeild);
   }
   else {
      if(changeDirection == PLUS_SIGN)
         permission->plusGroup(changeFeild);
      else
         permission->minusGroup(changeFeild);
   }
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