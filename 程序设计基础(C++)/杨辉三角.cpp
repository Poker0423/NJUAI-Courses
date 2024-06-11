#include<bits/stdc++.h>
using namespace std;
int main()
{
	int num[100][100]={1};
	int h;
	cin>>h;
	for (int i=1;i<=h;i++){
		for (int j=1;j<=i;j++)//j<=i就是三角形 
		num[i][j]=num[i-1][j]+num[i-1][j-1];
	}
	for (int i=1;i<=h;i++){
		for (int j=1;j<=i;j++){
		cout<<std::left<<setw(6);//每个数字左对齐，宽度为6，不足的用空格补足。
		cout<<num[i][j];
	}
	cout<<endl;
}
  	return 0;
}
