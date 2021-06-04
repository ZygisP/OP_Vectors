#ifndef FUNCTION
#define FUNCTION

#include "libraries.h"
#include "mokinys.h"
#include "vector.h"

void writeToFiles(Vec<mokinys> &p);
void sortByCool(Vec<mokinys> &k, Vec<mokinys> &l, Vec<mokinys> &p);
void readFromFile (Vec<mokinys> &p);
void generateInputFile(int nOfNd, int nOfStudents, string filename);
bool checkFileExists(string filename);
int numOfDigits(int number);
void getAverage(Vec<mokinys> &p);
void getMedian(Vec<mokinys> &p);
#endif