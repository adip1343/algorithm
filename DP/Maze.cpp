#include <iostream>
#include <cstring>
#include <string>
#define MAX 1000
#define BIG_NUM 1000000007
using namespace std;


int M;	//number of rows
int N;	//number of columns
int dp[MAX][MAX];		//number of ways to reach square [i][j]
string table[MAX];	//square is blocked or not

int main(){
	cin>>N>>M;

	memset(dp,0,sizeof(dp));	//initialising all bytes to zero

	for(int i=0;i<N;i++){
		cin>>table[i];
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(table[i][j]=='.'){	//only if current square is accesible then only we will update it
				if(i==0 && j==0)			//origin
					dp[i][j]=1;
				else if(i==0)				//First row
					dp[i][j]=dp[i][j-1];	
				else if(j==0)				//First Column
					dp[i][j]=dp[i-1][j];	
				else							//General	Needs modulo only here
					dp[i][j]=(dp[i-1][j]+dp[i][j-1])%BIG_NUM;
			}
		}
	}
	cout<<dp[N-1][M-1]<<endl;
}
