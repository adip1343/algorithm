#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef long long ll;

struct SegTree{
	int size;
	vector <ll> mins;
	
	void init(int n){
		size=1;
		while(size<n) size*=2;
		mins.assign(2*size,INT_MAX);
	}
	
	void set(int i, ll v, int ix, int lx,int rx){
		if(rx-lx==1){
			mins[ix]=v;
			return;
		}
		int mx = (lx+rx)/2;
		if(i<mx)
			set(i,v,2*ix+1,lx,mx);
		else
			set(i,v,2*ix+2,mx,rx);
		mins[ix] = min(mins[2*ix+1],mins[2*ix+2]);
	}
	
	void set(int i, ll v){
		set(i,v,0,0,size);
	};
	
	ll Min(int l,int r,int ix,int lx,int rx){
		if(lx>=r || l>=rx)
			return INT_MAX;
		if(lx>=l && rx<=r)
			return mins[ix];
		int mx = (lx+rx)/2;
		ll s1 = Min(l,r,2*ix+1,lx,mx);
		ll s2 = Min(l,r,2*ix+2,mx,rx);
		return min(s1,s2);
	};
	
	ll Min(int l,int r){
		return Min(l,r,0,0,size);
	};
};

int main(){
	int n,m,a;
	cin>>n>>m;
	
	SegTree st;
	st.init(n);
	for(int i=0;i<n;i++){
		cin>>a;
		st.set(i,a);
	}
	
	int i,op,l,r,v;
	
	while(m--){
		cin>>op;
		if(op==1){
			cin>>i>>v;
			st.set(i,v);
		}else{
			cin>>l>>r;
			cout<<st.Min(l,r)<<endl;
		}
	}
}



