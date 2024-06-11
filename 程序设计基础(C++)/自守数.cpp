#include<bits/stdc++.h>
#include <cstring>
using namespace std;
int main()
{
	for (int i=1;i<=10000;i++){
	int sum=pow(i,2);
	int s=i,r=0;
	while (s!=0){
	s=s/10;
	r++;	
	}
	int n=pow(10,r);
	if (sum%n==i)
	cout<<i<<endl;
}
 	return 0;
}

