#include "vector.h"
using namespace std;
// tariame, kad `avail` point'ina į išskirtą, bet neinicializuotą vietą
int main() {
    Vec<int> musu_vec;
    vector<int> tikras_vec;
    int sampleSize = 10000;
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < sampleSize; i++) {
        musu_vec.push_back(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    cout << std::chrono::duration <double, milli> (diff).count() << " ms" << endl;
    musu_vec.~Vec();
    start = std::chrono::steady_clock::now();
    for(int i = 0; i < sampleSize; i++) {
        tikras_vec.push_back(i);
    }
    end = std::chrono::steady_clock::now();
    diff = end - start;
    cout << std::chrono::duration <double, milli> (diff).count() << " ms" << endl;
    tikras_vec.clear();
}