#include "func_vec.h"

double getAverage(Vec<double> pazymiai, int exam_res) {
	double avg = 0;
	for (int i = 0; i < pazymiai.size(); i++) {
		avg += pazymiai[i];
	}

	avg = ((avg/pazymiai.size()) * 0.4) + (0.6 * exam_res);
	return avg;
}

double getMedian(Vec<double> pazymiai, int exam_res) {
	sort(pazymiai.begin(), pazymiai.end());
	double median;

	if ((pazymiai.size()) % 2 == 0) {
		median = (pazymiai[pazymiai.size() / 2 - 1] / 2) + (pazymiai[pazymiai.size() / 2] / 2);
		return median;
	} else {
		median = pazymiai[pazymiai.size() / 2];
		return median;
	}
}

int numOfDigits(int number){
    int output = 0;
    if(number == -1){
        output = 0;
    } else if(number==0){
        number=1;
    }
    while(number>0){
        number=number/10;
        output++;
    }
    return output;
}
bool checkFileExists(string filename) {
    ifstream file_to_check(filename);
    if (file_to_check.is_open()) {
        file_to_check.close();
        return true;
    }
    return false;    
}
void generateInputFile(int nOfNd, int nOfStudents, string filename){
    auto start = std::chrono::steady_clock::now();
    int temp = -1;
    string name = "Vardas";
    string surname = "Pavarde";
    string nd = "ND";
    srand(time(NULL));
    ofstream rOffile;
    cout<<"Generating..."<<endl;
    rOffile.open(filename);
    rOffile << "Vardas              Pavarde                ND1   ND2   ND3   ND4   ND5      Egz." << endl;
    rOffile << "------------------------------------------------------------------------------" << endl;
    for(int i=0; i<nOfStudents; i++){
        rOffile << right <<  name << i;
        rOffile << setw(20-numOfDigits(i)) << right;
        rOffile << surname << i;

        for(int j=0; j<nOfNd; j++){
            if(j==0) {
                rOffile << setw(18-numOfDigits(i)) << right;
            }
            else {
                rOffile << setw(6) << right;
            }
                rOffile  << rand() % 10 + 1;
            }
            rOffile << setw(6) << right << rand() % 10 + 1;
            if(i != nOfStudents-1) {
                rOffile<<endl;
            }
        }
        rOffile.close();
        auto ending = std::chrono::steady_clock::now();
        cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;
}

void readFromFile (Vec<mokinys> &p) {
    ifstream infile ("generated_file.txt");

    try{
    	if(infile.fail()) throw "Klaida! Failo pavadinimas.";
    } catch(const char * e) {
    	std::cerr << e << endl;
    	exit(EXIT_FAILURE);
    }

	auto start = std::chrono::steady_clock::now();
    stringstream sStream;

    sStream << infile.rdbuf();
    infile.close();
    string temp;
    getline(sStream, temp);
    temp.clear();
    getline(sStream, temp);
    temp.clear();
    cout<<"Reading from file..."<<endl;
    int counter = 0;
    while(!sStream.eof()) {
    	string eilute;
    	getline(sStream, eilute);
    	if (sStream.eof()) break;
    	stringstream lStream(eilute);

    	double exam_res;
        Vec<double> grades;
    	mokinys temp_student;

    	string vardasTemp, pavardeTemp;

    	lStream >> vardasTemp >> pavardeTemp;
    	temp_student.setVardas(vardasTemp);
    	temp_student.setPavarde(pavardeTemp);

    	while(!lStream.eof()) {
    		double pazymis;
    		lStream >> pazymis;
    		if(lStream.eof())
    			exam_res = pazymis;
    		else
    			grades.push_back(pazymis);
    	}
    	temp_student.setAvg(getAverage(grades, exam_res));
    	temp_student.setMedian(getMedian(grades, exam_res));

    	p.push_back(temp_student);
        if (p.capacity() == p.size())
            counter++;
    }
    auto ending = std::chrono::steady_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;

    cout << counter << " times capacity==size" << endl;

    sort(p.begin(), p.end());
}

void sortByCool(Vec<mokinys> &k, Vec<mokinys> &l, Vec<mokinys> &p) {
    int counter = 0;
    auto start = std::chrono::steady_clock::now();
    cout<<"Splitting students..."<<endl;
    for(int i=0; i<p.size(); i++) {
        if(p[i].getAvg() >= 5) {
            k.push_back(p[i]);
            if (k.capacity() == k.size())
                counter++;
        } else {
            l.push_back(p[i]);
            if (l.capacity() == l.size())
                counter++;
        }
    }
    auto ending = std::chrono::steady_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;
    cout << counter << " times capacity==size" << endl;
}

