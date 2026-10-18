#include <iostream>
using namespace std;
int main()
{
cout<<"九九乘法表:"<<endl;
int i,j;
for (size_t i = 1; i < 10; i++)
{
 for (size_t j = 1;  j<i+1 ;j++) 
 {cout <<i<<"*"<<j<<"="<<j*i<<"\t";}
 cout<<"\n";
}

return 0;

}
