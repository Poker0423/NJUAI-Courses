#include <iostream>//n个数中找最大与第n个交换，如此重复 
using namespace std;
void sel_sort(int x[],int n)
{
	for (;n>1;n--)
	{
		int i_max=0;
		for (int i=1;i<n;i++)
		if (x[i]>x[i_max])
		i_max=i;
		int temp=x[i_max];
		x[i_max]=x[n-1];//n-1是最后一个数 
		x[n-1]=temp;
	}
}
const int n=10;
int main()
{
	int a[n],i;
	for (i=0;i<n;i++)
	cin>>a[i];
	sel_sort(a,n);
	for (i=0;i<n;i++)
	cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
