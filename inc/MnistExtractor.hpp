#include <iostream>
#include <string>

class MnistExtractor {
public:
  int reverseInt(int x);
  void readMnist(std::string path);
  unsigned char **read_mnist_images(std::string full_path,
                                    int &number_of_images, int &image_size);
};
