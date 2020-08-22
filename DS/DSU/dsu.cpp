#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)

class DSU{

	protected :

		int n;
		vector <int> parent;
		vector <int> size;

	public :

		DSU(int N){
			n = N;
			parent.resize(N);

			rep(i,n){
				parent[i] =i;
			}
		}

		int find_set(int i){
			if(i==parent[i]){
				return i;
			}
			return find_set(parent[i]);
		}

		void union_set(int i,int j){
			i = find_set(i);
			j = find_set(j);

			if(i!=j){
				parent[j] = i;
			}
		}

		void print(){
			rep(i,n){
				cout<<parent[i]<<" ";
			}
		}
};
//Disjoint Set Union Without any optimisation

class DSU_pc:public DSU{

	public :

		DSU_pc(int N) : DSU(N){
		};

		int find_set(int i){
			if(i==parent[i]){
				return i;
			}
			return parent[i] = find_set(parent[i]);
		}
};
//Disjoint Set Union with path compression

class DSU_siz:public DSU_pc{

	protected :

		vector <int> size;

	public :

		DSU_siz(int N) : DSU_pc(N){
			size.resize(N,1);
		}

		void union_set(int i,int j){
			i = find_set(i);
			j = find_set(j);

			if(i!=j){
				if(size[i]<size[j])
					swap(i,j);
				parent[j] = i;
				size[i] += size[j];
			}
		}

		int size_of(int i){
			return size[find_set(i)];
		}
};
//Disjoint Set Union with Union by size
//This is useful if we need size of

class DSU_rnk:public DSU_pc{

	protected :

		vector <int> rank;

	public :

		DSU_rnk(int N) : DSU_pc(N){
			rank.resize(N,0);
		}

		void union_set(int i,int j){
			i = find_set(i);
			j = find_set(j);

			if(i!=j){
				if(rank[i]<rank[j])
					swap(i,j);
				parent[j] = i;
				if(rank[i]==rank[j])
					rank[i]++;
			}
		}
};
//Disjoint Set Union with Union by rank
