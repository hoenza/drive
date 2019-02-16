#ifndef CORE_DEFINE_
#define CORE_DEFINE_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include "Element.hpp"
#include "User.hpp"
#include "Group.hpp"
#include "ErrorException.hpp"
#include "Folder.hpp"
#include "File.hpp"

#define ROOT_NAME "root"
#define ROOT_PASSWORD "root"
#define SID_SIZE 16
#define ASCII_SIZE (int)(2*( (int)'z' - (int) 'a' + 1) + (int)'9' - (int)'0' + 1)

class Drive {
   public:
   Drive();

   void addUser(std::string sid, std::string name, std::string pass);
   std::string login(std::string name, std::string password);
   void logout(std::string sid);
   void addGroup(std::vector<std::string> addGroupData);
   void addToGroup(std::vector<std::string> addToGroupData);
   void upload(std::string sid, std::string name, std::string data);
   std::string download(std::string path);
   void addFolder(std::string sid, std::string name);
   void copy(std::string sid, std::string path);
   void move(std::string sid, std::string path);
   void paste(std::string sid, std::string targetPath);
   void remove(std::vector<std::string> removeData);
   void remove(std::string sid, std::string path);
   void fileSize(std::vector<std::string> sizeData);
   void changeMode(std::vector<std::string> changeModeData);
   void changeOwner(std::vector<std::string> changeOwnerData);
   void changeGroup(std::vector<std::string> changeGroupData);
   void changeDirectory(std::string sid, std::string path);
   void elemInfo(std::vector<std::string> elemInfoData);
   std::vector<std::string> listNameElement(std::string sid);
   std::vector<std::string> listPathElement(std::string sid);
   std::string detail(std::string sid, std::string path);
   void promote(std::string sid, std::string user);
   void demote(std::string sid, std::string user);
   void userlist();
   void storage();
   bool isAdmin(std::string sid);
   bool isSuperuser(std::string sid);
   std::vector<std::string> getUserList();
   std::string getName(std::string path);
   Type getType(std::string path);
   private:
   Element* rootPath;
   std::vector<User*> users;
   std::vector<Group*> groups;
   std::map<User*, std::string> sidList;
   

   User* findUser(std::string name);
   User* findUserBySid(std::string sid);
   Group* findGroup(std::string name) {return NULL; }

   void validAddUser(std::string sid, std::string name);
   void validLogin(std::string name, std::string password);
   void validAddGroupData(std::vector<std::string> addGroupData);
   void validAddToGroupData(std::vector<std::string> addToGroupData);
   std::vector<std::string> parsePath(std::string path);
   Element* goDir(std::string path);
   Element* goFatherDir(std::string path);
   void validUpload(std::string sid, std::string name);
   std::vector<char> readFile(std::string fileName);
   void validDownloadData(std::vector<std::string> downloadData);
   void validMakeDirectoryData(std::vector<std::string> data);
   void validChangeDirectoryData(std::vector<std::string> data);
   void validPromoteData(std::string sid, std::string user);
   void validDemoteData(std::string sid, std::string user);
   void validFilesizeData(std::vector<std::string> sizeData);
   void validCopyData(std::vector<std::string> data);
   void validMoveData(std::vector<std::string> data);
   void validRemoveData(std::vector<std::string> data);
   std::string generateSid();
   bool duplicateSid(std::string sid);
   void removeSid(std::string sid);
};

#endif