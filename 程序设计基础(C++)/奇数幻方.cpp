#include<bits/stdc++.h>
using namespace std;
int N,a[40][40],h,l;//初始化时全是0 
int main(){
	cin>>N;
	a[0][N/2]=1,h=0,l=N/2;//h与l做光标 
	for(int i=2;i<=N*N;i++)//i++为从小到大填入 
	{
		if(h==0&&l!=N-1) a[N-1][l+1]=i,h=N-1,l++;//每次结束将光标放到下一个条件上 
		else if(l==N-1&&h!=0) a[h-1][0]=i,h--,l=0;
		else if(h==0&&l==N-1) a[h+1][l]=i,h++;
		else if(h!=0&&l!=N-1){
			if(a[h-1][l+1]==0&&h-1>=0&&l+1<=N) //后两个条件是要考虑溢出 
			a[h-1][l+1]=i,h--,l++;
			else a[h+1][l]=i,h++;
		}
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++) 
		cout<<a[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}

