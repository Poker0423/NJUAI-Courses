#include <iostream>
using namespace std;
int main()
{
	int n,ans;
	double sum=1;
	cin>>n;
	for (int i=2;sum<=n;i++)
	{
		double a;
		a=1.0/(double)i;
		sum+=a;
		ans=i;
	}
	cout<<ans;
	return 0;
}
