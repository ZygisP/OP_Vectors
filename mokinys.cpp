#include "libraries.h"
#include "mokinys.h"

mokinys::mokinys(string vardas, string pavarde)
{
    this->vardas = vardas;
    this->pavarde = pavarde;
    this->mediana = 0;
    this->vidurkis = 0;
}

mokinys::mokinys() {
	this->vardas = "";
    this->pavarde = "";
    this->mediana = 0;
    this->vidurkis = 0;
}

mokinys::mokinys(const mokinys& student) {
    this->vardas = student.vardas;
    this->pavarde = student.pavarde;
    this->mediana = student.mediana;
    this->vidurkis = student.vidurkis;
}

mokinys mokinys::operator=(const mokinys& student) {
    this->vardas = student.vardas;
    this->pavarde = student.pavarde;
    this->mediana = student.mediana;
    this->vidurkis = student.vidurkis;
    return *this;
}

mokinys::~mokinys() {} // destructor

double countAvg(vector<double> &grades) {
	double sum = 0;
	sum = std::accumulate(grades.begin(), grades.end(), 0.0);
	return sum / grades.size();
}

double countMedian(vector<double> &grades) {
	sort(grades.begin(), grades.end());
	double median;

	if (!(grades.size() == 0)) {
		if ((grades.size()) % 2 == 0) {
			median = (grades[grades.size() / 2 - 1] / 2) + (grades[grades.size() / 2] / 2);
			return median;
		} else {
			median = grades[grades.size() / 2];
			return median;
		}
	}
	return 0;
}

void mokinys::countSemester(vector<double> &grade, double exam_res) {
	exam_res *= 0.6;
	vidurkis = countAvg(grade) * 0.4 + exam_res;
	mediana = countMedian(grade) * 0.4 + exam_res;
}

// getters
const string zmogus::getVardas() {
	return vardas;
}

const string zmogus::getPavarde() {
	return pavarde;
}

//setters
void zmogus::setVardas(string name) {
	vardas = name;
}

void zmogus::setPavarde(string surname) {
	pavarde = surname;
}

// more getters
double mokinys::getMedian() {
	return mediana;
}

double mokinys::getAvg() {
	return vidurkis;
}

// more setters
void mokinys::setAvg(double a) {
	vidurkis = a;
}

void mokinys::setMedian(double m) {
	mediana = m;
}

bool mokinys::operator < (const mokinys &student) const {
	return vardas.compare(student.vardas) < 0;
}

