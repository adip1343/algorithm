#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SuffixArray{
	private :
		int n;				//Number of letters
		string s;			//String
		vector <int> p;		//Position of ith suffix
		vector <int> c;		//Comparision Class of ith suffix

		void count_sort_string(){
			vector <int> cnt(26,0);
			vector <int> pos(26);

			for(int i=0;i<n-1;i++){
				cnt[s[i]-'a']++;
			}

			pos[0]=1;
			for(int i=1;i<26;i++){
				pos[i] = pos[i-1]+cnt[i-1];
			}

			p[0] = n-1;
			for(int i=0;i<n-1;i++){
				p[pos[s[i]-'a']] = i;
				pos[s[i]-'a']++;
			}
		}

		void count_sort(){
			vector <int> cnt(n,0);
			vector <int> pos(n);

			for(auto x: c){
				cnt[x]++;
			}

			pos[0]=0;
			for(int i=1;i<n;i++){
				pos[i] = pos[i-1]+cnt[i-1];
			}

			vector <int> p_new(n);
			int y;
			for(auto x: p){
				y = c[x];
				p_new[pos[y]] = x;
				pos[y]++;
			}
			p=p_new;
		}

	public :

		SuffixArray(string S){
			s = S;
			s += "$";
			n = s.length();
			p.resize(n);c.resize(n);

			count_sort_string();	//k=0

			c[p[0]] = 0;
			for(int i=1;i<n;i++){
				if(s[p[i-1]]==s[p[i]])
					c[p[i]] = c[p[i-1]];
				else
					c[p[i]] = c[p[i-1]]+1;
			}
			//updating comparison classes

			int k=0;

			while((1<<k)<n){

				for(int i=0;i<n;i++)
					p[i] = (p[i]-(1<<k)+n)%n;
				//shifting p[i]

				count_sort();
				//count sort

				vector <int> c_new(n);
				c_new[p[0]] = 0;
				for(int i=1;i<n;i++){
					pair<int,int> prev = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
					pair<int,int> curr = {c[p[i]],c[(p[i]+(1<<k))%n]};
					if(prev==curr)
						c_new[p[i]] = c_new[p[i-1]];
					else
						c_new[p[i]] = c_new[p[i-1]]+1;
				}
				c = c_new;
				//updating comparison classes

				if(c[n-1]==n-1)
					break;
				//if the suffixes are already sorted

				k++;
				//ready for next iteration
			}

			for(auto x:p){
				cout<<x<<" ";
			}
		}

};

int main(){
	string s;
	cin>>s;
	SuffixArray S(s);
}


