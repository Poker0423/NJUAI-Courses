#include<bits/stdc++.h>
using namespace std;
int main()
{
	char sen[100];
	int cnt=1,i=0;
	cin.getline(sen,100);
	while(sen[i]!='\0')
	{
	if (sen[i]==' ')
	cnt++;
	i++;
	}
	cout<<cnt;
 	return 0;
}
