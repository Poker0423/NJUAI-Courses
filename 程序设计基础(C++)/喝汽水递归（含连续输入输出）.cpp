#include <iostream>
using namespace std;
int f(int n)
{
	if (n==0||n==1){
		return 0;
	}
	else if (n==2){
		return 1;
	}
	else return f(n-2)+1;
}
int main()
{
	int a,b[100];
	int no;
	cin>>a;
	for (int i=0;a!=0;i++)
	{
		no=i;
		b[no]=f(a);
		cin>>a;//输入下一个数 
	}
	for (int i=0;i<no+1;i++)
	cout<<b[i]<<endl;
	return 0;	
}
