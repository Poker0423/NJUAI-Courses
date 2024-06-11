#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    if(d-a>18)
    cout<<"YES";
    else if(d-a==18&&b<e)
    cout<<"YES";
    else if(d-a==18&&b==e&&c<=f)
    cout<<"YES";
    else
    cout<<"NO";
	return 0;
}
