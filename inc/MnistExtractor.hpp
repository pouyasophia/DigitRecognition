#include <iostream>
#include <string>

class MnistExtractor {
public:
  int reverseInt(int x);
  void readMnistImage(std::string path);
  void readMnistLabel(std::string path);
};
