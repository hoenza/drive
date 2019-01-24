#ifndef _ERROREXCEPTION_DEFINE_
#define _ERROREXCEPTION_DEFINE_
#include <string>

#define ROOT "Root"
#define SUPERUSER "Superuser"
#define ADMIN "Admin"
#define USER "User"
#define ADMIN_SIGN "admin"
#define SUPERUSER_SIGN "superuser"
#define NORMAL_SIGN "normal"
#define GROUP_SIGN "group"
#define USER_SIGN "user"
#define MINUS_SIGN "-"
#define PLUS_SIGN "+"
#define READ_SIGN "read"
#define WRITE_SIGN "write"
#define READ_WRITE_SIGN "rw"

#define DIRECTORY "Directory"
#define FILE_SIGN "File"


#define ERROR_WRONG_COMMAND "Wrong command\n"
#define ERROR_INVALID_DATA "Entered data is not valid\n"
#define ERROR_DUPLICATE_USERNAME "Entered username already exists\n"
#define ERROR_NOT_LOGGED_IN "The user is not logged\n"
#define ERROR_NOT_ENOUGH_AUTHORITY "The user authority is not enough\n"
#define ERROR_USER_NOT_FOUND "Such user not found\n"
#define ERROR_WRONG_PASSWORD "Wrong password\n"
#define ERROR_ALREADY_LOGGEDIN "Someone is already logged in\n"
#define ERROR_NOONE_LOGGEDIN "No one is logged in\n"
#define ERROR_DUPLICATE_GROUPNAME "Entered group name already exists\n"
#define ERROR_GROUP_NOT_FOUND "Such group not found\n"
#define ERROR_YOU_ARE_NOT_MEMBER "You are not a member of this group\n"
#define ERROR_ALREADY_MEMBER_GROUP "The user already is a member of group\n"
#define ERROR_OPEN_FILE_FAILED "Opening file failed\n"
#define ERROR_INVALID_PATH "The path is not valid\n"
#define ERROR_FILE_SAME_NAME "Already there is a file with this name\n"
#define ERROR_ELEMENT_SAME_NAME "Already there is a element with such name\n"
#define ERROR_INVALID_SOURCE_PATH "The source path is not valid\n"
#define ERROR_INVALID_DESTINATION_PATH "The destination path is not valid\n"
#define ERROR_WRONG_AUTHORITY "Wrong authority\n"
#define ERROR_USER_THIS_AUTHORITY "The user already has this authority\n"
#define ERROR_WRONG_PROMOTE "You are not promoting\n"
#define ERROR_WRONG_DEMOTE "Yoa are not demoting\n"
#define ERROR_PATH_IS_FOLDER "The entered path is not a file"
#define ERROR_NOT_ENOUGH_PERMISSION "You do not have enough permission\n"
#define ERROR_NO_SUCH_DIRECTORY "There is not such directory\n"
#define ERROR_INVALID_SOURCE_PATH "The source path is not valid\n"
#define ERROR_INVALID_DIST_PATH "The dist path is not valid\n"


#define SLASH '/'

class ErrorException {
   public:
      ErrorException(std::string _error) :error(_error) {}
      std::string getError() const {return error; }
   private:
      std::string error;
};

#endif