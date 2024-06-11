#include <iostream>
#include <cmath>
using namespace std;
bool is_prime(int n);
int main()
{
	char a[110];
	int x[26]={0};
	cin>>a;
	for (int i=1;a[i]!='\0';i++)
	x[a[i]-'a']++;
	int max=0,min=110,cha;
	for (int i=0;i<26;i++)
	{
		if (x[i]>max) max=x[i];
		if (x[i]<min&&x[i]!=0) min=x[i];
	}
	cha=max-min;
	if (is_prime(cha)&&cha!=1&&cha!=0)
	{
	 cout<<"Lucky Word"<<endl;
	 cout<<max-min;
}
	else
	{
		cout<<"No Answer"<<endl;
		cout<<"0";
}
	return 0;
}
bool is_prime(int n)
{
	if (n=2) return true;
	else
	{
	for (int i=n;i>1;i--)
	if (n%i==0) return false;
	else return true;
}
}
