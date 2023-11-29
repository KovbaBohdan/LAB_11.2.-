
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

enum Specialty { ��, ��, ��, Բ, �� };
string specialtyStr[] = { "��", "��", "��", "Բ", "��" };

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
        cout << "1. ��������� ���\n"
            << "2. ������� �� ����� ���\n"
            << "3. ʳ������ �������� � �������� 5 � ������ �� ����������\n"
            << "4. ʳ������ ������ ������ � ������� ��������:\n"
            << "0. ��������� ������ ��������\n\n";
        cout << "������� ��:\n"; cin >> ch; cout << "\n";
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "������ ��'� �����: "; cin.getline(fname, 100);
            EnterSave(fname);
            cout << "\n\n";
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "������ ����� ����� ��� ���������� �����: "; cin.getline(fname, 100);
            LoadPrint(fname);
            cout << "\n\n";
            break;
        case '3':
            Physics_Math(fname, r);
            cout << "5 � ������ �� ����������: " << r << "\n";
            cout << "\n\n";
            break;
        case '4':
            CountMarks(fname, countInformatics, countPhysics, countMath);
            cout << "ʳ������ ������ 5 � �����������: " << countInformatics << "\n";
            cout << "ʳ������ ������ 5 � ������: " << countPhysics << "\n";
            cout << "ʳ������ ������ 5 � ����������: " << countMath << "\n";
            cout << "\n\n";
            break;
        default:
            cout << "����������� �������!\n\n";
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
        return;
    }

    Student student;

    int specialty;
    char ch;
    int i = 0;
    do
    {
        cout << "������� �" << i + 1 << ":\n";
        i++;
        cin.sync();
        cout << "�������: "; cin >> student.Surname;
        cout << "����: "; cin >> student.course;
        cout << "������������ (��������� - 0, ����������� - 1, ���������� �� �������� - 2, Գ���� �� ����������� - 3, ������� �������� - 4): ";
        cin >> specialty;
        student.specialty = (Specialty)specialty;
        cout << "������ � ������: "; cin >> student.physics;
        cout << "������ � ����������: "; cin >> student.mathematics;
        cout << "������ � �����������: "; cin >> student.informatics; cout << "\n";

        if (!f.write((char*)&student, sizeof(Student)))
        {
            cerr << "������� �������� �����" << endl;
        }
        cout << "������ \'y\', ��� ���������� ��������:\n\n "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "�� ������� ������� ���� \'" << fname << "'" << endl;
        return;
    }

    Student student;
    int i = 0;

    cout << "+-----------------------------------------------------------------------------------------------------------+"
        << "\n";
    cout << "| � |     ������� | ���� |    ����.   | ���. | ���. | ���. | "
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
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
        cout << "�� ������� ������� ���� \'" << fname << "\'\n";
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