#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a,b;
	int c=0,d=0;
	cin>>a>>b;
	if (a[0]=='1')
	{
			for (int i=1;i<8;i++){
				if (a[i]=='1')
				c-=pow(2,7-i);
			}
	}
	else
		for (int i=1;i<8;i++){
		if (a[i]=='1')
		c+=pow(2,7-i);	
		}
	if (b[0]=='1')
	{
			for (int i=1;i<8;i++){
				if (b[i]=='1')
				d-=pow(2,7-i);
			}
	}
	else
		for (int i=1;i<8;i++){
		if (b[i]=='1')
		d+=pow(2,7-i);	
		}
		cout<<c<<" "<<d<<" "<<c+d<<endl;
    return 0;
}

