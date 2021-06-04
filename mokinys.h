#ifndef mokinys_h
#define mokinys_h

#include "libraries.h"
#include "vector.h"

class zmogus {
protected:
    string vardas, pavarde;
public:
    virtual const string getVardas();
    virtual const string getPavarde();

    void setVardas(string name);
    void setPavarde(string surname);

    virtual void print() = 0;
};

class mokinys : public zmogus {
private:
    double vidurkis, mediana;

public:
    mokinys(string vardas, string pavarde);
    //CONSTRUCTOR
    mokinys();
    //COPY CONSTRUCTOR
    mokinys(const mokinys& student);
    //ASSIGN OPERATOR
    mokinys operator=(const mokinys& student);
    //DESTRUCTOR
    ~mokinys();
    void countSemester(vector<double> &grade, double exam_res);

    double getAvg();

    double getMedian();

    void setMedian(double m);

    void setAvg(double a);

    bool operator < (const mokinys &student) const;

    void print() override{};
};

#endif