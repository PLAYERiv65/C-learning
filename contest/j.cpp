#include<bits/stdc++.h>
using namespace std;
bool dc(char a,char b)
{
    if(int(a)>int(b)) swap(a,b);
    if(a==b && (a=='A'||a=='H'||a=='I'||a=='M'||a=='O'||a=='o'||a=='T'||a=='U'||a=='V'||a=='v'||a=='W'||a=='w'||a=='X'||a=='x'||a=='Y'))
    {
        return 1;
    }
    if((a=='b'&&b=='d')||(a=='p'&&b=='q'))
    {
        return 1;
    }
    return 0;
}
bool zdc(char a)
{
    if(a=='A'||a=='H'||a=='I'||a=='M'||a=='O'||a=='o'||a=='T'||a=='U'||a=='V'||a=='v'||a=='W'||a=='w'||a=='X'||a=='x'||a=='Y')
    {
        return 1;
    }
    return 0;
}
string s;
int main()
{
    cin>>s;
    int l = s.length();
    if(l&1)
    {
        if(!zdc(s[l>>1]))
        {
            goto bbb;
        }
        for(int i=(l>>1)-1;i>=0;i--)
        {
            if(!dc(s[i],s[l-i-1])) goto bbb;
        }
    }
    if(!(l&1))
    {
        for(int i=(l>>1)-1;i>=0;i--)
        {
            if(!dc(s[i],s[l-i-1])) goto bbb;
        }
    }
    cout<<"TAK";
    return 0;
    bbb:
    cout<<"NIE";
    return 0;
}