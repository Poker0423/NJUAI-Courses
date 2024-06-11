#include<iostream>
using namespace std;
int f[33],p[7],n,m;
int main()
{
    cin>>n;
    for(int i=0;i<7;i++)
    {
        cin>>m;
        f[m]=1;
    }
    for(int i=0;i<n;i++)
    {
        int sum=0;//ÖÐ½±ºÅÂëÊýÁ¿
        for(int j=0;j<7;j++)
        {
            cin>>m;
            if(f[m]==1)sum++;
        }
        p[sum]++;
    }
    for(int i=7;i>=1;i--)cout<<p[i]<<' ';
    return 0;
}
