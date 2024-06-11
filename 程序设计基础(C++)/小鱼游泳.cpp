#include<bits/stdc++.h> 
using namespace std;
int main()
{
    unsigned long long n,ans=0; 
    int x;
    cin >> x >> n; //输入星期和持续天数
    for(int i=0;i<n;i++)
    {
        if((x!=6)&&(x!=7)) //只要星期不等于6和7
            ans += 250; //总长度增加250
        if(x==7) //当x等于7的时候
        x=1; // x归位为1
        else //其他情况下（x不等于7的时候）
            x++; //x自加1
    }
    cout << ans; //输出总路程
    return 0;//有一只小鱼，它每天游泳 250公里，周末休息（实行双休日)，假设从周 x 开始算起，过了 n天以后，小鱼一共累计游泳了多少公里呢？输入两个正整数 x,n，表示从周 x 算起，经过 n 天。

}

