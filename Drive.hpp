#ifndef CORE_DEFINE_
#define CORE_DEFINE_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Element.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "ErrorException.hpp"
#include "Folder.hpp"
#include "File.hpp"

#define ROOT_NAME "root"
#define ROOT_PASSWORD "root"

class Drive {
   public:
   Drive();
   void addUser(std::vector<std::string> addUserData);
   void login(std::vector<std::string> loginData);
   void logout();
   void addGroup(std::vector<std::string> addGroupData);
   void addToGroup(std::vector<std::string> addToGroupData);
   void upload(std::vector<std::string> uploadData);
   void download(std::vector<std::string> downloadData);
   void makeDirectory(std::vector<std::string> makeDirectoryData);
   void copy(std::vector<std::string> copyData);
   void move(std::vector<std::string> moveData);
   void remove(std::vector<std::string> removeData);
   void fileSize(std::vector<std::string> sizeData);
   void changeMode(std::vector<std::string> changeModeData);
   void changeOwner(std::vector<std::string> changeOwnerData);
   void changeGroup(std::vector<std::string> changeGroupData);
   void printDirectory() {std::cout<< currentPath->getPath()<< std::endl; }
   void changeDirectory(std::vector<std::string> changeDirectoryData);
   void elemInfo(std::vector<std::string> elemInfoData);
   void promote(std::vector<std::string> promoteData);
   void demote(std::vector<std::string> demoteData);
   void userlist();
   void storage();

   private:
   Element* rootPath;
   std::vector<User*> users;
   std::vector<Group*> groups;
   User* loggedUser;
   Element* currentPath;

   User* findUser(std::string name);
   Group* findGroup(std::string name);

   void validAddUserData(std::vector<std::string> addUserData);
   void validLoginData(std::vector<std::string> loginData);
   void validAddGroupData(std::vector<std::string> addGroupData);
   void validAddToGroupData(std::vector<std::string> addToGroupData);
   std::vector<std::string> parsePath(std::string path);
   Element* goDir(std::string path);
   Element* goFatherDir(std::string path);
   void validUploadData(std::vector<std::string> uploadData);
   std::vector<char> readFile(std::string fileName);
   void validDownloadData(std::vector<std::string> downloadData);
   void validMakeDirectoryData(std::vector<std::string> data);
   void validChangeDirectoryData(std::vector<std::string> data);
   void validPromoteData(std::vector<std::string> data);
   void validDemoteData(std::vector<std::string> data);
   void validFilesizeData(std::vector<std::string> sizeData);
   void validCopyData(std::vector<std::string> data);
   void validMoveData(std::vector<std::string> data);
   void validRemoveData(std::vector<std::string> data);
};

#endif