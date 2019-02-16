#include "handlers.hpp"
#include "my_server.hpp"
#include "../drive/Drive.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  Drive* myDrive = new Drive();
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/bg.jpg", new ShowImage("static/bg.jpg"));
    server.get("/pic2.jpg", new ShowImage("static/pic02.jpg"));
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(myDrive));
    server.get("/logout", new LogoutHandler(myDrive));
    server.get("/addUser", new ShowPage("static/adduser.html"));
    server.post("/addUser", new AddUserHandler(myDrive));
    server.get("/adminPage", new ShowPage("static/adminPage.html"));
    server.get("/users", new UserListHandler(myDrive));
    server.get("/promote", new PromoteHandler(myDrive));
    server.get("/demote", new DemoteHandler(myDrive));
    server.get("/elements", new ElementListHandler(myDrive));
    server.get("/goDir", new goDirHandler(myDrive));
    server.get("/details", new DetailHandler(myDrive));
    server.get("/remove", new RemoveHandler(myDrive));
    server.get("/copy", new CopyHandler(myDrive));
    server.get("/move", new MoveHandler(myDrive));
    server.get("/paste", new PasteHandler(myDrive));
    server.get("/addFolder", new ShowPage("static/addfolder.html"));
    server.post("/addFolder", new AddFolderHandler(myDrive));
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler(myDrive));
    server.get("/download", new DownloadHandler(myDrive));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
  delete myDrive;
}
