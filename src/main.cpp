#include "CalculateGap.hpp"
#include "Tile.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define VERSION "1.0"
#define PROG_NAME "main"
#define YEAR "2017"
#define LICENSE "unlicense"
#define AUTHOR "Justin Kaipada"

void helper();
void calculateWithDimensions(Tile);
void readFromFile();
void errorInArguments();

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Pentagonal Tiling %s\n", VERSION);
    printf("Copyright (c) %s, %s.  All rights reserved.\n", YEAR, AUTHOR);
    printf("This program was made available under %s\n", LICENSE);
    printf("See LICENSE file included with the distribution for details and "
           "disclaimer.\n");
    printf("\nError : No arguments specified (use -help or -h for help)\n\n");
  } else {
    if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0)
      helper();
    else if (strcmp(argv[1], "-d") == 0) {
      if (argc == 11) {
        Tile pentagon = {atof(argv[2]), atof(argv[3]), atof(argv[4]),
                         atof(argv[5]), atof(argv[6]), atof(argv[7]),
                         atof(argv[8]), atof(argv[9]), atof(argv[10])};
        calculateWithDimensions(pentagon);
      } else if (argc == 12) {
        Tile pentagon = {atof(argv[2]), atof(argv[3]), atof(argv[4]),
                         atof(argv[5]), atof(argv[6]), atof(argv[7]),
                         atof(argv[8]), atof(argv[9]), atof(argv[10]),
                         atof(argv[11])};
        calculateWithDimensions(pentagon);
      } else
	errorInArguments();
    } else if (strcmp(argv[1], "-f") == 0)
      readFromFile();
    else
      errorInArguments();
  }
  return 0;
}

void helper() {
  printf("Pentagonal Tiling %s\n", VERSION);
  printf("Copyright (c) %s, %s.  All rights reserved.\n", YEAR, AUTHOR);
  printf(
	 "\nTo use the program call the executable and pass either 9 or 10 \n"
	 "arguments, which are the dimensions of the pentagon you're trying to \n"
	 "get the gap from. \n");
  printf("The first five arguments must be dimensions of the sides\n");
  printf("The next four of five are measurement of the angles in degrees\n");
  printf("To pass arguments this way you should also use the flag \"-d\" or "
         "\"-dimensions\". \n");
  printf("For example, this is a correct way to invoke the program\n");
  printf("\.\/%s\.exe -d 32.72 73.59 78.67 49.06 57.68 122.03 115.73 84.19 "
         "95.81 122.23\n",
         PROG_NAME);
  printf("\nYou can also pass arguments in a file with many calculations to "
         "do.\n");
  printf("For that use the flag \"-f\" instead of \"-d\" and then pass the "
         "path to the file \n");
  printf("Or just the name of the file if its in the same directory as the "
         "executable \n");
  printf("For example, this is another correct way to invoke the program\n");
  printf("\.\/%s\.exe -f data.csv\n", PROG_NAME);
  printf("Only .csv files are parsable now\n");
  printf("\nPassing dimensions returns the gap here\n");
  printf("Passing a file writes the answer into the file called result.dat\n");
}

void calculateWithDimensions(Tile tile) {
  double minimum_gap = getGap(tile);
  printf("\n Minimum gap calculated is : %f",minimum_gap);
}

void readFromFile() {}

void errorInArguments() {
  printf("Pentagonal Tiling %s\n", VERSION);
  printf("Copyright (c) %s, %s.  All rights reserved.\n", YEAR, AUTHOR);
  printf("\nError : Unrecognized flag or arguments(use -help or -h for "
         "help)\n\n");
}
