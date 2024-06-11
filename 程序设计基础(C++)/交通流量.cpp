#include<bits/stdc++.h>
#include <cstring>
using namespace std;
int main()
{
	int sign[1000],a=0,b=0,c;
	cin>>sign[1000];
	for (int i=0;sign[i]!=0;i++)
	{
		if (sign[i]==1)
		a++;
		if (sign[i]==2)
		b++;
		int j=0;
		if (sign[j]==1||sign[j+1]==2)
		{
			 c=1;
			for (int h=j+1;h++;){
				if (sign[h]==2)
				c++;
				else break;
			}
			}
	}
	cout<<a<<" "<<b<<" "<<c<<endl;
 	return 0;
}
