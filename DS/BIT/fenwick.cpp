#include <iostream>
#include <vector>
using namespace std;

#define lsb(i) (i)&(-i)

vector <int> bit;
int n;

void add(int i,int a){
	for(i++; i<=n; i+=lsb(i))
		bit[i]+=a;
}

int sum(int i){
	int sum=0;
	for(i++; i>0; i-=lsb(i))
		sum+=bit[i];
	return sum;
}

int range_sum(int l,int r){
	return sum(r)-sum(l-1);
}

int main(){
	int a;
	cin>>n;
	bit.resize(n);

	for(int i=0;i<n;i++){
		cin>>a;
		add(i,a);
	}
}
