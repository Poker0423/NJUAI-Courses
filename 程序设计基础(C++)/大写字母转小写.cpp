#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	char a[10];
	cin>>setw(10)>>a;
	for (int i=0;a[i]!='\0';i++)
	if (a[i]>='A'&&a[i]<='Z')
	a[i]=a[i]-'A'+'a';
	cout<<a<<endl;
	return 0;
}
