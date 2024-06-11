#include <iostream>
#include <cmath>
using namespace std;
bool is_prime(int n);
int main()
{
	char a[100];
	int x[26]={0};//将所有字母数初始化为0 
	cin>>a;
	for (int i=1;a[i]!='\0';i++)
	x[a[i]-'a']++;//字符数组减'a'就与26个字母一一对应 
	int max=0,min=100,cha;//用不可能的值对最大值和最小值初始化，便于操作 
	for (int i=0;i<26;i++)
	{
		if (x[i]>max) max=x[i];
		if (x[i]<min&&x[i]!=0) min=x[i];//一个字母最少出现一次 
	}
	cha=max-min;
	if (is_prime(cha))
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
	for (int i=n-1;i>1;i--)
	if (n%i==0) return false;
	else return true;
}
}
