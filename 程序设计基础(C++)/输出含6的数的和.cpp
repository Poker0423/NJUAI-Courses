#include <iostream>
using namespace std;
int main()
{
	int n=1000;
	int sum=0;
	for (int i=1;i<=n;i++ )
	{
	if (i/100==6||(i/10)%10==6||i%10==6)
	sum+=i;
}
	cout<<sum;
	return 0;
}