void writeToFiles(Vec<mokinys> &p) {
	Vec<mokinys> kietekas;
    Vec<mokinys> lievakas;
    sortByCool(kietekas, lievakas, p);
	ofstream offile_k("kietekai.txt");
    ofstream offile_l("lievakai.txt");
    offile_k << "Vardas" << setw(15+7) << "Pavarde" << setw(15+15) << "Vidurkis (med.)" << setw(5+15) << "Vidurkis (vid.)" 
    << endl << "------------------------------------------------------------------------------" << endl;
    offile_l << "Vardas" << setw(15+7) << "Pavarde" << setw(15+15) << "Vidurkis (med.)" << setw(5+15) << "Vidurkis (vid.)" 
    << endl << "------------------------------------------------------------------------------" << endl;
    auto start = std::chrono::high_resolution_clock::now();
    cout<<"Writing..."<<endl;
    for(int i=0; i < kietekas.size(); i++){
        offile_k << kietekas[i].getVardas() << setw(25 - kietekas[i].getVardas().length() + kietekas[i].getPavarde().length()) << kietekas[i].getPavarde() 
            << setw(25 - kietekas[i].getPavarde().length() + 3) << fixed << setprecision(2) << kietekas[i].getMedian()  
            << setw(25 - 3 + 3) << fixed << setprecision(2) << kietekas[i].getAvg() << endl;
    }
    for(int i=0; i < lievakas.size();i++){
       offile_l << lievakas[i].getVardas() << setw(25 - lievakas[i].getVardas().length() + lievakas[i].getPavarde().length()) << lievakas[i].getPavarde() 
            << setw(25 - lievakas[i].getPavarde().length() + 3) << fixed << setprecision(2) << lievakas[i].getMedian()  
            << setw(25 - 3 + 3) << fixed << setprecision(2) << lievakas[i].getAvg() << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(end - start).count()<<" ms"<<endl;
}

/*void mokinys::getAverages(vector<mokinys> &p) {
    auto start = std::chrono::steady_clock::now();
    cout<<"Calculating averages..."<<endl;
    double sum = 0;
    for(int i=0; i<p.size(); i++){
        sum = 0;
        for(int j=0; j<p[i].nd.size(); j++){
            sum+=p[i].nd[j];
        }
        p[i].vidurkis = 0.4 * (sum/p[i].nd.size()) + 0.6 * p[i].egzaminas;
    }
    auto ending = std::chrono::steady_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;
}
*/

/*void mokinys::getMedians(vector<mokinys> &p) {
    cout<<"Calculating medians..."<<endl;
    auto start = std::chrono::steady_clock::now();
    for(int x=0; x<p.size(); x++){
        int n = p[x].nd.size();
        sort(p[x].nd.begin(), p[x].nd.end());
        if(n%2 == 1){
            p[x].mediana = 0.4 * (p[x].nd[n/2]) + 0.6 * p[x].egzaminas;
        } else {
            p[x].mediana = 0.4 * ((p[x].nd[n/2] + p[x].nd[(n/2)-1]) / 2) + 0.6 * p[x].egzaminas;
        }
    }
    auto ending = std::chrono::steady_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;
}
*/

/*void mokinys::writeEverything(vector<mokinys> k, vector<mokinys> l) {
    auto start = std::chrono::steady_clock::now();
    cout<<"Writing..."<<endl;
    ofstream offile_k ("kietekai.txt");
    offile_k<<k;

    ofstream offile_l ("lievakai.txt");
    offile_l<<l;
    auto ending = std::chrono::steady_clock::now();
    cout<<"Done in : "<<std::chrono::duration <double, milli>(ending - start).count()<<" ms"<<endl;
}
ostream& operator<<(ostream& os, vector<mokinys> &vec){
    os.width(15);
    os << left << "Vardas";
    os.width(15);
    os << left << "Pavarde";
    os.width(20);
    os << left << "Galutinis (Vid.)";
    os.width(20);
    os << left << "Galutinis (Med.)"<<endl;
    for (int n = 0; n < 70; n++) os << "-";
    os<<endl;
    for(int i=0; i < vec.size(); i++) {
        os.width(15);
        os << left << vec[i].vardas;
        os.width(15);
        os << left << vec[i].pavarde;
        os.width(20);
        os << fixed << setprecision(2) << vec[i].vidurkis;
        os.width(20);
        os << fixed << setprecision(2) << vec[i].mediana<<endl;
    }
    return os;
}
*/