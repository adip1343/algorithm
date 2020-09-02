#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef pair<int,int> ii;

#define m first
#define cnt second

ii combine(ii a,ii b){
	if(a.m<b.m)
		return a;
	if(a.m>b.m)
		return b;
	return {a.m,a.cnt+b.cnt};
}

struct SegTree{
	int size;
	vector <ii> mins;
	
	void init(int n){
		size=1;
		while(size<n) size*=2;
		mins.assign(2*size,{INT_MAX,0});
	}
	
	void set(int i, int v, int ix, int lx,int rx){
		if(rx-lx==1){
			mins[ix]={v,1};
			return ;
		}
		int mx = (lx+rx)/2;
		if(i<mx)
			set(i,v,2*ix+1,lx,mx);
		else
			set(i,v,2*ix+2,mx,rx);
		
		mins[ix] = combine(mins[2*ix+1],mins[2*ix+2]);
	}
	
	void set(int i, int v){
		set(i,v,0,0,size);
	}
	
	ii Min(int l,int r,int ix,int lx,int rx){
		
		if(lx>=r || l>=rx)
			return {INT_MAX,0};
		// [l,r) is outside of [lx,rx) 
		
		if(lx>=l && rx<=r)
			return mins[ix];
		// [lx,rx) is completely inside of [l,r) 
		
		int mx = (lx+rx)/2;
		ii min1 = Min(l,r,2*ix+1,lx,mx);	
		ii min2 = Min(l,r,2*ix+2,mx,rx);
		// [lx,rx) -> [lx,mx) + [mx,rx)
		
		return combine(min1,min2);
	}
	
	ii Min(int l,int r){
		return Min(l,r,0,0,size);
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
	int v;
	
	while(m--){
		cin>>op;
		if(op==1){
			cin>>i>>v;
			st.set(i,v);
		}else{
			cin>>l>>r;
			ii M = st.Min(l,r);
			cout<<M.m<<" "<<M.cnt<<endl;
		}
	}
}



