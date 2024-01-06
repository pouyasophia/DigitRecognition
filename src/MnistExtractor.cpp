#include "../inc/MnistExtractor.hpp"
#include <algorithm>
#include <cctype>
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

void MnistExtractor::readMnistImage(std::string path) {
  std::ifstream file(path, std::ios::binary);

  // clean up path name
  path.erase(
      std::remove_if(path.begin(), path.end(),
                     [](auto const &c) -> bool { return !std::isalnum(c); }),
      path.end());

  std::string tempPath = path + "_ouput.txt";
  std::ofstream outfile(tempPath, std::ios::out);
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
    float imageSize = 255;
    for (u_int32_t i = 0; i < num_of_images; ++i) {
      float tempFloat;

      for (int r = 0; r < n_rows * n_cols; ++r) {

        unsigned char temp = 0;
        file.read((char *)&temp, sizeof(temp));
        tempFloat = (float(temp) / imageSize);

        if (r % 27 != 0)
          outfile << tempFloat << " ";
        else
          outfile << "\n";
        outfile << tempFloat << " ";

        _mnistImages.emplace_back(tempFloat);
      }
    }
    file.close();
    outfile.close();
  }
};

void MnistExtractor::readMnistLabel(std::string path) {
  std::ifstream file(path, std::ios::binary);

  // clean up path name
  path.erase(
      std::remove_if(path.begin(), path.end(),
                     [](auto const &c) -> bool { return !std::isalnum(c); }),
      path.end());

  std::string tempPath = path + "_ouput.txt";
  std::ofstream outfile(tempPath, std::ios::out);

  if (file.is_open()) {
    int magic_num = 0;
    int num_of_labels = 0;

    file.read((char *)&magic_num, sizeof(magic_num));
    magic_num = reverseInt(magic_num);
    file.read((char *)&num_of_labels, sizeof(num_of_labels));
    num_of_labels = reverseInt(num_of_labels);
    int count = 0;
    for (int i = 0; i < num_of_labels; ++i) {
      unsigned char temp = 0;
      file.read((char *)&temp, sizeof(temp));
      _mnistLabels.emplace_back(float(temp));

      // print vector to outfile
      outfile << _mnistLabels[i] << " ";
    }

    file.close();
    outfile.close();
  }
};