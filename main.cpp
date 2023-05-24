#include <iostream>
#include "Student.h"
#include "Grup.h"
#include <unordered_set>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

istream& operator >> (istream &os, Student & S)
{
    if (!os){
        return os;
    }
    cout << "Enter Name: ";
    os >> S.Name;
    cout << "Enter NumZach: ";
    os >> S.NumZach;
    cout << "Enter KolDis: ";
    os >> S.KolDis;
    delete [] S.marks;
    S.marks = new int [S.KolDis];
    cout << "Enter " << S.KolDis << "marks: " << endl;
    for (int i = 0; i < S.KolDis; i++) {
        os >> S.marks[i];
    }
    return os;
}
ostream& operator << (ostream &os, const Student &S)
{
    os << S.Name << endl << S.NumZach <<
       endl << S.KolDis << endl;
    for (int i = 0; i < S.KolDis; i++)
    {
        os << S.marks[i] << " ";
    }
    os << endl;
    return os;
}
ostream& operator << (ostream &os, Grup &G)
{
    lock_guard<mutex> lock(G.mutex_);
    os << G.NameGrup << endl << G.Facultet << endl << G.KolStudents << endl;
    for (unordered_set<Student, MyHash>::iterator it = G.p.begin(); it != G.p.end(); it++) {
        os << *it << " ";
    }
    os << endl;
    return os;
}
Grup& operator + (Grup &G, Student &S) {
    lock_guard<mutex> lock(G.mutex_);
    G.p.insert(S);
    G.KolStudents++;
    return G;
}

void printGrup(Grup& G)
{

    G.PrintGrup();

}
void scanGrup(Grup* G)
{

    G->ScanGrup();

}


int main(int argc, char **argv) {


    system("chcp 65001");//меняем кодировку файла, чтоб был русский язык
    if (argc != 1) {
        cout << "введите правильное колличество аргументов" << endl;
    } else {

        //обьявляем студента и группу
        Grup G;
        Student S;


        //поток для ввода данных
        //thread thread2(scanGrup, &G);


        // добавляем немного студентов в группу
        G.setFacultet("IU8");

        int marks1[3] = {3, 4, 2};
        int marks2[2] = {4, 5};
        Student S_0 = {"vlad", "22y555", 3, marks1};
        Student S_1 = {"igor", "24t555", 2, marks2};
        G = G + S_0;
        G = G + S_1;

        cout << G;

        // ловим ошибку


        try {

            int arr[2] = {1, 2};
            Student S1("vlad", "23r", 2, arr);

        }
        catch (InvalidStudent &I) {
            I.printInvalid();
        }


        // поиск студента по имени
        /*string name;
        cout << "введите имя для поиска студента " << endl;
        cin >> name;
        Student S1 = G.getStudent(name);
        cout << S1;*/


        // изменение данных студента
        /*string name_, NumZach;
        int KolDis;
        cout << "введите имя, номер зачетки и количество предметов " << endl;
        cin >> name_ >> NumZach >> KolDis;
        int arr[KolDis];

        for (int i = 0; i < KolDis; i++)
        {
            cout << "введите оценку№ " << i+1 << endl;
            cin >> arr[i];
        }

        S.reName(name_);
        S.reNumZach(NumZach);
        S.reKolDis(KolDis);
        S.remarks(arr);

        cout << S;*/

        //использование методов группы
        /*cout << G.MidleOfGrup() << endl;
        cout << G.MidleDis(0) << endl;
        cout << G.getFacultet() << endl;
        cout << G.getKolStudents() << endl;
        G.PrintOtl();
        G.PrintZad();*/


        // создание потока для вывода группы
        /*thread thread1(printGrup, ref(G));


        thread2.join();
        thread1.join();*/

    }
    return 0;
}
