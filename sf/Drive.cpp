#include "Drive.hpp"

using namespace std;

Drive::Drive() {
   User* rootUser = new User(ROOT_NAME, ROOT_PASSWORD, Admin);
   users.push_back(rootUser);
   Group* rootGroup = new Group(ROOT_NAME, rootUser);
   groups.push_back(rootGroup);
   Folder* rootFolder = new Folder("", "", rootUser, rootGroup);
   rootPath = rootFolder;


   User* newUser1 = new User("user1", "123");
   users.push_back(newUser1);

   Folder* newFolder1 = new Folder("", "user1", newUser1, NULL);
   rootPath->addElement(newFolder1);

   Folder* nF = new Folder(newFolder1->getPath(), "one", newUser1, NULL);
   newFolder1->addElement(nF);

   Folder* nF1 = new Folder(newFolder1->getPath(), "two", newUser1, NULL);
   newFolder1->addElement(nF1);

   Folder* nF2 = new Folder(newFolder1->getPath(), "three", newUser1, NULL);
   newFolder1->addElement(nF2);

   User* newUser2 = new User("user2", "123");
   users.push_back(newUser2);

   Folder* newFolder2 = new Folder("", "user2", newUser2, NULL);
   rootPath->addElement(newFolder2);

   Folder* nF3 = new Folder(newFolder2->getPath(), "one", newUser2, NULL);
   newFolder2->addElement(nF3);

   Folder* nF4 = new Folder(newFolder2->getPath(), "two", newUser2, NULL);
   newFolder2->addElement(nF4);

   Folder* nF5 = new Folder(newFolder2->getPath(), "three", newUser2, NULL);
   newFolder2->addElement(nF5);

   vector<char> data1 = readFile("File.hpp");
   vector<char> data2 = readFile("File.hpp");
   vector<char> data3 = readFile("Folder.hpp");
   vector<char> data4 = readFile("Folder.cpp");
   vector<char> data5 = readFile("Element.hpp");
   vector<char> data6 = readFile("Element.cpp");
   vector<char> data7 = readFile("main.cpp");

   // File* newFile1 = new File(nF->getPath(), "fileOne", newUser1, NULL);
   // nF->addElement(newFile1);

   // File* newFile2 = new File(nF1->getPath(), "fileTwo", newUser1, NULL);
   // nF1->addElement(newFile2);

   // File* newFile3 = new File(nF2->getPath(), "fileTwo", newUser1, NULL);
   // nF2->addElement(newFile3);

}

User* Drive::findUser(string name) {
   for(int i=0; i<users.size(); i++)
      if(users[i]->getName() == name)
         return users[i];
   
   return NULL;
}

User* Drive::findUserBySid(string sid) {
   map<User*, string>::iterator it;
   for(it = sidList.begin(); it != sidList.end(); it++)
      if(it->second == sid)
         return it->first;
   return NULL;
}

void Drive::validAddUser(string sid, string name) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_NOT_LOGGED_IN);
   if(findUser(name) != NULL)
      throw ErrorException(ERROR_DUPLICATE_USERNAME);
}

void Drive::addUser(string sid, string name, string pass) {
   validAddUser(sid, name);

   User* newUser = new User(name, pass);
   users.push_back(newUser);
   Folder* newFolder = new Folder("", name, newUser, NULL);
   rootPath->addElement(newFolder);
   newUser->setPath(newFolder->getPath());
}

bool Drive::duplicateSid(string sid) {
   map<User*, string>::iterator sidIt;
   for(sidIt = sidList.begin(); sidIt != sidList.end(); sidIt++)
      if(sidIt->second == sid)
         return true;
   return false;
}

