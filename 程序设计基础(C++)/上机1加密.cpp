#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	char ch[100];
	for (int i=0;i<n;i++) 
	{
		cin>>ch[i];
		if (ch[i]>'a'&&ch[i]<'z')
		{
			ch[i]=ch[i]+m;
			if (ch[i]>'z')
			ch[i]=ch[i]-26;
		}
		if (ch[i]>'A'&&ch[i]<'Z')
		{
			ch[i]=ch[i]+m;
			if (ch[i]>'z')
			ch[i]=ch[i]-26;
		}
	}
	for (int i=0;i<n;i++)
	cout<<ch[i]; 
	return 0;
}
