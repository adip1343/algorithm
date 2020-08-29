#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>
using namespace std;

typedef pair<int,int> ii;

#define v second
#define w first

int n;
vector <vector<ii>> edges;
vector <int> d;
vector <int> p;

void dijkstra(int start){
	d.assign(n,INT_MAX);
	p.assign(n,-1);
	set <ii> q;
	q.insert({0,start});
	
	d[start]=0;
	
	while(!q.empty()){
		int v = q.begin()->v;			//closest vertex
		q.erase(q.begin());
		
		for(auto e:edges){
			int to=e.v;
			int len=e.w;
			if(d[v]+len<d[to]){
				q.erase({d[to],to});
				d[to]+=len;
				p[to]=v;
				q.insert({d[to],to});	//updating childs
			}
		}
	}
}
