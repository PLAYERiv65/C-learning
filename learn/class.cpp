#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
int test(int a,int b);
int test(int &a,int &b);
class People{
private:
    char *m_name;
public:
    People(char *name);
    ~People();
    char* getname();
};
People::People(char *name)
{
    m_name = new char [strlen(name) + 1];
    strcpy(m_name,name);
}
People::~People()
{
    delete m_name;
    m_name = NULL;
}
char* People::getname()
{
    return m_name;
}
class Student :protected People{
private:
    int *m_score;
    char *m_ID;
public:
    Student(char *name,int score,char *id);
    ~Student();
    void setscore(int score);
    void setID(char *id);
    void show();
};
Student::Student(char *name,int score,char *id):People(name)
{
    m_score = new int;
    *m_score = score;
    m_ID = new char [strlen(id) + 1];
    strcpy(m_ID,id);
}
void Student::setscore(int score)
{
    *m_score = score;
}
void Student::setID(char *id)
{
    delete m_ID;
    m_ID = new char [strlen(id) + 1];
    strcpy(m_ID,id);
}
void Student::show()
{
    cout<<"姓名："<<getname()<<endl;
    cout<<"学号："<<m_ID<<endl;
    cout<<"成绩："<<*m_score<<endl;
}
Student::~Student()
{
    delete m_score;
    m_score = NULL;
    delete m_ID;
    m_ID = NULL;
}
int main()
{
    Student *stuA = new Student("学生甲",98,"2023211700");
    char sid[20] = "2023211700",iid[20];
    cout<<"请输入学号："<<endl;
    cin>>iid;
    if(strcmp(sid,iid))
    {
        cout<<"学号错误！"<<endl;
        return 0;
    }
    stuA->show();
    cout<<"是否更改成绩? Y\\N"<<endl;
    char c;
    cin>>c;
    if(c == 'N')
    {
        cout<<"祝您生活愉快！"<<endl;
        return 0;
    }
    if(c == 'Y')
    {
        cout<<"请输入原因："<<endl;
        char reason[100];
        cin>>reason;
        cout<<"审核中......"<<endl;
        _sleep(10000);
        stuA->setscore(100);
        cout<<"修改完成！"<<endl;
        stuA->show();
    }
    delete stuA;
    return 0;
}