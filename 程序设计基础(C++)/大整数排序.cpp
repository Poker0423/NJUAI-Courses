#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
using namespace std;

bool cmp(string str1,string str2){
	if(str1.size() != str2.size()){
		return str1.size() < str2.size();
	}else{
		return str1 < str2;
	}
}

int main()
{
	string number;
	int n;
	vector<string> vc;//承装string的容器 
	while(cin >> n){
		for(int i = 0; i < n ; i++){
			cin >> number;
			vc.push_back(number);//用于向vector的最后添加元素 
		}//26-30行为大数的读入过程 
		sort(vc.begin(),vc.end(),cmp);//用于字符排序，将bool类型改成大于号就是降序排列 
		for(int i = 0; i < vc.size(); i++){
			cout << vc[i] << endl;
		}
		vc.clear();
	}	
    return 0;
}  
