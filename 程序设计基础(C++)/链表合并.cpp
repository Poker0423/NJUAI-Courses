#include <cstring>
using namespace std;
void reverse(char *str)
{
	for (int i=0,j=strlen(str)-1;i<j;i++,j--)
	{
		char temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
}
int main()
{
	char a[100];
	cin>>a;
	char *p=a;
	reverse(*p);
	cout<<a;
	return 0;
}
