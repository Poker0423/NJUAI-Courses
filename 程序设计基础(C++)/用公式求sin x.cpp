#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
double sin(double x,int n)
{
    double item=x,sum=x;
    int i=2;
    for(i=2;i<=n;i++)
     {   
        item *=x*x/((2*i-1)*(2*i-2));//用叠加实现阶乘的增加 
        if(i%2==1)
        {
            
            sum +=item;
        }
        else if(i%2==0)
        {
            
            sum -=item;
        }
     }
     return sum;
}
int main()
{
   double x;
   int n;
   cout<<"Please input x and n";
   cin>>x>>n;
   cout<<setiosflags(ios::fixed)<<setprecision(4);
   cout<<sin(x,n)<<endl;
  return 0;
}
