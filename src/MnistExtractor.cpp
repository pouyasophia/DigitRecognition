#include "../inc/MnistExtractor.hpp"
#include <fstream>
#include <iostream>

int MnistExtractor::reverseInt(int x) {
  unsigned char c1, c2, c3, c4;

  c1 = x & 255;
  c2 = (x >> 8) & 255;
  c3 = (x >> 16) & 255;
  c4 = (x >> 24) & 255;

  return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
};

void MnistExtractor::readMnist(std::string path) {
  std::ifstream file(path, std::ios::binary);
  std::ofstream outfile("mnistOutput.txt", std::ios::out);
  if (file.is_open()) {
    int magic_num = 0;
    int num_of_images = 0;
    int n_rows = 0;
    int n_cols = 0;

    file.read((char *)&magic_num, sizeof(magic_num));
    magic_num = reverseInt(magic_num);
    file.read((char *)&num_of_images, sizeof(num_of_images));
    num_of_images = reverseInt(num_of_images);
    file.read((char *)&n_rows, sizeof(n_rows));
    n_rows = reverseInt(n_rows);
    file.read((char *)&n_cols, sizeof(n_cols));
    n_cols = reverseInt(n_cols);

    for (int i = 0; i < num_of_images; ++i) {
      for (int r = 0; r < n_rows; ++r) {

        for (int c = 0; c < n_cols; ++c) {
          unsigned char temp = 0;
          file.read((char *)&temp, sizeof(temp));
          outfile << u_int32_t(temp) << " ";
        }
        outfile << "\n";
      }
      outfile << "\n";
    }
  }
};
