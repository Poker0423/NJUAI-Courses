#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a[1002][4],sum[1002],cnt=0;
	cin>>n;
	for (int i=1;i<=n;i++){
	cin>>a[i][1]>>a[i][2]>>a[i][3];
	sum[i]=a[i][1]+a[i][2]+a[i][3];
	}
	for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++)
		if (abs (a[i][1] - a[j][1]) <= 5 && 
				abs (a[i][2] - a[j][2]) <= 5 && 
				abs (a[i][3] - a[j][3]) <= 5 && 
				abs (sum[i] - sum[j]) <= 10)
		cnt++;
	cout<<cnt;
    return 0;
}
