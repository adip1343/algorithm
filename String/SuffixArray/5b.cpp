#include <bits/stdc++.h>
using namespace std;

#define rep(i,b,e) for(int i=b;i<n;i++)
typedef pair<int,int> ii;

const int MAXN = 400005;

string s;		//string
int n;			//length of string
int p[MAXN];	//p[i] = lexicographically ith suffix
int c[MAXN];    //c[i] = comparison class of ith suffix
				//after build p[i] for s[i...n-1]
int lcp[MAXN];  //lcp[i] = longest common prefix among s[p[i]...] & s[p[i-1]...]
ii a[MAXN];

void Build(string S){
	s = S+"$";
	n = s.length();

	//first iteration
	rep(i,0,n)
		p[i]=i;
	sort(p,p+n,[&s](int p1,int p2){return s[p1]<s[p2];});

	c[p[0]]=0;
	rep(i,1,n)
		c[p[i]] = c[p[i-1]] + c[p[i]]==c[p[i-1]];

	//sz -> sz*2
	for(int sz=1;sz<n;sz<<=1){
		rep(i,0,n)
			a[i] = {c[i],c[(i+sz)%n]};

		sort(p,p+n,[&a,&sz](int p1,int p2){return a[(p1+sz)%n]<a[(p2+sz)%n];});

		c[p[0]]=0;
	    rep(i,1,n)
    	    c[p[i]] = c[p[i-1]] + (int)(a[p[i]]==a[p[i-1]]);
	}
}

void Build_LCP(){
	int k=0,s1,s2;
	lcp[0]=0;
	rep(i,1,n){
		s1 = p[i];
		s2 = p[c[s1]-1];
		while(s[s1+k]==s[s2+k]) k++;
		lcp[i] = k;
		k = max(k-1,0);
	}
}

long long CountSubstring(){
	long long sum = 0;
	rep(i,1,n)
		sum += n-1-p[i]+lcp[i];
	return sum;
}

/*
void CountSubstring(string& s,string& t)
	int m = s.size();
	Build(s+"#"+t);
	Build_LCP();
	long long sum = 0;
	rep(int i=0;i<n;i++){
		sum += n-1-
	}

}
*/
int main(){
	cin>>s;
	Build(s);
	Build_LCP();
	cout<<CountSubstring()<<endl;
}
