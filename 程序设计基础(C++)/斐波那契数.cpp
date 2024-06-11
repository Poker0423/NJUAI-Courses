#include<iostream>
using namespace std;
int main()
{
	int fibs[40];
	int n;
	cin>>n;
	fibs[0]=fibs[1]=1;
	for (int i=2;i<=n;i++)
	fibs[i]=fibs[i-1]+fibs[i-2];
	cout<<fibs[n-1]<<endl; 
	return 0;
}
