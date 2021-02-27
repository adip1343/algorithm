#include <iostream>
#include <vector>
using namespace std;

// f is associaive function
long long f(long long a,long long b){
	if(b==0)
		return a;
	return f(b,a%b);
}

// identity for f
const long long IDENTITY=0;

struct Stack{
	vector<long long>n;	// stack of numbers
	vector<long long>g;	// stack of evaluated f
	
	// initialisation of Stack
	Stack(){
		g.push_back(IDENTITY);
	}

	// pops element in the stack
	// returns top number
	long long pop(){
		long long res = n.back();
		n.pop_back();
		g.pop_back();
		return res;
	}

	// pushes element in the stack
	void push(long long i){
		n.push_back(i);
		g.push_back(f(i,g.back()));
	}

	bool empty(){
		return n.empty();
	}
	
	// evaluates f over all elements in the stack
	long long eval(){
		return g.back();
	}
};

struct Queue{
	Stack S1;
	Stack S2;

	// nQs element in the queue
	void insert(long long i){
		S1.push(i);
	}

	// dQs element in the queue
	long long remove(){
		if(S2.empty()){
			while(!S1.empty()){
				S2.push(S1.pop());
			}
		}
		return S2.pop();
	}

	// evaluates f over all elements in the queue
	long long eval(){
		return f(S1.eval(),S2.eval());
	}

	// evaluates f over all elements in the queue after remove operation
	// without altering state of queue
	long long eval2(){
		long long tmp=remove();
		long long res=eval();
		S2.push(tmp);
		return res;
	}
};

int main(){
	int n;
	cin>>n;
 
	vector <long long>  a(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
 
	Queue window;
	int l=0;
	int res=n+1;
	for(int r=0;r<n;r++){
		window.insert(a[r]);
		while(window.eval2()==1){
			window.remove();
			l++;
		}
 
		if(window.eval()==1)
			res = min(res,r-l+1);
	}
	cout<<((res==n+1)?-1:res)<<endl;
}
