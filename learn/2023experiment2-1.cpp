#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
class Student{
public:
    string name;
    int num,score;
    Student(string name,int num,int score):name(name),num(num),score(score){}
    Student(){}
};
bool cmp(Student a,Student b)
{
    return a.score>b.score;
}
int main()
{
    const int n=8;
    Student stu[n];
    string name;
    int num,score;
    for(int i=0;i<n;i++)
    {
        cin>>name>>num>>score;
        stu[i] = Student(name,num,score);
    }
    sort(stu,stu+n,cmp);
    for(int i=0;i<n-1;i++)
    {
        cout<<stu[i].name<<" "<<stu[i].num<<" "<<stu[i].score<<endl;
    }
    cout<<stu[n-1].name<<" "<<stu[n-1].num<<" "<<stu[n-1].score;
    return 0;
}