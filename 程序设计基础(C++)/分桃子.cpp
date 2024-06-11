#include <iostream>
using namespace std;
int f(int m,int n)
{
	if(m==0||n==1)//没苹果或一个盘 
	{
		return 1;
	}
	if (m<n)//盘子富余 
	{
		return f(m,m);
	}
	else{
		return f(m,n-1)+f(m-n,n);//先少一个盘，多出的情况就是保证每个盘都有苹果 
	}
}
int main()
{
	int m,n;
	cin>>m>>n;
	cout<<f(m,n);
	return 0;	
}
