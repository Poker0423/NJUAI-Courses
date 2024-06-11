#include <iostream>
using namespace std;
int main()
{
	char a[100];//必须注明字符数组的大小 
	cin>>a;
	int num=0,ans=0;
	for (int i=0;a[i]!='\0';i++)
	num++;
	if (num%2==0)
	{
		for (int i=0;i<num;i++)
		{
			if (a[i]==a[num-1-i])
			ans=1;	
		}
	}
	else
	{
		for (int i=0;i<(num-1)/2;i++)
		{
			if (a[i]==a[num-1-i])
			ans=1;	
		}
	}
	if (ans==1) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
	return 0;
}
