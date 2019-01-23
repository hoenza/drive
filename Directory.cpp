

void Directory::addFile(string fileName,string userOwner , vector<char> data) {
   if(findDocument(fileName) != NULL)
      throw ErrorException(ERROR_FILE_SAME_NAME);
   File* newFile = new File(this->getPath(), fileName, userOwner, "", data);
   documents.push_back(newFile);
}



void Directory::addDirectory(Document* newDocument) {
   if(findDocument(newDocument->getName()) != NULL)
      throw ErrorException(ERROR_DOCUMENT_SAME_NAME);

   documents.push_back(newDocument);
}

void Directory::remove(std::string path) {
   for(int i=0; i<documents.size(); i++)
      if(documents[i]->getPath() == path) {
         documents.erase(documents.begin() + i);
         return;
      }
}