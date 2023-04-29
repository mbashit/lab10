// lab10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*11. ��������� ������� � ��������� ���� ������ �� ����� student.dat ,
�������� ������� ������� �������� �� ��������� ����, ������ ������ �
��������� 4 �����.*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Exam
{
    string subject;
    int grade;
};

enum Mode
{
    FullTime,
    PartTime
};

struct Student
{
    string surname;
    string middleName;
    string firstName;
    int course;
    int group;
    int* rating;
    Mode mode;
    Exam exam;
};

Student* createStudent();
void writeToDatFile(Student* students, int size);
Student* readFromfile(int size);
void writeToTextFile(Student* students, int size);

int main()
{
    Student* students = createStudent();

    int size = 5;
    writeToDatFile(students, size);

    Student* newStudents = readFromfile(size);

    int removed = 0;
    for (int i = 0; i < size; i++)
    {
        if (newStudents[i].course == 4)
        {
            removed++;
            if (i == size - 1)
            {
                break;
            }
            for (int j = i + 1; j < size; j++)
            {
                newStudents[j - 1] = newStudents[j];
            }
        }
        else
        {
            newStudents[i].course++;
        }
    }

    writeToTextFile(newStudents, size - removed);

    return 0;
}

void writeToDatFile(Student* students, int size)
{
    ofstream studentWriter;
    studentWriter.open("student.dat", ios::out | ios::binary);

    studentWriter.write((char*)&students, size);

    studentWriter.close();
}

void writeToTextFile(Student* students, int size)
{
    ofstream studentWriter;
    studentWriter.open("student.txt");

    for (int i = 0; i < size; i++)
    {
        studentWriter << students[i].surname << " " << students[i].middleName << " " << students[i].firstName << "\n"
            << students[i].course << "\n"
            << students[i].group << "\n";

        for (int j = 0; j < 10; j++)
        {
            studentWriter << students[i].rating[j] << " ";
        }

        studentWriter << "\n";

        studentWriter << students[i].mode << "\n"
            << students[i].exam.subject << "\n"
            << students[i].exam.grade << "\n";
    }

    studentWriter.close();
}

Student* createStudent()
{
    Student* students;
    Exam exam;

   Student student1 {
        "John",
        "Smith",
        "Emma",
        2,
         24,
        new int[10] {5, 4, 4, 5, 5, 5, 4, 4, 4, 3},
        FullTime,
        {
            exam.subject = "Maths",
            exam.grade = 5} };
    Student student2 {
        "Johnson",
        "David",
        "Sophie",
        1,
        32,
        new int[10] {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        PartTime,
        {
            exam.subject = "English",
            exam.grade = 4} };
    Student student3 { 
        "Brown",
        "Oliver",
        "Lily",
        3,
        18,
        new int[10] {5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        FullTime,
        {
             "History",
             5} };
    Student student4 = {
        "Davis",
        "Ethan",
        "Ava",
        2,
        27,
        new int[10] {4, 4, 4, 4, 5, 5, 5, 5, 5, 5},
        PartTime,
        {
            exam.subject = "Biology",
            exam.grade = 4} };
    Student student5 = {
        "Miller",
        "Lucas",
        "Emily",
        4,
        12,
        new int[10] {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        FullTime,
        {
            exam.subject = "Chemistry",
            exam.grade = 3} };

    students = new Student[5]{student1};

    return students;
}

Student* readFromfile(int size)
{
    ifstream studentReader;
    studentReader.open("student.dat", ios::in | ios::binary);

    string surname, middleName, firstName, subject;
    int course, group, mode, grade;
    int* rating = new int[10];

    Student* students = new Student[size];

    studentReader.read((char*)&students, size);

    return students;
}