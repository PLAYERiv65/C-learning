#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
class Student{
private:
    char *school;
    string name;
    int age;
public:
    Student(char *school,string name,int age);
    ~Student();
    void Print();
};
class C_Student:public Student{
private:
    string teacher;
    int score;
public:
    C_Student(char *school,string name,int age,string teacher,int score);
    ~C_Student();
    void Print();
};
Student::Student(char *school, string name, int age)
{
    this->school = new char [strlen(school) + 10];
    strcpy(this->school, school);
    this->name = name;
    this->age = age;
}

C_Student::C_Student(char *school, string name, int age, string teacher, int score):Student(school, name, age)
{
    this->teacher = teacher;
    this->score = score;
}

Student::~Student()
{
    delete[] school;
    school = NULL;
}

C_Student::~C_Student()
{
    teacher = "";
}

void Student::Print()
{
    cout << school << "大学的" << name << "年龄是" << age <<"，";
}

void C_Student::Print()
{
    Student::Print();
    cout << "课程老师是" << teacher << "，课程成绩是" << score << "。";
}

int main()
{
    int a, s;
    char sch[20];
    string nam, tea;
    cin >> sch >> nam >> a >> tea >> s;
    C_Student stu(sch, nam, a, tea, s);
    stu.Print();
    return 0;
}