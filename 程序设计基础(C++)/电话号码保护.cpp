#include <iostream>
#include <cstring>
using namespace std;
int main()
{	
	string s;
	cin>>s;
	for (int i=0;i<=10;i++)
		if (i>=3&&i<=6)
		cout<<'*';
		else
		cout<<s[i];
return 0;
}
