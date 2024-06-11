#include <iostream>
using namespace std;
int main()
{
	const int N=3;
	int a[N][N];
	int i,j;
	for (i=0;i<N;i++)
	for (j=0;j<N;j++)
	cin>>a[i][j];
	for (i=0;i<N;i++)
	for (j=i+1;j<N;j++)
	{
		int temp=a[i][j];
		a[i][j]=a[j][i];
		a[j][i]=temp;
	}
	for (i=0;i<N;i++){
	for (j=0;j<N;j++)
	cout<<a[i][j]<<" ";
	cout<<endl;
	}
	return 0;
}
