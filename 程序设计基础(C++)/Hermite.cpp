#include <iostream>
using namespace std;
int hermite(int n,int x);
int main()
{
	int n,x;
	cin>>n>>x;
	if(n<0) return -1;
	cout<<hermite(n,x);
	return 0;
}
int hermite(int n,int x)
{

	if(n=0) return 1;
	else if(n=1) return 2*x;
	else return 2*x*hermite(n-1,x)-2*(n-1)*hermite(n-2,x);
}
