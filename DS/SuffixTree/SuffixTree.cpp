#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define F first
#define S second
#define rep(i,b,e) for(int i=b;i<e;i++)

int main(){
	string s;
	cin>>s;
	s+="$";
	int n = s.length();

	vector <int> p(n),c(n);

	{
		vector < pair<char,int> > a(n);
		rep(i,0,n)
			a[i] = {s[i],i};

		sort(a.begin(),a.end());
		
		rep(i,0,n)
			p[i] = a[i].S;

		c[p[0]] = 0;
		rep(i,1,n){
			if(a[i].F==a[i-1].F)
				c[p[i]] = c[p[i-1]];
			else
				c[p[i]] = c[p[i-1]]+1;
		}

		int k=0;

		while((1<<k)<n){
			//k->k+1
			vector < pair <pair<int,int>,int> > a(n);
			rep(i,0,n)
				a[i]={{c[i],c[(i+(1<<k))%n]},i};

			sort(a.begin(),a.end());

			rep(i,0,n)
				p[i] = a[i].S;

			c[p[0]] = 0;
			rep(i,1,n){
				if(a[i].F==a[i-1].F)
					c[p[i]] = c[p[i-1]];
	            else
    	            c[p[i]] = c[p[i-1]]+1;

			}
			k++;
		}

		rep(i,0,n){
			cout<<p[i]<<" ";
		}
	}

}
