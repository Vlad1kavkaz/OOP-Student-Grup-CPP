#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Student
{

    string Name;
    string NumZach;
    int KolDis;
    int *marks;

public:

    Student()
    {
        Name = "";
        NumZach = "";
        KolDis = 0;
        marks = nullptr;
    }
    Student(string Name_, string NumZach_, int KolDis_, const int *marks_){
        Name = Name_;
        NumZach = NumZach_;
        KolDis = KolDis_;
        marks = new int[KolDis];
        for(int i = 0; i < KolDis; i++){
            marks[i] = marks_[i];
        }

        if (NumZach_.length() != 6)
        {
            throw invalid_argument("Invalid NumZach");
        }
    }

    void setName(string Name_)
    {
        this->Name = std::move(Name_);
    }
    void setNumZach(string NumZach_)
    {
        this->NumZach = std::move(NumZach_);
    }
    void setKolDis(int KolDis_)
    {
        this->KolDis = KolDis_;
    }
    void setmarks(int *marks_)
    {
        this->marks = marks_;
    }
    void setStudent(string Name_, string NumZach_, int KolDis_, int *marks_)
    {
        this->Name = std::move(Name_);
        this->NumZach = std::move(NumZach_);
        this->KolDis = KolDis_;
        this->marks = marks_;
    }

    bool sucsess() const
    {

        bool flag;
        for (int i = 0; i < KolDis; i++) {
            if (marks[i] < 3)
            {
                flag = false;
                break;
            } else {
                flag = true;
            }
        }
        return flag;
    }
    bool otl() const
    {
        bool res = true;
        for (int i = 0; i < KolDis; i++) {
            if (marks[i] < 5) {
                res = false;
            }
        }
        return res;
    }

    int getMark(int n) const
    {
        if (n >= 0 && n < KolDis) {
            return marks[n];
        } else
        {
            cout << "enter normal number dis" << endl;
        }
    }
    string getName() const { return Name; }
    string getNumZnach() const { return NumZach; }
    int getKolDis() const { return KolDis; }

    double midlemark() const
    {
        double sum = 0;
        double res = 0;
        for (int i = 0; i < KolDis; i++) {
            sum += marks[i];
        }
        res = sum/KolDis;
        return res;
    }

    void reName (string Name_)
    {
        this->Name = std::move(Name_);
    }
    void reKolDis (int KolDis_)
    {
        this->KolDis = KolDis_;
    }
    void reNumZach (string NumZach_)
    {
        this->NumZach = std::move(NumZach_);
    }
    void remarks (int* marks_)
    {
        this->marks = marks_;
    }

    ~Student()
    {
        cout << "~Student() " << KolDis << endl;
        if (marks != nullptr) {
            delete[] marks;
        }
    }

    Student operator = (Student &S)
    {

        if (this != &S) {
            swap(Name, S.Name);
            swap(NumZach, S.NumZach);
            swap (KolDis, S.KolDis);
            swap(marks, S.marks);
        }
        return *this;

    }
    bool operator < (const Student &S) const
    {

        return Name < S.Name;

    }
    bool operator==(const Student& other) const
    {

        return Name == other.Name && NumZach == other.NumZach;

    }
    friend ostream& operator << (ostream &os, const Student & S);
    friend istream& operator >> (istream &os, Student & S);

};

class InvalidStudent : public invalid_argument
{

    string Name;
    string NumZach;
    int KolDis;
    int *marks;

public:

    InvalidStudent(string Name_, string NumZach_, int KolDis_, int* marks_) : invalid_argument("Invalid NumZach"),
    Name(Name_), NumZach(NumZach_), KolDis(KolDis_), marks(marks_) {}

    void printInvalid() const
    {

        cout << "name:" << Name << ", NumZach:" << NumZach << ", KolDis:" <<
        KolDis << ", marks: " << endl;

        for (int i = 0 ; i < KolDis; i++)
        {
            cout << marks[i] << " ";
        }

    }

};



struct MyHash {
    size_t operator()(const Student& S) const
    {

        int p = 31;
        unsigned long long hash = 0;
        hash = hash * p + std::hash<string>()(S.getName());
        hash = hash * p + std::hash<string>()(S.getNumZnach());
        hash = hash * p + std::hash<int>()(S.getKolDis());
        hash = hash * p + std::hash<double>()(S.midlemark());
        return static_cast<size_t>(hash);

    }
};

#endif