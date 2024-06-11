#include<bits/stdc++.h>
using namespace std;
int main()
{
	const int M=2,N=3,T=4;
	int a[M][N],b[N][T],c[M][T];
	int i,j,k;
	for (i=0;i<M;i++)
	  for (j=0;j<N;j++)
	    cin>>a[i][j];
	for (i=0;i<N;i++)
	  for (j=0;j<T;j++)
	    cin>>b[i][j];
	for (i=0;i<M;i++)
	{
		for (j=0;j<T;j++)
		{
			c[i][j]=0;
			for (k=0;k<N;k++)
			  c[i][j]+=a[i][k]*b[k][j];
		}
	}
	for (i=0;i<M;i++)
	{
		for (j=0;j<T;j++)
	    cout<<c[i][j]<<" "; 
	    cout<<endl; 
	}   
	return 0;
}

