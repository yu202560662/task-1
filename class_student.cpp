#include<iostream>
using namespace std;
#include<string>
class Student
{private:
    string name;
    string id;
    int numscore;
    int cap;
    int*score_list;
public:
    Student(string n,string m,int arr[]):numscore(3),cap(4)
    {   name=n;
        id=m;
        
        score_list=new int[cap];
        for(int i=0;i<numscore;i++)
        {score_list[i]=arr[i];}
 };
    void expand()
    {   
        cap=cap*2;
        int newcap=cap;
        int*newscore_list=new int[newcap];
            for(int i=0;i<numscore;i++)
            {newscore_list[i]=score_list[i];}
            delete []score_list;
            score_list=newscore_list;
            cap=newcap;
  }
    void add(int idex,int score)
    {   
        if (numscore>=cap)
    {
        expand();
    }
    else
    {score_list[idex-1]=score;
    if (idex>numscore)
    {numscore++;}

    }
}
void student_print()
{
cout<<"姓名:"<<name<<"学号:"<<id<<"成绩:";
for (int k=0;k<numscore;k++)
{cout<<score_list[k]<<"\t";
}
cout<<endl;
}
Student(const Student &s)
{
    name=s.name;
    id=s.id;
    numscore=s.numscore;
    cap=s.cap;
    score_list=new int[cap];
    for(int i=0;i<numscore;i++)
    {
        score_list[i]=s.score_list[i];
    }
}
~Student()
{delete []score_list;}
};
int main()
{   int scores1[]={85,90,78};
    Student s1("张三", "2025001", scores1);
    s1.student_print();
    Student s2(s1);
    s2.add(1, 88);
    s2.student_print();

    
    

    
    return 0;}