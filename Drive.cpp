
void Drive::validCopyData(vector<string> data) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(data.size() != 2)
      throw ErrorException(ERROR_INVALID_DATA);

   string sourcePath = data[0];
   if(goDir(sourcePath) == NULL)
      throw ErrorException(ERROR_INVALID_SOURCE_PATH);

   string destinationPath = data[1];
   if(goDir(destinationPath) == NULL)
      throw ErrorException(ERROR_INVALID_DESTINATION_PATH);
}

void Drive::copy(std::vector<std::string> copyData) {
   validCopyData(copyData);
   string sourcePath = copyData[0];
   Document* source = goDir(sourcePath);

   string destinationPath = copyData[1];

}

void Drive::validRemoveData(vector<string> removeData) {
   if(loggedUser == NULL)
      throw ErrorException(ERROR_NOONE_LOGGEDIN);
   if(removeData.size() != 1)
      throw ErrorException(ERROR_INVALID_DATA);
   string path = removeData[0];
   Document* target = goDir(path);
   if(target == NULL)
      throw ErrorException(ERROR_INVALID_PATH);
}

void Drive::remove(vector<string> removeData) {
   validRemoveData(removeData);
   string path = removeData[0];
   Document* fatherDirectory = goFatherDir(path);
   fatherDirectory->remove(path);
}