
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

enum Specialty { КН, ІН, МЕ, ФІ, ТН };
string specialtyStr[] = { "КН", "ІН", "МЕ", "ФІ", "ТН" };

struct Student
{
    char Surname[99];
    short unsigned course;
    Specialty specialty;
    short unsigned physics;
    short unsigned mathematics;
    short unsigned informatics;
};

void EnterSave(char* fname);
void LoadPrint(char* fname);
void CountMarks(char* fname, int& countInformatics5, int& countInformatics4, int& countInformatics3);
void Physics_Math(char* fname, int& Procent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    char ch;
    int r = 0;
    int countInformatics = 0;
    int countPhysics = 0;
    int countMath = 0;

    do
    {
        cout << "1. Заповнити дані\n"
            << "2. Вивести на екран дані\n"
            << "3. Кількість студентів з оцінками 5 з фізики та математики\n"
            << "4. Кількість оцінок відмінно з кожного предмету:\n"
            << "0. Завершити роботу програми\n\n";
        cout << "Виберіть дію:\n"; cin >> ch; cout << "\n";
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 100);
            EnterSave(fname);
            cout << "\n\n";
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            LoadPrint(fname);
            cout << "\n\n";
            break;
        case '3':
            Physics_Math(fname, r);
            cout << "5 з фізики та математики: " << r << "\n";
            cout << "\n\n";
            break;
        case '4':
            CountMarks(fname, countInformatics, countPhysics, countMath);
            cout << "Кількість оцінок 5 з інформатики: " << countInformatics << "\n";
            cout << "Кількість оцінок 5 з фізики: " << countPhysics << "\n";
            cout << "Кількість оцінок 5 з математики: " << countMath << "\n";
            cout << "\n\n";
            break;
        default:
            cout << "Нерозпізнана команда!\n\n";
        }
    } while (ch != '0');

    system("pause");
    return 0;
}

void EnterSave(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    int specialty;
    char ch;
    int i = 0;
    do
    {
        cout << "Студент №" << i + 1 << ":\n";
        i++;
        cin.sync();
        cout << "Прізвище: "; cin >> student.Surname;
        cout << "Курс: "; cin >> student.course;
        cout << "Спеціальність (КомпНауки - 0, Інформатика - 1, Математика та економіка - 2, Фізика та інформатика - 3, Трудове навчання - 4): ";
        cin >> specialty;
        student.specialty = (Specialty)specialty;
        cout << "Оцінка з фізики: "; cin >> student.physics;
        cout << "Оцінка з математики: "; cin >> student.mathematics;
        cout << "Оцінка з інформатики: "; cin >> student.informatics; cout << "\n";

        if (!f.write((char*)&student, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу" << endl;
        }
        cout << "Введіть \'y\', щоб продовжити введення:\n\n "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Не вдалося відкрити файл \'" << fname << "'" << endl;
        return;
    }

    Student student;
    int i = 0;

    cout << "+-----------------------------------------------------------------------------------------------------------+"
        << "\n";
    cout << "| № |     прізвище | курс |    спец.   | фіз. | мат. | інф. | "
        << "\n";
    cout << "+-----------------------------------------------------------------------------------------------------------+"
        << "\n";

    while (f.read((char*)&student, sizeof(Student)))
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(13) << right << student.Surname
            << "| " << setw(4) << right << student.course << " "
            << "| " << setw(6) << right << specialtyStr[student.specialty] << " " << setw(6)
            << "| " << setw(4) << right << student.physics << " "
            << "| " << setw(4) << right << student.mathematics << " "
            << "| " << setw(4) << right << student.informatics << " " << "|";
        cout << endl;

        cout << "+-----------------------------------------------------------------------------------------------------------+"
            << "\n";
        ++i;
    }
}

void CountMarks(char* fname, int& countInformatics5, int& countInformatics4, int& countInformatics3)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;

    while (f.read((char*)&student, sizeof(Student)))
    {
        if (student.informatics == 5)
            countInformatics5++;
        if (student.physics == 5)
            countInformatics4++;
        if (student.mathematics == 5)
            countInformatics3++;
    }
}

void Physics_Math(char* fname, int& r)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cout << "Не вдалося відкрити файл \'" << fname << "\'\n";
        return;
    }

    Student student;
    int NumberOfStudents = 0;
    int kilkist = 0;
    while (f.read((char*)&student, sizeof(Student)))
    {
        if ((student.physics == 5 && student.mathematics == 5))
            r++;
    }
}