#include<bits/stdc++.h>
using namespace std;
string s,ch;
int main()
{
    cout<<"�������ַ�����";
    cin>>s;
    while(1)
    {
        cout<<"������һ��Ӣ����ĸ��";
        cin>>ch;
        if(ch.length()>1 || !((ch[0]>='A' && ch[0]<='Z') || (ch[0]>='a' && ch[0]<='z')))
        {
            cout<<"�Ƿ�������"<<endl;
            continue;
        }
        break;
    }
    int l = s.length();
    for(int i=0;i<l;i++)
    {
        if(s[i] != ch[0]) cout<<s[i];
    }
    return 0;
}