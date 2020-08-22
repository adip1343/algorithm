// https://codeforces.com/contest/1167/problem/C

#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)

class dsu{
	int n;
	vector <int> p;

	public :

	vector <int> s;

	dsu(int N){
		n = N;
		p.resize(N);
		s.resize(N,1);
		rep(i,n)
			p[i] = i;
	}

	int parent(int i){
		if(p[i]==i)
			return i;
		return p[i] = parent(p[i]);	//Path Compression
	}

	void connect(int i,int j){
		i = parent(i);
		j = parent(j);
		
		if(i!=j){	
			if(s[j]>s[i])
				swap(i,j);

			s[i] += s[j];
			p[j] = i;
		}		//union by size
	}
};

int main(){
	int n,m,g,f,s;
	cin>>n>>m;

	dsu user(n+1);
	
	rep(i,m){
		cin>>g;
		if(g!=0)
			cin>>f;
		rep(j,g-1){
			cin>>s;
			user.connect(f,s);
		}
	}

	rep(i,n){
		cout<<user.s[user.parent(i+1)]<<" ";
	}	
}
