#include <iostream>
using namespace std;
int max(int x[],int n)
{
	int *p_max=x;//P_max指向最大元素，先假设第一个元素最大
	int *p=x+1,//p指向第二个元素 
		*p_last=x+n-1;//p+last指向最后一个元素
	for (;p<=p_last;p++)//从第二个元素开始找最大元素
		if (*p>*p_max) p_max=p;
	return *p_max; 
}
#define M 5
#define N 5
int main()
{
	int a[M][N];
	int i,j;
	for (i=0;i<M;i++)
	  for (j=0;j<N;j++)
	    cin>>a[i][j];//获取数组元素的值
	int (*p)[N]=a,//p为数组的行指针，初始化为指向第一行，用于对数组的行进行遍历
		(*p_last_line)[N]=a+M-1;//p_last_line也为行指针，指向最后一行
	for (;p<=p_last_line;p++)//对数组的行进行循环，计算每一行的最大值
	cout<<max(*p,N)<<endl;
	return 0; 
 } 
