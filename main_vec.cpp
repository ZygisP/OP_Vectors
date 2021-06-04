#include "libraries.h"
#include "mokinys.h"
#include "func_vec.h"

int main() {
    Vec<mokinys> p;
    //generateInputFile(10, 100000, "generated_file.txt");

    readFromFile(p);
    writeToFiles(p);
    p.clear();

    return 0;
}