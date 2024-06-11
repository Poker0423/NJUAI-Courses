#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[1001],n,i,j;
	double ans;
	cin>>n;
	for (i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	for (j=2;j<=(n-1);j++)
	ans+=a[j];
	ans=ans/(n-2);
	cout << fixed << setprecision(2) <<ans;
return 0;
}
