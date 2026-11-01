#include<iostream>
#include<string>
using namespace std;
int main()
{
    cout<<"输入:"; 
    string st;
    getline(cin,st);
    cout<<"输出:"<<st<<endl;
    int len=st.length();
    int num=1;
    for(int i=0;i<len;i++)
    {if (st[i]==' ')
    {num++;}
    }
    cout<<"单词个数:"<<num<<endl;
    cout<<"逆序输出:";
    for(int i=0;i<len;i++)
    {cout<<st[len-1-i];}
    cout<<endl;
    return 0;
}