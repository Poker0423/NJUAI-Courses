#include<iostream>
#include <cstring>
using namespace std;
int main()
{
	char s[25];//必须用25等数字规定字符数组的长度 
	int a=0,b=0,c=0,num=0;
	cin>>s;
	for (int i=0;s[i]!='\0';i++)
	{
		num++;
		if (('a'<=s[i]&&'z'>=s[i])||('A'<=s[i]&&'Z'>=s[i]))
		a++;
		else if ('0'<=s[i]&&'9'>=s[i]) 
		b++;
		else c++; //考虑输入不合规的情况 
	}
	if (num>=8&&a>=1&&b>=1&&c==0)
	cout<<"valid";
	else 
	cout<<"invalid";	
	return 0;
}
