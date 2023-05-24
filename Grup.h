#ifndef HW3_GRUP_H
#define HW3_GRUP_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <mutex>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Grup {

    string NameGrup;
    int KolStudents;
    string Facultet;
    mutex mutex_;
    unordered_set<Student, MyHash> p;

public:

    Grup()
    {

        lock_guard<mutex> lock(mutex_);
        NameGrup = "";
        KolStudents = 0;
        Facultet = "";
        p.clear();

    }
    Grup(string NameGrup, int KolStudents, string Facultet, unordered_set<Student, MyHash> &t)
    {

        lock_guard<mutex> lock(mutex_);
        this->NameGrup = NameGrup;
        this->KolStudents = KolStudents;
        this->Facultet = Facultet;
        p.clear();
        for(std::unordered_set<Student, MyHash>::iterator it = t.begin(); it != t.end(); it++) {
            p.insert(*it);
        }

    }

    void setGrup(string NameGrup, int KolStudents, string Facultet, unordered_set<Student, MyHash> &t)
    {

        lock_guard<mutex> lock(mutex_);
        this->NameGrup = NameGrup;
        this->KolStudents = KolStudents;
        this->Facultet = Facultet;
        p.clear();
        for(std::unordered_set<Student, MyHash>::iterator it = t.begin(); it != t.end(); it++) {
            p.insert(*it);
        }

    }
    void setNameGrup(string NameGrup)
    {

        lock_guard<mutex> lock(mutex_);
        this->NameGrup = NameGrup;

    }
    void setKolStudents(int KolStudents) \
    {

        lock_guard<mutex> lock(mutex_);
        this->KolStudents = KolStudents;

    }
    void setFacultet(string Facultet)
    {

        lock_guard<mutex> lock(mutex_);
        this->Facultet = Facultet;

    }

    string getNameGrup() const { return NameGrup; }
    string getFacultet() const { return Facultet; }
    int getKolStudents() const { return KolStudents; }
    Student getStudent(string name)
    {

        lock_guard<mutex> lock(mutex_);
        for (unordered_set<Student, MyHash>::iterator it = p.begin(); it != p.end(); it++) {
            if (it->getName() == name)
            {
                return *it;
            }
        }

    }
    unordered_set<Student, MyHash> getp()
    {

        lock_guard<mutex> lock(mutex_);
        return p;

    }

    Student stringDel(string str)
    {
        istringstream ss(str);
        vector<string> v;

        string word;
        while (ss >> word)
        {
            v.push_back(word);
        }

        int* marks = new int[stoi(v[2])];
        for(int i = 0 ;i < stoi(v[2]); i++)
        {
            marks[i] = stoi(v[i+3]);
        }

        Student S(v[0], v[1], stoi(v[2]), marks);

        delete[] marks;
        return S;
    }

    double MidleOfGrup()
    {

        lock_guard<mutex> lock(mutex_);
        double sum = 0;
        double res;
        for (unordered_set<Student>::iterator it = p.begin(); it != p.end(); it++) {
            sum += it->midlemark();
        }
        res = sum/KolStudents;
        return res;

    }
    double MidleDis(int n)
    {

        lock_guard<mutex> lock(mutex_);
        double sum = 0;
        double res;
        for (unordered_set<Student>::iterator it = p.begin(); it != p.end(); it++) {
            sum += it->getMark(n);
        }
        res = sum/KolStudents;
        return res;

    }
    void PrintOtl()
    {

        cout << getNameGrup() << "отличники: " << endl;
        lock_guard<mutex> lock(mutex_);
        for (unordered_set<Student>::iterator it = p.begin(); it != p.end(); it++) {
            if (it->otl()) {
                cout << it->getName() << " ";
            }
        }
        cout << endl;

    }
    void PrintZad()
    {

        cout << getNameGrup() << "должники: " << endl;
        lock_guard<mutex> lock(mutex_);
        for (unordered_set<Student>::iterator it = p.begin(); it != p.end(); it++)
        {
            if (!it->sucsess()) {
                cout << it->getName() << " ";
            }
        }
        cout << endl;

    }
    void PrintGrup()
    {

        lock_guard<mutex> lock(mutex_);
        string output = "C:\\Users\\28218\\CLionProjects\\hw3\\output.txt";
        ofstream out(output);
        out << NameGrup << endl << Facultet << endl << KolStudents << endl;
        for (unordered_set<Student, MyHash>::iterator it = p.begin(); it != p.end(); it++) {
            out << *it << " ";
        }
        out << endl;

    }
    void ScanGrup()
    {

        lock_guard<mutex> lock(mutex_);

        int k = 0;

        string input = "C:\\Users\\28218\\CLionProjects\\hw3\\input.txt";
        ifstream in(input);
        if (in.is_open())
        {

            string str;

            while(getline(in, str))
            {

                k++;
                switch (k)
                {

                    case 1:
                    {
                        NameGrup = str;
                        break;
                    }
                    case 2:
                    {
                        KolStudents = stoi(str);
                        break;
                    }
                    case 3:
                    {
                        Facultet = str;
                        break;
                    }
                    case 4:
                    {
                        p.insert(stringDel(str));
                    }

                }

            }

        }

    }

    Grup& operator = (Grup &G1)
    {

        lock_guard<mutex> lock(mutex_);
        if (this != &G1)
        {
            swap(NameGrup, G1.NameGrup);
            swap(Facultet, G1.Facultet);
            swap(KolStudents, G1.KolStudents);
            swap(p, G1.p);
        }
        return *this;

    }
    Grup& operator = (const Grup& G1)
    {

        lock_guard<mutex> lock(mutex_);
        if (this != &G1)
        {
            KolStudents = G1.KolStudents;
            Facultet = G1.Facultet;
            NameGrup = G1.NameGrup;
            if (this != &G1) {
                p.clear();
            }
            for (unordered_set<Student, MyHash>::const_iterator it = G1.p.begin(); it != G1.p.end(); it++) {
                p.insert(*it);
            }
        }
        return *this;

    }

    ~Grup()
    {

        lock_guard<mutex> lock(mutex_);
        cout << "Grup() " << NameGrup << endl;
        if (p.size() == 0)
        {
            p.clear();
        }

    }

    friend ostream& operator << (ostream &os, Grup & G);
    friend Grup& operator + (Grup &G, Student &S);

};

#endif