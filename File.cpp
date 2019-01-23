#include "FIle.hpp"

using namespace std;

File::File(std::string fatherPath, std::string _name, std::string _userOwner, std::string _groupOwner, std::vector<char> _data)
      :Document(fatherPath, _name, _userOwner, _groupOwner) {
   type = FILE_SIGN;
   data = _data;
}

