   void addGroup(std::vector<std::string> addGroupData);
   void addToGroup(std::vector<std::string> addToGroupData);
   void upload(std::vector<std::string> uploadData);
   void download(std::vector<std::string> downloadData);
   void makeDirectory(std::vector<std::string> makeDirectoryData);
   void copy(std::vector<std::string> copyData);
   void remove(std::vector<std::string> removeData);
   
   
   std::vector<char> readFile(std::string fileName);
   void validDownloadData(std::vector<std::string> downloadData);
   void validMakeDirectoryData(std::vector<std::string> data);
   void validCopyData(std::vector<std::string> copyData);
   void validRemoveData(std::vector<std::string> removeData);
