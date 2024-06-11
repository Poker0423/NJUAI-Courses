#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char s[14],c;
	cin>>s;
	int h=0,k=0;
	for(int i=0;i<11;i++)
	{
		if(s[i]!='-')
		{
			k++;
			h+=k*(s[i]-'0');//-0是为了将字符串变成普通数字
		}
	}
	h%=11;
	if(h==10) c='X';
	else c=h+'0';
	if(c==s[12]) cout<<"Right"<<endl;
	else
	{
		s[12]=c;
		cout<<s;
	}
	return 0;
}
