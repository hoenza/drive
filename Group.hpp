   public:
   Group(std::string _name) {name = _name; }
   void addMember(std::string username) {members.push_back(username); }
   std::string getName() {return name; }
   bool isMember(std::string name);
