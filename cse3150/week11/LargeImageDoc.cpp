// The following code works on small data, but not on large data
#include <vector>
#include <map>
#include <set>
#include <string>

// Large document
class LargeImageDoc
{
public:
  // <int, string>: the page where the image is at and the filename to load the image
  /*LargeImageDoc(const std::map<int, std::string > &listImageInfo) : numTicks(0)
  {
    for(auto it = listImageInfo.begin(); it != listImageInfo.end(); ++it)
    {
      LoadImage(it->first, it->second);
    }
  }*/
  explicit LargeImageDoc(const std::map<int, std::string> &listImageInfo) : imageInfo(listImageInfo), numTicks(0) {}
  void Show(int page)
  {
    // do nothing for now
    if(imageInfo.find(page) != imageInfo.end() && loadedImages.find(page) == loadedImages.end()){
	LoadImage(page, imageInfo[page]);
	loadedImages.insert(page);
    }
  }
  
private:
  // don't change this function
  void LoadImage(int page, const std::string &fileNameImage)
  {
    for(int i=0; i<1000000; ++i)
    {
      ++numTicks;
    }
  }
  
  std::map<int, std::string> imageInfo;
  std::set<int> loadedImages;
  int numTicks;
};
