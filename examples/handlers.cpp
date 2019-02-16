#include "handlers.hpp"

using namespace std;

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string sid;
  try {
    sid = drive->login(username, password);
    for(int i=0; i<sid.size(); i++)
      cout<<(int)sid[i]<< "_";
    cout<< "size = "<< sid.size()<< endl;
  }
  catch(ErrorException e) {
    throw Server::Exception(e.getError());
  }
  Response* res;
  if(drive->isAdmin(sid))
    res = Response::redirect("/adminPage");
  else
    res = Response::redirect("/elements");
  res->setSessionId(sid);
  return res;
}

Response* UserListHandler::callback(Request* req) {
  if(!drive->isAdmin(req->getSessionId()))
    throw Server::Exception(ERROR_WRONG_AUTHORITY);
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  res->setBody(makeHtml());
  return res;
}

string UserListHandler::makeHtml() {
  vector<string> userList = drive->getUserList();
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += LINK;
  body += "<style>";
  body += "* { font-size:30px;margin:auto;color:dimgray;outline:none;}";
  body += ".field{margin: 10px 15px;}";
  body += "html, body {height:100%; margin=0;}";
  body += "body {background-image: url(\"/bg.jpg\"); background-size: cover;";
  body += "background-repeat: no-repeat; background-position: center;}";
  body += "</style>";
  body += "</head>";
  body += "<body style=\"text-align: center;\"><div class=\"all\"";
  body += "<div><a href=\"addUser\" style=\"text-decoration:none;\">";
  body += ADD_USER_ICON;
  body += "</a></div class=\"all\">";
  for(int i=0; i<userList.size(); i++) {
    body += "<div class=\"field\"><span> " + userList[i] + "</span>";
    body += "<span><a href = \"/promote?user=" + userList[i] + "\" style=\"text-decoration:none;\">" + PROMOTE_ICON + "</a></span>";
    body += "<span><a href = \"/demote?user=" + userList[i] + "\"  style=\"text-decoration:none;\">" + DEMOTE_ICON + "</a></span>";
    body += "</div></div>";
  }
  body += "</body></html>";
  return body;
}

