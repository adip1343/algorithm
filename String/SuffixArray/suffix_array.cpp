#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i,b,e) for(int i=b;i<e;i++)

typedef pair<int,int> ii;

class SuffixArray{
	protected :
		int n;				//Number of letters
		string s;			//String
		vector <int> p;		//Position of ith suffix
		vector <int> c;		//Comparision Class of ith suffix
		vector <int> lcp;	//longest common prefix of suffixes
/*
		void count_sort_string(){
			vector <int> cnt(26,0);
			vector <int> pos(26);

			rep(i,0,n-1)
				cnt[s[i]-'a']++;

			pos[0]=1;
			rep(i,1,26)
				pos[i] = pos[i-1]+cnt[i-1];

			p[0] = n-1;
			rep(i,0,n-1)
				p[pos[s[i]-'a']++] = i;
		}
*/
		void count_sort(){
			vector <int> cnt(n,0);
			vector <int> pos(n);

			for(auto x: c)
				cnt[x]++;

			pos[0]=0;
			for(int i=1;i<n;i++)
				pos[i] = pos[i-1]+cnt[i-1];

			vector <int> p_new(n);
			for(auto x: p)
				p_new[pos[c[x]]++] = x;

			p=p_new;
		}

		void Build(){
			{
				rep(i,0,n)
					p[i]=i;
				sort(p.begin(),p.end(),[&](int i1,int i2){return s[i1]<s[i2];});

				c[p[0]] = 0;
				rep(i,1,n)
					c[p[i]] = c[p[i-1]]+(s[p[i-1]] != s[p[i]]);
				//updating comparison classes
			}

			int k=0;

			for(int sz=1;sz<n;sz<<=1){

				rep(i,0,n)
					p[i] = (p[i]-sz+n)%n;
				//shifting p[i]

				count_sort();
				//count sort

				vector <int> c_new(n);
				c_new[p[0]] = 0;
				rep(i,1,n){
					ii prev = {c[p[i-1]],c[(p[i-1]+sz)%n]};
					ii curr = {c[p[i]]  ,c[(p[i]+sz)%n]};
					c_new[p[i]] = c_new[p[i-1]]+ (prev!=curr);
				}
				c = c_new;
				//updating comparison classes
			}
		}

		void Build_LCP(){
			int k=0;

			for(int i=0;i<n-1;i++){
				int pi = c[i];
				int j  = p[pi-1];

				while(s[i+k]==s[j+k])
					k++;

				lcp[pi]=k;
				k=max(k-1,0);
			}
			return;
		}

	public :

		SuffixArray(string S){
			s = S;
			s += "$";
			n = s.length();
			p.resize(n);c.resize(n);lcp.resize(n);

			Build();
			Build_LCP();
/*
			rep(i,0,n){
				cout<<s.substr(p[i],n-p[i])<<"\n";
			}
*/
		}

		bool Search(string & t){
			int len = t.length();

			int l=0,r=n-1,m;
			while(l<r){
				m = (l+r)/2;
				if(s.substr(p[m],len)<t)
					l=m+1;
				else
					r=m;
			}

			if(s.substr(p[l],len)==t)
				return true;
			return false;
		}

		int Count(string& t){
			int len = t.length();
			int L,R,l,r,m;

			l=0,r=n-1;
			while(l<r){
				m = (l+r+1)/2;
				if(s.substr(p[m],len)<t)
					l=m;
				else
					r=m-1;
			}
			L=l;

			l=0,r=n-1;
			while(l<r){
				m = (l+r+1)/2;
				if(s.substr(p[m],len)<=t)
					l=m;
				else
					r=m-1;
			}
			R=r;

			return R-L;
		}

		long long CountSubstrings(){
			long long sum=0;
			for(int i=1;i<n;i++){
				sum += n-p[i]-1-lcp[i];
			}
			return sum;
		}
};

class LongestCommonSubstring:public SuffixArray{
	public :
		LongestCommonSubstring(string S,string T):SuffixArray(S+"#"+T){
			int m = S.length();
			int index=0,len=0;
			int i1,i2;
			for(int i=3;i<n;i++){
				i1 = p[i];
				i2 = p[i-1];
				if(i1>i2) swap(i1,i2);

				if(i1<m && i2>m)
					if(len<lcp[i]){
						len = lcp[i];
						index = i1;
					}
			}
			cout<<S.substr(index,len)<<endl;
		}

};

int main(){
	string s,t;
	cin>>s>>t;
	LongestCommonSubstring S(s,t);
}


