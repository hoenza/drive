#include "Drive.hpp"

using namespace std;

Drive::Drive() {
   User* rootUser = new User(ROOT_NAME, ROOT_PASSWORD, Admin);
   users.push_back(rootUser);
   Group* rootGroup = new Group(ROOT_NAME, rootUser);
   groups.push_back(rootGroup);
   Folder* rootFolder = new Folder("", "", rootUser, rootGroup);
   rootPath = rootFolder;
   currentPath = rootFolder;
   loggedUser = NULL;
}

Group* Drive::findGroup(string name) {
   for(int i=0; i<groups.size(); i++)
      if(groups[i]->getName() == name)
         return groups[i];
   
   return NULL;
}

User* Drive::findUser(string name) {
   for(int i=0; i<users.size(); i++)
      if(users[i]->getName() == name)
         return users[i];
   
   return NULL;
}

void Drive::validAddUserData(vector<string> addUserData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOT_LOGGED_IN);
   else if(loggedUser->getAuthority() == UsualUser)
      throw ErrorException(ERROR_NOT_ENOUGH_AUTHORITY);
   
   if(addUserData.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string name = addUserData[0];
   if(findUser(name) != NULL)
      throw ErrorException(ERROR_DUPLICATE_USERNAME);
}

void Drive::addUser(vector<string> addUserData) {
   validAddUserData(addUserData);
   string name = addUserData[0];
   string password = addUserData[1];

   User* newUser = new User(name, password);
   users.push_back(newUser);

   Group* newGroup = new Group(name, newUser);
   groups.push_back(newGroup);

   Folder* newFolder = new Folder("", name, newUser, newGroup);
   rootPath->addElement(newFolder);
}

