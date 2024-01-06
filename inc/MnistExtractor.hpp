#include <iostream>
#include <string>
#include <vector>

class MnistExtractor {
public:
  int reverseInt(int x);
  void readMnistImage(std::string path);
  void readMnistLabel(std::string path);
  std::vector<float> getImages() { return _mnistImages; }
  std::vector<float> getLabels() { return _mnistLabels; }

private:
  std::vector<float> _mnistImages;
  std::vector<float> _mnistLabels;
};
