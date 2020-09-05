#include <iostream>
#include <string>
#include <stack>
#include <cstring>
using namespace std;

#define MAX_LENGTH  3000

string s1;					//string 1
string s2;					//string 2
stack <char> soln;	//soln stack
int dp[MAX_LENGTH][MAX_LENGTH];

//Memoisation solution
//step 1 : Base Case
//step 2 : if soln not computed already then compute recursively
//step 3 : return the soln

int solve(int p1,int p2){
	if(p1<0||p2<0)				//base case
		return 0;
	if(dp[p1][p2]==-1){
		if(s1[p1]==s2[p2])
			return dp[p1][p2] = 1+ solve(p1-1,p2-1);	//equal char
		return dp[p1][p2] = max( solve(p1-1,p2) , solve(p1,p2-1) );	//otherwise
		// Should we take max of both these???
		// Noooooo
		// This is lcs("aabb","bdb")->lcs("aab","bd")
		// we are considering the common character
		// There is no harm in removing last character 
	}
	return dp[p1][p2];	//returning already computed soln
}

void build(int p1,int p2){
	if(p1<0||p2<0)		//base case
		return;
	if(s1[p1]==s2[p2]){
		soln.push(s1[p1]);		//pushing into soln
		build(p1-1,p2-1);		//building on
		return;
	}
	if(p1>0 && p2>0){			//both strings have more than one characters
		if(dp[p1-1][p2] > dp[p1][p2-1] )
			build(p1-1,p2);
		else
			build(p1,p2-1);
	}
	else if(p1>0)				//only s1 has more than one character
		build(p1-1,p2);
	else if(p2>0)				//only s2 has more than one character
		build(p1,p2-1);
	return;
}

int main(){
	
	memset(dp,-1,sizeof(dp));

	cin>>s1>>s2;
	int L = s1.length();
	int M = s2.length();

	solve(L-1,M-1);	//solving
	build(L-1,M-1);	//backtracking
	
	while(!soln.empty()){	//printing
		cout<<soln.top();
		soln.pop();
	}
}
