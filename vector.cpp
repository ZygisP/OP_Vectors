#include "vector.h"
using namespace std;
// tariame, kad `avail` point'ina į išskirtą, bet neinicializuotą vietą
int main() {
    Vec<int> musu_vec;
    vector<int> tikras_vec;

    int sampleSizes[4] = {100000, 1000000, 10000000, 100000000};
    for (int i = 0; i < 4; i++) {
        int counter1 = 0, counter2 = 0;
    	cout << sampleSizes[i] << " pushbacks:" << endl;
    	auto start = std::chrono::steady_clock::now();
    	for(int j = 0; j < sampleSizes[i]; j++) {
        	musu_vec.push_back(j);
            if (musu_vec.capacity() == musu_vec.size())
                counter1++;
   		}
        cout << counter1 << " times capacity==size (our vec)" << endl;
    	auto end = std::chrono::steady_clock::now();
    	auto diff = end - start;
    	cout << std::chrono::duration <double, milli> (diff).count() << " ms" << endl;
    	musu_vec.clear();
    	start = std::chrono::steady_clock::now();
	    for(int j = 0; j < sampleSizes[i]; j++) {
	        tikras_vec.push_back(j);
            if (tikras_vec.capacity() == tikras_vec.size())
                counter2++;
	    }
        cout << counter2 << " times capacity==size (classic vec)" << endl;
	    end = std::chrono::steady_clock::now();
	    diff = end - start;
	    cout << std::chrono::duration <double, milli> (diff).count() << " ms" << endl;
	    tikras_vec.clear();
    }
}