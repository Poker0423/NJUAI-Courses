#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int a[1000];
	cin>>n;
	for (int i=0;i<n;i++)
	cin>>a[i];
	sort (a,a+n);
	int m=unique(a,a+n)-a;
	cout<<m<<endl;;
	for (int i=0;i<m;i++)
	cout<<a[i]<<" ";
	return 0;
}

