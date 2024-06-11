#include <iostream>
using namespace std;
int main()
{
	int n,sum[100],max;
	cin>>n;
	int a[n][4];//数据类型一样直接用二维数组 
	for (int i=0;i<n;i++)
{
		for (int j=0;j<4;j++)
{
     	cin>>a[i][j];
}
}
   for (int i=0;i<n;i++)
   {
   		sum[i]=a[i][3]+a[i][2]+a[i][1];
   }
	max=0;
	for (int i=0;i<n;i++)
	{
		if (sum[i]>max)	
		max=sum[i];
	}
	for (int i=0;i<n;i++)
	{
		if (sum[i]==max)
		cout<<a[i][0]<<endl;
	}
	return 0;
}//按学号从小到大，输入n个学生的三门课成绩，n<100 。输入说明：先输入n，再输入n个学生学号和三门课成绩，学生的学号为4位整数，各门课的成绩为整数。输出说明：按学号从小到大，输出总分最高的学生学号，每个学号占一行。
