#include<iostream>
#include<algorithm>
using namespace std;
int a[3];
char A,B,C;
int main()
{
    cin>>a[0]>>a[1]>>a[2];
    cin>>A>>B>>C;
    sort(a,a+3);
    cout<<a[A-'A']<<" "<<a[B-'A']<<" "<<a[C-'A'];//字母是大写，减去‘A’后得到0（A）,1（B）,2（C）。
    return 0;//注意区分代表字母的ABC和实际字母A 
}
