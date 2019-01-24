#include <vector>
#include <string>
#include <iostream>
#include "Drive.hpp"
#include "ErrorException.hpp"

using namespace std;

#define ADD_USER "add_user"
#define LOGIN "login"
#define LOGOUT "logout"
#define ADD_GROUP "add_group"
#define ADD_TO_GROUP "add_to_group"
#define UPLOAD "upload"
#define DOWNLOAD "download"
#define MAKE_DIRECTORY "make_directory"
#define COPY "copy"
#define MOVE "move"
#define REMOVE "remove"
#define PRINT_DIRECTORY "print_directory"
#define CHANGE_DIRECTORY "change_directory"
#define ELEM_INFO "elem_info"
#define FILE_SIZE "file_size"
#define CHANGE_MODE "change_mode"
#define CHANGE_OWNER "change_owner"
#define CHANGE_GROUP "change_group"
#define PROMOTE "promote"
#define DEMOTE "demote"
#define USERLIST "userlist"
#define STORAGE "storage"

vector<string> parseCommand(string command) {
   vector<string> ans;
   string tmp;
   while(command.size() > 0) {
      if(command[0] == ' ') {
         if(tmp.size() > 0) {
            ans.push_back(tmp);
            tmp = "";
         }
      }
      else {
         tmp.push_back(command[0]);
      }
      command.erase(command.begin());
   }
   if(tmp.size() > 0)
      ans.push_back(tmp);
   return ans;
}

void handleCommand(vector<string> parsedCommand, Drive* drive) {
   if(parsedCommand.size() < 1)
      throw ErrorException(ERROR_WRONG_COMMAND);
   
   string mainCommand = parsedCommand[0];
   parsedCommand.erase(parsedCommand.begin());

   if(mainCommand == ADD_USER)
      drive->addUser(parsedCommand);
   else if(mainCommand == LOGIN)
      drive->login(parsedCommand);
   else if(mainCommand == LOGOUT)
      drive->logout();
   else if(mainCommand == ADD_GROUP)
      drive->addGroup(parsedCommand);
   else if(mainCommand == ADD_TO_GROUP)
      drive->addToGroup(parsedCommand);
   else if(mainCommand == UPLOAD)
      drive->upload(parsedCommand);
   else if(mainCommand == DOWNLOAD)
      drive->download(parsedCommand);
   else if(mainCommand == MAKE_DIRECTORY)
      drive->makeDirectory(parsedCommand);
   else if(mainCommand == COPY)
      drive->copy(parsedCommand);
   else if(mainCommand == MOVE)
      drive->move(parsedCommand);
   else if(mainCommand == REMOVE)
      drive->remove(parsedCommand);
   else if(mainCommand == PRINT_DIRECTORY)
      drive->printDirectory();
   else if(mainCommand == CHANGE_DIRECTORY)
      drive->changeDirectory(parsedCommand);
   else if(mainCommand == ELEM_INFO)
      drive->elemInfo(parsedCommand);
   else if(mainCommand == CHANGE_MODE)
      drive->changeMode(parsedCommand);
   else if(mainCommand == CHANGE_OWNER)
      drive->changeOwner(parsedCommand);
   else if(mainCommand == CHANGE_GROUP)
      drive->changeGroup(parsedCommand);
   else if(mainCommand == FILE_SIZE)
      drive->fileSize(parsedCommand);
   else if(mainCommand == PROMOTE)
      drive->promote(parsedCommand);
   else if(mainCommand == DEMOTE)
      drive->demote(parsedCommand);
   else if(mainCommand == USERLIST)
      drive->userlist();
   else if(mainCommand == STORAGE)
      drive->storage();
   else
      throw ErrorException(ERROR_WRONG_COMMAND);
}

int main() {
   string command;
   vector<string> parsedCommand;
   Drive* drive = new Drive();
   while(getline(cin, command)) {
      parsedCommand = parseCommand(command);
      try {
         handleCommand(parsedCommand, drive);
      }
      catch (ErrorException ex) {
         cout<< ex.getError();
      }
   }
   return 0;
}