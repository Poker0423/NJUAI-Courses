#include<bits/stdc++.h>
using namespace std;
int main()
{    
    int m,n,p,q;
	cin>>m>>n>>p>>q;
    int d1=0,s1=0;
    int d2=0,s2=0;
    switch(m)
   {
	case 12:d1+=30;
    case 11:d1+=31;
	case 10:d1+=30;
	case 9:d1+=31;
	case 8:d1+=31;
	case 7:d1+=30;
	case 6:d1+=31;
	case 5:d1+=30;
	case 4:d1+=31;
	case 3:d1+=28;
	case 2:d1+=31;
	case 1:;
   }
   s1=d1+n;
	switch(p)
   {
	case 12:d2+=30;
    case 11:d2+=31;
	case 10:d2+=30;
	case 9:d2+=31;
	case 8:d2+=31;
	case 7:d2+=30;
	case 6:d2+=31;
	case 5:d2+=30;
	case 4:d2+=31;
	case 3:d2+=28;
	case 2:d2+=31;
	case 1:;
   }
   s2=d2+q;
   cout<<s1-s2;
 return 0;
} 
