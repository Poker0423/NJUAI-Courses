#include<iostream>
#include <string>
using namespace std;
int str_to_int (char str[])
{
	int n=0;
	for (int i=0;str[i]!='\0';i++)
	n=n*10+(str[i]-'\0');
	return n;
}
int main()
{
	char ch[100];
	cin>>ch;
	cout<<str_to_int (ch)<<endl;
	return 0;
}
