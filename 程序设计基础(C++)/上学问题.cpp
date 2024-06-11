#include<bits/stdc++.h>
using namespace std;
double s,v,m;
int n,a,t,b;
int main()
{
	cin>>s>>v;
	n=8*60+24*60;//两天总共的分钟数
	t=ceil(s/v)+10;//ceil()很重要，向上取整，否则按C++逻辑会向下取整导致行走时间少。
	n=n-t;//得出剩下的时间。
	if(n>=24*60) n-=24*60;判断是否在前一天。
	b=n%60;//得出出发分。
	a=n/60;//得出出发时
	if(a<10)//慢慢判断是否补0
	{
		if(b<10) cout<<"0"<<a<<":0"<<b;
		else cout<<"0"<<a<<":"<<b;
	}
	else
	{
		if(b<10) cout<<a<<":0"<<b;
		else cout<<a<<":"<<b;
	}
	return 0;
}