string Drive::generateSid() {
   string ans;
   srand(time(NULL));
   while(ans.size() != SID_SIZE || duplicateSid(ans)) {
      ans = "";
      while(ans.size() < SID_SIZE) {
         int randNum = rand() % ASCII_SIZE + 1;
         if(randNum <= ((int)'z' - (int)'a' + 1))
            ans.push_back(randNum + (int)'a');
         else if(randNum <= 2*((int)'z' -(int)'a' + 1)) {
            randNum -= ((int)'z' - (int)'a' + 1);
            ans.push_back(randNum + (int)'A');
         }
         else {
            randNum -= 2*((int)'z' - (int)'a' + 1);
            ans.push_back(randNum + (int)'0');
         }
      }
   }
   return ans;
}

void Drive::validLogin(string name, string password) {
   User* user = findUser(name);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   else if(password != user->getPassword())
      throw ErrorException(ERROR_WRONG_PASSWORD);

   map<User*, string>::iterator sidIt = sidList.find(user);
   if(sidIt != sidList.end())
      sidList.erase(sidIt);
}

string Drive::login(string name, string password) {
   validLogin(name, password);

   string newSid = generateSid();
   User* user = findUser(name);
   sidList.insert(pair<User*, string>(user, newSid));
   user->setDefaultPath();
   return newSid;
}

void Drive::removeSid(string sid) {
   map<User*, string>::iterator it;
   for(it = sidList.begin(); it != sidList.end(); it++) {
      if(it->second == sid)
         sidList.erase(it);
         return;
   }
}

void Drive::logout(string sid) {
   if(sid.size() != SID_SIZE)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   
   user->setPath("/" + user->getName());
   removeSid(sid);
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
   Element* currentDir = rootPath;
   if(parsedDir.size() == 0)
      return currentDir;
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
   Element* currentDir = rootPath;
   if(parsedDir.size() == 0)
      return currentDir;
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

void Drive::validUpload(string sid, string name) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   Element* target = goDir(user->getPath());
   if(target == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   if(target->getType() != _FOLDER_)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
}

void Drive::upload(string sid, string name, string data) {
   validUpload(sid, name);
   User* user = findUserBySid(sid);
   Element* target = goDir(user->getPath());
   File* newFile = new File(user->getPath(), name, user, NULL);
   newFile->setData(data);
   target->addElement(newFile);
}


string Drive::download(string path) {
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   if(element->getType() != _FILE_)
      throw ErrorException(ERROR_PATH_IS_FOLDER);
   
   return element->download();
}

void Drive::addFolder(string sid, string name) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);

   Element* target(goDir(user->getPath()));
   if(target == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   target->addElement(new Folder(target->getPath(), name, user));
}

void Drive::copy(string sid, string path) {
   Element* target = goDir(path);
   if(target == NULL || goFatherDir(path) == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   if(user->getName() != ROOT_NAME && !target->hasReadPermission(user->getName()))
      throw ErrorException(ERROR_NOT_ENOUGH_PERMISSION);
   
   user->setCopySource(path);
}

void Drive::move(string sid, string path) {
   Element* target = goDir(path);
   if(target == NULL || goFatherDir(path) == NULL)
      throw ErrorException(ERROR_INVALID_PATH);

   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   if(user->getName() != ROOT_NAME && !target->hasReadPermission(user->getName()))
      throw ErrorException(ERROR_NOT_ENOUGH_PERMISSION);

   user->setMoveSource(path);
}

void Drive::paste(string sid, string targetPath) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   if(user->getSourceType() == NONE)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);
   if(goDir(targetPath) == NULL)
      throw ErrorException(ERROR_INVALID_DIST_PATH);
   
   string sourcePath = user->getSourcePath();
   if(goDir(sourcePath) == NULL || goFatherDir(sourcePath) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);

   Element* dist = goDir(targetPath);
   if(user->getName() != ROOT_NAME && !dist->hasWritePermission(user->getName()))
      throw ErrorException(ERROR_NOT_ENOUGH_PERMISSION);
   
   Element* element = goDir(sourcePath);
   Element* copyElement = element->clone();
   dist->addElement(copyElement);

   if(user->getSourceType() == MOVE) {
      Element* fatherSource = goFatherDir(sourcePath);
      fatherSource->removeElement(element->getName());
   }
   user->resetSourceDetail();
}

