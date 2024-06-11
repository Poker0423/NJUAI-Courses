#include <iostream>
#include <cmath>
using namespace std;
int cal_roots(double a,double b,double c,double *root1,double *root2)//函数返回机制只能返回一个值， 
{	if (a==0)
	return -1;
	double t=b*b-4*a*c;
	if (t<0)
	return 0;
	if (t==0)
	{	*root1=*root2=-b/(2*a);
		return 1;
	}
	else
	{	t=sqrt(t);
		*root1=(-b+t)/(2*a);
		*root2=(-b-t)/(2*a);
		return 2;
	}
}
int main()
{
	double a1,b1,c1,r1,r2;
	cout<<"请输入方程的三个系数(a,b,c):"<<endl;
	cin>>a1>>b1>>c1;
	switch (cal_roots(a1,b1,c1,&r1,&r2))
	{
		case -1:
			cout<<"不是一元二次方程"<<endl;
			break;
		case 0:
			cout<<"方程无实根" <<endl;
			break;
		case 1:
			cout<<"方程有两个相等实根："<<r1<<endl;
			break;
		case 2:
			cout<<"方程有两个不等实根："<<r1<<"和"<<r2<<endl;
	}
	return 0;
}
