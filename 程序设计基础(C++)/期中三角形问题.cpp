#include <iostream>
using namespace std;
int main()
{
	int m,a,b,c,num=0;
	cin>>m;
	for (a=m/2;a>0;a--)
	{
		for (b=a;b>0;b--)
        {
          for (c=b;c>0;c--)  
          {
              if (a+b+c==m&&b+c>a)//思路类四方定理 
              num++;
          }
        }
	}
	cout<<num;
	return 0;
}//一根长度为m（m为整数）的木棒截成三小段，输出截成后的三小段木棒可以组成多少种的三角形？注意，两个三角形，如果三边长仅是顺序不同，算同一种三角形。例如：边长为2,4,4的三角形，和边长为4,2,4的三角形是同一种三角形。