void Drive::remove(std::vector<std::string> removeData) {
   string path = removeData[0];
   Element* element = goDir(path);
   Element* father = goFatherDir(path);
   father->removeElement(element->getName());
}

void Drive::remove(string sid, string path) {
   cout<< "deleting path"<< path<< endl;
   Element* element = goDir(path);
   Element* father = goFatherDir(path);
   father->removeElement(element->getName());
}

void Drive::changeDirectory(string sid, string path) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   Element* destination = goDir(path);
   if(destination == NULL)
      throw ErrorException(ERROR_NO_SUCH_DIRECTORY);

   cout<< user->getName()<< endl;
   bool result = destination->hasReadPermission(user->getName());
   if(user->getName() != ROOT_NAME && !result) {
      throw ErrorException(ERROR_NOT_ENOUGH_PERMISSION);
   }
   user->setPath(path);
}

vector<string> Drive::listNameElement(string sid) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   Element* currentElement = goDir(user->getPath());
   if(currentElement == NULL)
      currentElement = rootPath;
   vector<string> ans = currentElement->listNameElement();
   if(goFatherDir(user->getPath()) != NULL)
      ans.insert(ans.begin(), "..");
   return ans;
}

vector<string> Drive::listPathElement(string sid) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   Element* currentElement = goDir(user->getPath());
   if(currentElement == NULL)
      currentElement = rootPath;
   vector<string> ans = currentElement->listPathElement();
   if(goFatherDir(user->getPath()) != NULL)
      ans.insert(ans.begin(), goFatherDir(user->getPath())->getPath());
   return ans;
}

string Drive::detail(string sid, string path) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);

   return element->getDetails();
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

void Drive::validPromoteData(string sid, string user) {
   User* subjectUser = findUserBySid(sid);
   if(subjectUser == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   if(subjectUser->getAuthority() == UsualUser)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   User* objectUser = findUser(user);
   if(objectUser == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
}

void Drive::promote(string sid, string user) {
   validPromoteData(sid, user);
   
   User* objectUser = findUser(user);
   Authority newAuth;
   if(objectUser->getAuthority() == UsualUser)
      newAuth = Admin;
   else
      newAuth = Supueruser;
   objectUser->setAuthority(newAuth);
}

void Drive::validDemoteData(string sid, string user) {
   User* subjectUser = findUserBySid(sid);
   if(subjectUser == NULL)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   if(subjectUser->getAuthority() == UsualUser)
      throw ErrorException(ERROR_WRONG_AUTHORITY);
   
   User* objectUser = findUser(user);
   if(objectUser == NULL)
      throw ErrorException(ERROR_USER_NOT_FOUND);
}

void Drive::demote(string sid, string user) {
   validDemoteData(sid, user);
   
   User* objectUser = findUser(user);
   Authority newAuth;
   if(objectUser->getAuthority() == Supueruser)
      newAuth = Admin;
   else
      newAuth = UsualUser;
   objectUser->setAuthority(newAuth);
}

bool Drive::isAdmin(string sid) {
   User* user = findUserBySid(sid);
   if(user == NULL) {
      return false;
   }
   else if(user->getAuthority() == UsualUser) {
      return false;
   }
   else
      return true;
}

bool Drive::isSuperuser(string sid) {
   User* user = findUserBySid(sid);
   if(user == NULL)
      return false;
   else if(user->getAuthority() == Supueruser)
      return true;
   else
      return false;
}

vector<string> Drive::getUserList() {
   vector<string> ans;
   for(int i=0; i<users.size(); i++)
      ans.push_back(users[i]->getName());
   return ans;
}

string Drive::getName(string path) {
   Element* element = goDir(path);
   if(element == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
   
   return element->getName();
}

Type Drive::getType(string path) {
   Element* element = goDir(path);
   // if(element == NULL)
   return element->getType();
}