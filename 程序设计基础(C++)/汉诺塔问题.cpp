#include <iostream>
using namespace std;
void hanoi(char x,char y,char z,int n)//把n个圆盘从柱子x移到y 
{ 
if (n==1)
	cout<<"1: "<<x<<"→"<<y<<endl;//一个盘子就一步 
else
{	
	hanoi(x,z,y,n-1);//把n-1个圆盘从柱子x移到z
	cout<<n<<": "<<x<<"→"<<y<<endl;//最后一步
	hanoi(z,y,x,n-1);//把n-1个圆盘从柱子z移到y
}
}
int main ()
{
	char A,B,C;
	int n;
	cin>>n;
	hanoi('A','B','C',n);
	return 0;
}
