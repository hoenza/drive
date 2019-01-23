
#define READ "Read"
#define WRITE "Write"
#define READ_WRITE "Read_Write"


   Directory(std::string fatherPath, std::string _name, std::string _userOwner, std::string _groupOwner)
      :Document(fatherPath, _name, _userOwner, _groupOwner) {type = DIRECTORY; }
   
   void addFile(std::string fileName,std::string userOwner, std::vector<char> data);
   Document* findDocument(std::string document);
   virtual void addDirectory(std::string userOwner, std::string directoryName);
   virtual void addDirectory(Document* newDirectory);
   virtual void remove(std::string path);
   
};
