#include<iostream>
using namespace std;
int main(){
    int n,x;
    cin>>n;
    int sum,bus[1002]={0};
    for(int i=1;i<=n;i++)
	{
        cin>>x;
        if(bus[x])  //如果这个数已经出现过了，那么跳过
            continue;
        bus[x]++;  //如果没有出现，把数据放在桶里，并让总数居++
        sum++;
    }
    cout<<sum<<endl;
    for(int i=1;i<=1000;i++)
        if(bus[i])
            cout<<i<<' ';//再筛一遍把桶里的数输出 
    cout<<endl;
    return 0;
}

