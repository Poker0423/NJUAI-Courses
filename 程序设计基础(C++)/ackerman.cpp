#include <iostream>
using namespace std;
int ack(int m,int n);
int main()
{
	int m,n;
	cin>>m>>n;
	if (m<0||n<0)
	return -1;
	cout<<ack(m,n);
	return 0;
}
int ack(int m,int n)
{
	if (m==0) return (n+1);
	else if (n==0) return ack(m-1,1);
	else return ack(m-1,ack(m,n-1));//多个表达式分情况用if写出 
 } 

