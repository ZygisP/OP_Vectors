#ifndef FUNCTION
#define FUNCTION
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "vector.h"
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::streamsize;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::setprecision;
using std::milli;
using std::to_string;

//inline ifstream infile("studentai10000.txt");
//inline ofstream offile("res.txt");

class zmogus {
   public:
    string vardas;
    string pavarde;
    virtual int test() = 0;
};

class mokinys : public zmogus {
   public:
    double egzaminas;
    Vec<double> nd;
    double vidurkis;
    double mediana;
    void getAverages(Vec<mokinys> &p);
    void getMedians(Vec<mokinys> &p);
    void sortByCool(Vec<mokinys> &k, Vec<mokinys> &l, Vec<mokinys> &p);
    void readFromFile(Vec<mokinys> &p, string inputFileName);
    void writeEverything(Vec<mokinys> k, Vec<mokinys> l);
    int test();
    friend ostream& operator<<(ostream& os, Vec<mokinys> &vec);
};

bool compare(const mokinys &first, const mokinys &second);
int numOfDigits(int number);
void generateInputFile(int nOfNd, int nOfStudents, string filename);
bool checkFileExists(string filename);
ostream& operator<<(ostream& os, Vec<mokinys> &vec);
#endif