#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("Pentagonal Tiling 1.0\n");
    printf("Copyright (c) 2017, JustinJK007.  All rights reserved.\n");
    printf("This program was made available under the unlicense\n");
    printf("See LICENSE file included with the distribution for details and disclaimer.\n");
    printf("\nError : No arguments specified (use -help or -h for help)\n\n");
  }
  else {
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
      std::cout << argv[i] << std::endl;
    }
  }
  return 0;
}
