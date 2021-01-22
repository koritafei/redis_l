/**
 * @file set_new_handler.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief test set_new_handler cpp
 * @version 0.1
 * @date 2020-11-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

void oom_handler() {
  std::cout << "Out of memory when allocate " << std::endl;
  std::exit(1);
}

int main(int argc, char **argv) {
  std::set_new_handler(oom_handler);
  char *p = new char[4294967295];
  std::cout << "Ok\n";
  delete[] p;
}
