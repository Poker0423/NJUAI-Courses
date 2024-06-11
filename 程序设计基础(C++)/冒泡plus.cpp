#include <iostream>
void bubble_sort (int s[],int num);
using namespace std;
int main()
{
	int s[1000];
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	cin>>s[i];
	bubble_sort (s,n);//不必标明数组元素数量 
	for (int i=0;i<n;i++)
	cout<<s[i];
	return 0;
}
void bubble_sort (int s[],int num)
{
	bool exchange;
	while (num>1)
	{	exchange=false;
		for (int i=0;i<num-1;i++)
		{	if (s[i]>s[i+1])
			{	int temp=s[i];
				s[i]=s[i+1];
				s[i+1]=s[i];
				exchange=true;	
			}
		}
		if (!exchange) break;//不发生交换就不用往下做了 
		num--;
	}
}
