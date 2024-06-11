#include<iostream>
using namespace std;
void swap(int *px,int *py)
{
	int t=*px;
	*px=*py;
	*py=t;
}
int main()
{
	int a=0,b=1;
	swap(&a,&b);
	cout<<a<<" "<<b<<endl;
	return 0;
}
