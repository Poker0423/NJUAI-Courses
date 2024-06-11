#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a[1002]={0},i=1;
    cin>>n;
    while(n!=1)//重点
	{
		a[i]=n;
		i++;
		if(n%2==0) n/=2;
		else n=3*n+1;
	}
	a[i]=1;//开始准备输出
	for(int j=i;j>=1;j--)
	{
		cout<<a[j]<<' ';
	}
	return 0;
}
