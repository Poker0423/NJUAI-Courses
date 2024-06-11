#include<bits/stdc++.h>
using namespace std;
bool is_wanshu(int n);
int main()
{
	int n;
	cin>>n; 
	for (int i=1;i<=n;i++)
	{
		if (is_wanshu(i))
		cout<<i;
	}
 	return 0;
}
bool is_wanshu(int n)
{
	int sum=0;
	for (int i=1;i<n;i++)
	{
		if (n%i==0)
		sum+=i;
	}
	if (sum==n)
	return true;
	else
	return false;
}
