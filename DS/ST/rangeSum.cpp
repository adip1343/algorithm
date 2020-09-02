#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct SegTree{
	int size;
	vector <ll> sums;
	
	void init(int n){
		size=1;
		while(size<n) size*=2;
		sums.assign(2*size,0ll);
	}
	
	void set(int i, ll v, int ix, int lx,int rx){
		if(rx-lx==1){
			sums[ix]=v;
			return;
		}
		int mx = (lx+rx)/2;
		if(i<mx)
			set(i,v,2*ix+1,lx,mx);
		else
			set(i,v,2*ix+2,mx,rx);
		sums[ix]=sums[2*ix+1]+sums[2*ix+2];
	}
	
	void set(int i, ll v){
		set(i,v,0,0,size);
	}
	
	ll sum(int l,int r,int ix,int lx,int rx){
		
		if(lx>=r || l>=rx)
			return 0;
		// [l,r) is outside of [lx,rx) 
		
		if(lx>=l && rx<=r)
			return sums[ix];
		// [lx,rx) is completely inside of [l,r) 
		
		int mx = (lx+rx)/2;
		ll s1 = sum(l,r,2*ix+1,lx,mx);	
		ll s2 = sum(l,r,2*ix+2,mx,rx);
		// [lx,rx) -> [lx,mx) + [mx,rx)
		
		return s1+s2;
	}
	
	ll sum(int l,int r){
		return sum(l,r,0,0,size);
		//sum in [l,r)
	}
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
	
	int i,op,l,r;
	ll v;
	
	while(m--){
		cin>>op;
		if(op==1){
			cin>>i>>v;
			st.set(i,v);
		}else{
			cin>>l>>r;
			cout<<st.sum(l,r)<<endl;
		}
	}
}



