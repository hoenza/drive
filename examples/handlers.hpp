#include "../server/server.hpp"
#include "../drive/Drive.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <map>

#define LINK "<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.6.3/css/all.css\" integrity=\"sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/\" crossorigin=\"anonymous\">"
#define PROMOTE_ICON "<i class=\"fas fa-chevron-circle-up\"></i>"
#define DEMOTE_ICON "<i class=\"fas fa-chevron-circle-down\"></i>"
#define COPY_ICON "<i class=\"fas fa-copy\"></i>"
#define MOVE_ICON "<i class=\"fas fa-cut\"></i>"
#define DETAIL_ICON "<i class=\"fas fa-info-circle\"></i>"
#define REMOVE_ICON "<i class=\"fas fa-folder-minus\"></i>"
#define DOWNLOAD_ICON "<i class=\"fas fa-download\"></i>"
#define PASTE_ICON "<i class=\"fas fa-paste\"></i>"
#define EXIT_ICON "<i class=\"fas fa-sign-out-alt\"></i>"
#define UPLOAD_ICON "<i class=\"fas fa-upload\"></i>"
#define ADD_USER_ICON "<i class=\"fas fa-user-plus\"></i>"
#define USER_ICON "<i class=\"fas fa-user\"></i>"
#define ADD_FOLDER_ICON "<i class=\"fas fa-folder-plus\"></i>"


class LoginHandler : public RequestHandler {
  public:
  LoginHandler(Drive* _drive) {drive = _drive; }
  Response *callback(Request *);

  private:
  Drive* drive;
};

class AdminHomeHandler : public RequestHandler {
  public:
  AdminHomeHandler(Drive* _drive) {drive = _drive; }
  Response *callback(Request *);

  private:
  Drive* drive;
};

class UserListHandler : public RequestHandler {
  public:
  UserListHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request *);
  std::string makeHtml();

  private:
  Drive* drive;
};

class PromoteHandler : public RequestHandler {
  public:
  PromoteHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
    Drive* drive;
};

class DemoteHandler : public RequestHandler {
  public:
  DemoteHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class AddUserHandler : public RequestHandler {
  public:
  AddUserHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class ElementListHandler : public RequestHandler {
  public:
  ElementListHandler(Drive* _drive) { drive = _drive; }
  Response* callback(Request* );
  std::string makeHtml(std::string sid);

  private:
  Drive* drive;
};

class goDirHandler : public RequestHandler {
  public:
  goDirHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class DetailHandler : public RequestHandler {
  public:
  DetailHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );
  std::string makeHtml(std::string sid, std::string path);

  private:
  Drive* drive;
};

class RemoveHandler : public RequestHandler {
  public:
  RemoveHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
    Drive* drive;
};

class CopyHandler : public RequestHandler {
  public:
  CopyHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class MoveHandler : public RequestHandler {
  public:
  MoveHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class PasteHandler : public RequestHandler {
  public:
  PasteHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class LogoutHandler : public RequestHandler {
  public:
  LogoutHandler(Drive* _drive) {drive = _drive; }
  Response *callback(Request *);

  private:
  Drive* drive;
};

class AddFolderHandler : public RequestHandler {
  public:
  AddFolderHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );

  private:
  Drive* drive;
};

class UploadHandler : public RequestHandler {
  public:
  UploadHandler(Drive* _drive) {drive = _drive; }
  Response *callback(Request *);
  private:
  Drive* drive;
};

class DownloadHandler : public RequestHandler {
  public:
  DownloadHandler(Drive* _drive) {drive = _drive; }
  Response* callback(Request* );
  std::string makeHtml(std::string path);

  private:
  Drive* drive;
};