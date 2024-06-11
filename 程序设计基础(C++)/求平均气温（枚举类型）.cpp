#include <iostream>
#include<iomanip>
using namespace std;
enum Day {SUN,MON,TUE,WED,THU,FRI,SAT};
int main()
{
	double max,min,maxsum=0,minsum=0;
	for (Day d=SUN;d<=SAT;d=(Day)(d+1))//枚举类型的for循环
	{
		cout<<"Please input ";
		switch(d)
		{
			case SUN:{cout<<"Sunday";	break;}
			case MON:{cout<<"Monday";	break;}
			case TUE:{cout<<"Tuesday";	break;}
			case WED:{cout<<"Wednesday";	break;}
			case THU:{cout<<"Thursday";	break;}
			case FRI:{cout<<"Friay";	break;}
			case SAT:{cout<<"Satday";	break;}
		 } 
		 cout<<"'s temperature(max,min):"<<endl;
		 cin>>max>>min;
		 maxsum+=max;
		 minsum+=min;
	}
	maxsum=maxsum/7.0;//怎么保留一位小数 
	minsum=minsum/7.0;
	cout<<setiosflags(ios::fixed)<<setprecision(1);
	cout<<"The average temperture is "<<maxsum<<" and "<<minsum<<endl;
	return 0;
}
	

