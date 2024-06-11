#include<iostream>
using namespace std;
int main()
{
    int a[10]={12 ,43,9,13,67,98,101,89,3,35};//十个数的无序数列
    int i,j,t;
    //冒泡排序
    for(i=0;i<10-1;i++)//n个数的数列总共扫描n-1次
    {
        for(j=0;j<10-i-1;j++)//每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
        {
            if(a[j]>a[j+1])//后一位数比前一位数小的话，就交换两个数的位置（升序）
            {
               t=a[j+1];
               a[j+1]=a[j];
               a[j]=t;
            }
        }
    }
    for(i=0;i<10;i++)
    {
	cout<<a[i]<<" ";
    }
    return 0;
}
