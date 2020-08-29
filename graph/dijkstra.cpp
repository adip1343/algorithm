#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int,int> ii;

#define v first
#define w second

int n;
vector <vector<ii>> edges;
vector <int> d;
vector <int> p;

void dijkstra(int start){
	d.assign(n,INT_MAX);
	p.assign(n,-1);
	vector <bool> vis(n,false);
	
	d[start]=0;
	for(int i=0;i<n;i++){
		int v=-1;
		for(int j=0;j<n;j++){
			if(!vis[j] && (v==-1 || d[j]<d[v]))
				v=j;
			//finding next vertex among non visited vertices which
			//1. v==-1 ensures atleast 1 vertex is selected
			//2. otherwise it is going to choose vertex which
			//   minmum d[i]
		}
		
		if(d[v]==INT_MAX)
			break;
		//breaking the loop as remaining
		//vertices are not reachable
		
		vis[v]=true;
		for(auto e:edges[v]){
			int to = e.v;
			int len = e.w;
			
			if(d[v]+len < d[to]){
				d[to] = d[v]+len;
				p[to] = v;
			} 
		}
		//minimizing distance among child 
	}
}
