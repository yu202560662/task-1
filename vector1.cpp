#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<algorithm>
int main()
{   
    vector<int> v;
    v.push_back(5);
    v.push_back(3);
    v.push_back(1); 
    v.push_back(2);
    v.push_back(1);
    cout<<"输出:";
    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    {
        cout<<*it<<" ";
    
    }
    cout<<endl;
    cout<<"排序输出:";
    sort(v.begin(),v.end());
    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"去重输出:";
    set<int> s(v.begin(),v.end());
     for(set<int>::iterator it1=s.begin();it1!=s.end();it1++)
    {
        cout<<*it1<<" ";
    }
    return 0;
}