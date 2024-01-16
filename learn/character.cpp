#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string school;
    string name;
    int age;

public:
    Student(string school, string name, int age);
    virtual ~Student();
    virtual void Print();
};

class C_Student : public Student {
private:
    string teacher;
    int score;

public:
    C_Student(string school, string name, int age, string teacher, int score);
    ~C_Student();
    void Print() override;
};

Student::Student(string school, string name, int age) : school(school), name(name), age(age) {}

C_Student::C_Student(string school, string name, int age, string teacher, int score)
    : Student(school, name, age), teacher(teacher), score(score) {}

Student::~Student() {}

C_Student::~C_Student() {}

void Student::Print() {
    cout << school << "大学的" << name << "年龄是" << age << "岁，";
}

void C_Student::Print() {
    Student::Print();
    cout << "课程老师是" << teacher << "，课程成绩是" << score << "。" << endl;
}

int main() {
    string sch, nam, tea;
    int a, s;
    cout << "请输入学校名，学生名，年龄，老师名和分数：" << endl;
    cin >> sch >> nam >> a >> tea >> s;
    C_Student stu(sch, nam, a, tea, s);
    stu.Print();
    return 0;
}