void Drive::validLoginData(vector<string> loginData) {
   if(loggedUser != NULL)
      throw ErrorException(ERROR_ALREADY_LOGGEDIN);

   if(loginData.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string name = loginData[0];
   string password = loginData[1];

   if(findUser(name) == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
   else {
      User* user = findUser(name);
      if(user->getPassword() != password)
         throw ErrorException(ERROR_WRONG_PASSWORD);
   }
}

void Drive::login(vector<string> loginData) {
   validLoginData(loginData);
   string name = loginData[0];
   User* user = findUser(name);
   loggedUser = user;
   currentPath = rootPath;
}

void Drive::logout() {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   loggedUser = NULL;
}

void Drive::validAddGroupData(vector<string> addGroupData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(addGroupData.size() != 1)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string name = addGroupData[0];
   if(findGroup(name) != NULL)
      throw ErrorException(ERROR_DUPLICATE_GROUPNAME);
}

void Drive::addGroup(vector<string> addGroupData) {
   validAddGroupData(addGroupData);
   string groupName = addGroupData[0];
   Group* newGroup = new Group(groupName, loggedUser);
   groups.push_back(newGroup);
}

void Drive::validAddToGroupData(vector<string> addToGroupData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(addToGroupData.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string groupName = addToGroupData[0];
   Group* group = findGroup(groupName);
   if(group == NULL)
      throw ErrorException(ERROR_GROUP_NOT_FOUND);
   
   string userName = addToGroupData[1];

   if(!group->isMember(loggedUser->getName()))
      throw ErrorException(ERROR_YOU_ARE_NOT_MEMBER);
   if(group->isMember(userName))
      throw ErrorException(ERROR_ALREADY_MEMBER_GROUP);
   
   User* user = findUser(userName);
   if(user == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
}

void Drive::addToGroup(vector<string> addToGroupData) {
   validAddToGroupData(addToGroupData);
   Group* group = findGroup(addToGroupData[0]);
   User* user = findUser(addToGroupData[1]);
   group->addMember(user);
}

vector<string> Drive::parsePath(string path) {
   vector<string> ans;
   while(path.size() != 0) {
      string subDir = "";
      while(path.size() > 0 && path[0] != SLASH) {
         subDir.push_back(path[0]);
         path.erase(path.begin());
      }
      if(path.size() > 0)
         path.erase(path.begin());
      if(subDir.size() != 0)
         ans.push_back(subDir);
   }
   return ans;
}

Element* Drive::goDir(string path) {
   vector<string> parsedDir = parsePath(path);
   Element* currentDir;
   if(path[0] == SLASH)
      currentDir = rootPath;
   else
      currentDir = currentPath;
   while(parsedDir.size() != 0) {
      Element* nextDir = currentDir->goDir(parsedDir[0]);
      parsedDir.erase(parsedDir.begin());
      if(nextDir == NULL)
         return NULL;
      currentDir = nextDir;
   }
   return currentDir;
}

Element* Drive::goFatherDir(string path) {
   vector<string> parsedDir = parsePath(path);
   if(parsedDir.size() == 0)
      return NULL;
   parsedDir.erase(parsedDir.end());
   Element* currentDir;
   if(path[0] == SLASH)
      currentDir = rootPath;
   else
      currentDir = currentPath;
   while(parsedDir.size() != 0) {
      Element* nextDir = currentDir->goDir(parsedDir[0]);
      parsedDir.erase(parsedDir.begin());
      if(nextDir == NULL)
         return NULL;
      currentDir = nextDir;
   }
   return currentDir;
}

vector<char> Drive::readFile(string fileName) {
   streampos size;
   char* memblock;
   ifstream inFile (fileName, ios::in | ios::binary | ios::ate);
   if(!inFile.is_open())
      throw ErrorException(ERROR_OPEN_FILE_FAILED);

   size = inFile.tellg();
   memblock = new char [size];
   inFile.seekg(0, ios::beg);
   inFile.read(memblock, size);
   inFile.close();

   vector<char>ans;
   for(int i=0; i<size; i++)
      ans.push_back(memblock[i]);
   
   delete[] memblock;
   return ans;
}

void Drive::validUploadData(vector<string> uploadData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(uploadData.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string path = uploadData[1];
   if(goFatherDir(path) == NULL)
      throw ErrorException(ERROR_NO_SUCH_DIRECTORY);
   if(goFatherDir(path)->getType() == _FILE_)
      throw ErrorException(ERROR_INVALID_PATH);
}

void Drive::upload(vector<string> uploadData) {
   validUploadData(uploadData);
   string file = uploadData[0];
   string path = uploadData[1];
   vector<char> data = readFile(file);

   vector<string> parsedPath = parsePath(path);
   string fileName = parsedPath[parsedPath.size() - 1];
   if(goDir(path) != NULL && goDir(path)->getType() == _FILE_) {
      Element* fatherDist = goFatherDir(path);
      Element* dist = goDir(path);
      File* newFile = new File(fatherDist->getPath(), fileName, fatherDist->getPermission());
      newFile->setData(data);
      fatherDist->replaceElement(dist->getName(), newFile);
      return;
   }
   if(goFatherDir(path) != NULL && goFatherDir(path)->getType() != _FILE_) {
      Element* fatherDist = goFatherDir(path);
      File* newFile = new File(fatherDist->getPath(), fileName, fatherDist->getPermission());
      newFile->setData(data);
      fatherDist->addElement(newFile);
   }
}

void Drive::validDownloadData(vector<string> downloadData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(downloadData.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);

   string path = downloadData[0];

   if(goDir(path) == NULL)
      throw ErrorException(ERROR_INVALID_PATH);

   Element* source = goDir(path);
   
   if(goDir(path)->getType() != _FILE_)
      throw ErrorException(ERROR_INVALID_PATH);
}

void Drive::download(vector<string> downloadData) {
   validDownloadData(downloadData);
   string path = downloadData[0];
   string outputName = downloadData[1];
   Element* source = goDir(path);
   source->download(outputName);
}

void Drive::validMakeDirectoryData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 1)
      throw ErrorException(ERROR_INVALID_DATA);
}

void Drive::makeDirectory(vector<string> makeDirectoryData) {
   validMakeDirectoryData(makeDirectoryData);
   
   string dirName = makeDirectoryData[0];
   currentPath->addDirectory(currentPath->getPermission(), dirName);
}

void Drive::validCopyData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);

   if(goDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
   if(goFatherDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
   if(goDir(data[1]) == NULL)
      throw ErrorException(ERROR_INVALID_DIST_PATH);
   if(goFatherDir(data[1]) == NULL)
      throw ErrorException(ERROR_INVALID_DIST_PATH);
}

void Drive::copy(std::vector<std::string> copyData) {
   validCopyData(copyData);

   string sourcePath = copyData[0];
   string distPath = copyData[1];
   Element* element = goDir(sourcePath);
   Element* copyElement = element->clone();
   Element* fatherDist = goFatherDir(distPath);
   Element* dist = goDir(distPath);
   fatherDist->replaceElement(dist->getName(), copyElement);
}

void Drive::validMoveData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);

   if(goDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
   if(goFatherDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
   if(goDir(data[1]) == NULL)
      throw ErrorException(ERROR_INVALID_DIST_PATH);
   if(goFatherDir(data[1]) == NULL)
      throw ErrorException(ERROR_INVALID_DIST_PATH);
}

void Drive::move(std::vector<std::string> moveData) {
   validMoveData(moveData);

   string sourcePath = moveData[0];
   string distPath = moveData[1];
   Element* element = goDir(sourcePath);
   Element* copyElement = element->clone();
   Element* fatherDist = goFatherDir(distPath);
   Element* dist = goDir(distPath);
   fatherDist->replaceElement(dist->getName(), copyElement);
   Element* fatherSource = goFatherDir(sourcePath);
   fatherSource->removeElement(element->getName());
}

void Drive::validRemoveData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 1)
      throw ErrorException(ERROR_INVALID_DATA);

   if(goDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   if(goFatherDir(data[0]) == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
}

void Drive::remove(std::vector<std::string> removeData) {
   string path = removeData[0];
   Element* element = goDir(path);
   Element* father = goFatherDir(path);
   father->removeElement(element->getName());
}

void Drive::validChangeDirectoryData(std::vector<std::string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 1)
      throw ErrorException(ERROR_INVALID_DATA);
   
}

void Drive::changeDirectory(vector<string> changeDirectoryData) {
   validChangeDirectoryData(changeDirectoryData);
   string path = changeDirectoryData[0];
   Element* destination = goDir(path);
   if(destination == NULL)
      ErrorException(ERROR_NO_SUCH_DIRECTORY);
   currentPath = destination;
}

void Drive::elemInfo(vector<string> elemInfoData) {
   if(elemInfoData.size() == 0) {
      if(currentPath == NULL)
         throw ErrorException(ERROR_NO_SUCH_DIRECTORY);
      currentPath->listElement();
      return;
   }
   else {
      string elemPath = elemInfoData[0];
      Element* element = goDir(elemPath);
      if(element == NULL)
         throw ErrorException(ERROR_INVALID_PATH);
      element->info();
   }

}

void Drive::validFilesizeData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
}

void Drive::fileSize(vector<string> sizeData) {
   string path = sizeData[0];
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   
   cout<< "path Storage: "<< element->getStorage()<< " Bytes"<< endl;
}

void Drive::changeMode(vector<string> changeModeData) {
   string path = changeModeData[3];
   changeModeData.erase(changeModeData.end() - 1);
   Element* element = goDir(path);
   element->changeMode(changeModeData);
}

void Drive::changeOwner(vector<string> changeOwnerData) {
   string username = changeOwnerData[0];
   User* user = findUser(username);
   if(user == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
   
   string path = changeOwnerData[1];
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   
   element->changeOwner(user);
}

void Drive::changeGroup(vector<string> changeGroupData) {
   string groupname = changeGroupData[0];
   Group* group = findGroup(groupname);
   if(group == NULL)
      throw ErrorException(ERROR_GROUP_NOT_FOUND);
   string path  = changeGroupData[1];
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   element->changeGroup(group);
}

void Drive::validPromoteData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string username = data[0];
   if(findUser(username) == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
   
   User* user = findUser(username);
   string auth = data[1];

   Authority newAuth;
   if(auth == ADMIN_SIGN)
      newAuth = Admin;
   else if(auth == SUPERUSER_SIGN)
      newAuth = Supueruser;
   else
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   if(newAuth == user->getAuthority())
      throw ErrorException(ERROR_USER_THIS_AUTHORITY);
   
   if(newAuth == Admin && user->getAuthority() == Supueruser)
      throw ErrorException(ERROR_WRONG_PROMOTE);
}

void Drive::promote(vector<string> promoteData) {
   validPromoteData(promoteData);
   string username = promoteData[0];
   User* user = findUser(username);
   string auth = promoteData[1];
   Authority newAuth;
   if(auth == ADMIN_SIGN)
      newAuth = Admin;
   else
      newAuth = Supueruser;
   
   user->setAuthority(newAuth);
}

void Drive::validDemoteData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);
   
   string username = data[0];
   if(findUser(username) == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
   
   User* user = findUser(username);
   string auth = data[1];

   Authority newAuth;
   if(auth == ADMIN_SIGN)
      newAuth = Admin;
   else if(auth == NORMAL_SIGN)
      newAuth = UsualUser;
   else
      throw ErrorException(ERROR_WRONG_AUTHORITY);

   if(newAuth == user->getAuthority())
      throw ErrorException(ERROR_USER_THIS_AUTHORITY);
   
   if(newAuth == Admin && user->getAuthority() == UsualUser)
      throw ErrorException(ERROR_WRONG_DEMOTE);
}

void Drive::demote(vector<string> demoteData) {
   validDemoteData(demoteData);
   string username = demoteData[0];
   User* user = findUser(username);
   string auth = demoteData[1];
   Authority newAuth;
   if(auth == ADMIN_SIGN)
      newAuth = Admin;
   else
      newAuth = Supueruser;
   
   user->setAuthority(newAuth);
}

void Drive::userlist() {
   if(loggedUser->getAuthority() == UsualUser)
      throw ErrorException(ERROR_NOT_ENOUGH_PERMISSION);
   
   cout<< "--- Users ---"<< endl;
   for(int i=0; i<users.size(); i++)
      cout<< users[i]->getName()<< endl;
   cout<< "--- EndList ---"<< endl;
}

void Drive::storage() {
   int storage = rootPath->getStorage();
   cout<< "Storage: "<< storage<< "bytes"<< endl;
}