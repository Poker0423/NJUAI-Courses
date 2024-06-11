#include<bits/stdc++.h>
using namespace std;
int main()
{
	int m,n;
	string s[1000];
	cin>>m>>n;
	for (int i=1;i<=m;i++)
	cin>>s[i];
	bool in_circle[m];
	int num,index;
	for (index=0;index<m;index++)
		in_circle[index]=true;
	index=m-1;
	num=m;
	while (num>1)
	{
		int cnt=0;
		while (cnt<n)
		{
			index=(index+1)%m;
			if (in_circle[index]) cnt++;
		}
		in_circle[index]=false;
		num--;
	}
	for (index=0;index<m;index++)
	if (in_circle[index]) break;
	cout<<s[index+1];
  	return 0;
}//m(m<=100)个囚犯围坐成一个圈，按照顺时针方向从1到m编号。然后从1号开始顺时针报数，报到n的囚犯出局，然后再从刚出局的囚犯下一个位置开始重新从1报数，如此重复，直到只剩下最后一个囚犯，这个幸运的囚犯将获得释放。(1<=n<=m)输入：输入包括两行。第一行是囚犯数目m和出局的报数n；第二行是编号为1到m的每个囚犯名字（名字长度小于10）输出：幸运囚犯的名字

