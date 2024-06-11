#include<iostream>
using namespace std;
int main()
{
   int n;
   cin>>n;
   int i=1;
   int m=0,k,p,s=0;
   for(i=1;i<=n;i++)
   {
   	  for(p=1;p<=10;p++)
   	  {
   	  	cin>>k;
   	  	
   	  	if(k==1)m++;
	  }
	  if (m!=0)s++;
	  m=0;
   }
    cout<<s;
    return 0;
}