Response* PromoteHandler::callback(Request* req) {
  string targetUser = req->getQueryParam("user");
  string sid = req->getSessionId();
  try{
    drive->promote(sid, targetUser);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/users");
  return res;
}

Response* DemoteHandler::callback(Request* req) {
  string targetUser = req->getQueryParam("user");
  string sid = req->getSessionId();
  try{
    drive->demote(sid, targetUser);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/users");
  return res;
}

Response* AddUserHandler::callback(Request* req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string sid = req->getSessionId();
  try{
    drive->addUser(sid, username, password);
  }
  catch(ErrorException e) {
    throw Server::Exception(e.getError());
  }
  Response* res;
  if(drive->isAdmin(sid))
    res = Response::redirect("/adminPage");
  else
    res = Response::redirect("/elements");
  return res;
}

Response* ElementListHandler::callback(Request* req) {
  Response* res = new Response;
  res->setHeader("Content-type", "text/html");
  try {
    res->setBody(makeHtml(req->getSessionId()));
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  return res;
}

string ElementListHandler::makeHtml(string sid) {
  vector<string> nameList = drive->listNameElement(sid);
  vector<string> pathList = drive->listPathElement(sid);

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += LINK;
  body += "<style>";
  body += "* {font-size: 30px; margin: 10px 15px; color: dimgray; outline:none;}";
  body += "html, body {width=100%; height:100%; margin=0;}";
  body += "body {background-image: url(\"/bg.jpg\"); background-size: cover;";
  body += "background-repeat: no-repeat; background-position: center;}";
  body += "</style>";
  body += "</head>";
  body += "<body style=\"text-align: center;\">";
  body += "<div class=\"title\"><span><a href = \"/up\" title=\"Upload\" style=\"text-decoration:none;\">";
  body += UPLOAD_ICON;
  body += "</a></span>";
  body += "<div class=\"title\"><span><a href=\"/addFolder\" title=\"Add Folder\" style=\"text-decoration:none;\">";
  body += ADD_FOLDER_ICON;
  body += "</a><span>";
  body += "<span><a href = \"/paste\" title=\"Paste\" style=\"text-decoration:none;\">";
  body += PASTE_ICON;
  body += "</a></span>";
  body += "<span><a href = \"/logout\" title=\"Exit\" style=\"text-decoration:none;\">";
  body += EXIT_ICON;
  body += "</a></span></div>";
  for(int i=0; i<nameList.size(); i++) {
    body += "<div class=\"field\">";
    body += "<a href = \"/goDir?path=" + pathList[i] + "\" title=\"ElementName\" style=\"text-decoration:none;\">" + nameList[i] + "</a>";
    if(nameList[i] != "..") {
      body += "<a href = \"/copy?sourcePath=" + pathList[i] + "\" title=\"Copy\" style=\"text-decoration:none;\">" + COPY_ICON + "</a>";
      body += "<a href = \"/move?sourcePath=" + pathList[i] + "\" title=\"Move\" style=\"text-decoration:none;\">"+ MOVE_ICON +"</a>";
      body += "<a href = \"/details?path=" + pathList[i] + "\" title=\"Details\" style=\"text-decoration:none;\">"+ DETAIL_ICON + "</a>";
      body += "<a href = \"/remove?path=" + pathList[i] + "\" title=\"Remove\" style=\"text-decoration:none;\">"+ REMOVE_ICON +"</a></div>";
    }
  }
  body += "</body></html>";
  return body;
}

Response* goDirHandler::callback(Request* req) {
  string path = req->getQueryParam("path");
  string sid = req->getSessionId();
  Response* res;
  try {
    if(drive->getType(path) == _FOLDER_) {
      try {
        drive->changeDirectory(sid, path);
      }
      catch(ErrorException e) {
        Server::Exception(e.getError());
      }
      res = Response::redirect("/elements");
    }
    else {
      string data = drive->download(path);
      res = new Response;
      res->setHeader("Content-type", "text/plain");
      res->setBody(data);
    }
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  return res;
}

Response* DetailHandler::callback(Request* req) {
  string path = req->getQueryParam("path");
  string sid = req->getSessionId();
  Response* res = new Response;
  res->setHeader("Content-type", "text/html");
  try {
    res->setBody(makeHtml(sid, path));
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  return res;
}

string DetailHandler::makeHtml(string sid, string path) {
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += LINK;
  body += "<style>";
  body += "* {font-size: 30px;}";
  body += ".icon {font-size: 40px; color:dimgray}";
  body += "html, body {width=100%;height:100%; margin=0;}";
  body += "body {background-image: url(\"/bg.jpg\"); background-size: cover;";
  body += "background-repeat: no-repeat; background-position: center;}";
  body += "</style>";
  body += "</head>";
  body += "<body style=\"text-align: center;\">";
  body += "<div><pre>";
  body += "element List\n";
  body += drive->detail(sid, path);
  body += "</div></pre>";
  if(drive->getType(path) == _FILE_)
    body += "<div class=\"icon\"><a href = \"/download?path=" + path + "\" style=\"text-decoration:none;\">" + DOWNLOAD_ICON + "</a></div>";
  body += "</body></html>";
  return body;
}

Response* RemoveHandler::callback(Request* req) {
  string path = req->getQueryParam("path");
  string sid = req->getSessionId();
  try {
    drive->remove(sid, path);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/elements");
  return res;
}

Response* CopyHandler::callback(Request* req) {
  string sid = req->getSessionId();
  string sourcePath = req->getQueryParam("sourcePath");
  try {
    drive->copy(sid, sourcePath);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/elements");
  return res;
}

Response* MoveHandler::callback(Request* req) {
  string sid = req->getSessionId();
  string sourcePath = req->getQueryParam("sourcePath");
  try {
    drive->move(sid, sourcePath);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/elements");
  return res;
}

Response* PasteHandler::callback(Request* req) {
  string sid = req->getSessionId();
  try {
    drive->paste(sid);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/elements");
  return res;
}

Response *AdminHomeHandler::callback(Request * req) {
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  res->setBody("../static/adminPage.html");
  return res;
}

Response *LogoutHandler::callback(Request *req) {
  string sid = req->getSessionId();
  try {
    drive->logout(sid);
  }
  catch(ErrorException e) {
    throw Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/");
  res->setSessionId("");

  return res;
}

Response* AddFolderHandler::callback(Request* req) {
  string name = req->getBodyParam("folderName");
  string sid = req->getSessionId();
  try {
    drive->addFolder(sid, name);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response* res = Response::redirect("/elements");
  return res;
}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  string sid = req->getSessionId();
  cerr<< name<<file<< sid<< endl;
  try {
    drive->upload(sid, name, file);
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  Response *res = Response::redirect("/elements");
  return res;
}

Response* DownloadHandler::callback(Request* req) {
  string path = req->getQueryParam("path");
  Response* res = new Response;
  drive->getName(path);
  res->setHeader("Content-Type", "application/octet-stream");
  res->setHeader("Content-Disposition", "attachment");
  res->setHeader("filename", "\"picture.png\"");
  try {
    res->setBody(makeHtml(path));
  }
  catch(ErrorException e) {
    Server::Exception(e.getError());
  }
  return res;
}

string DownloadHandler::makeHtml(string path) {
  string ans = drive->download(path);
  return ans;
}