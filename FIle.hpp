   File(std::string fatherPath, std::string _name, std::string _userOwner, std::string _groupOwner, std::vector<char> _data);
   
   void setData(std::vector<char> _data) {data = _data; }
   virtual Document* goDir(std::string direction) {return NULL; }
   virtual void download(std::string outputName);
