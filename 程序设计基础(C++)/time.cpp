#include <windows.h>
#include <ctime>
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
	char onlinetime[20];
	time_t timep;
	time(&timep);
	strftime(onlinetime,sizeof(onlinetime),"%Y-%m-%d",localtime(&timep));	
	cout<<onlinetime;
	return 0;
}
