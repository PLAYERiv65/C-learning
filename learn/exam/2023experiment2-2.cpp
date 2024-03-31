#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
bool flag;
bool legal(string s)
{
    //前导0
    if(s[0]=='0' && s.length()>1) return 0;
    //[0,255]
    if(s.length()>3) return 0;
    int num = 0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]<'0' || s[i]>'9') return 0;
        num = num*10 + s[i]-'0';
    }
    if(num>255) return 0;
    return 1;
}
void out(bool o)
{
    //if(!flag) flag = 1;
    //else cout<<endl;
    if(o) cout<<"IP合法"<<endl;
    else cout<<"IP不合法"<<endl;
}
int main()
{
    string ip;
    int d1,d2,d3;
    while(cin>>ip)
    {
        d1 = ip.find('.');
        d2 = ip.find('.',d1+1);
        d3 = ip.find('.',d2+1);
        if(ip.find('.',d3+1)!=-1 || d1==-1 || d2==-1 || d3==-1)
        {
            out(0);
            continue;
        }
        if(legal(ip.substr(0,d1)) && legal(ip.substr(d1+1,d2-d1-1)) && legal(ip.substr(d2+1,d3-d2-1)) && legal(ip.substr(d3+1,ip.length()-d3-1)))
        {
            out(1);
        }
        else out(0);
    }
    return 0;
}