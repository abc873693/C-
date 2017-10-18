#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void F(int ,int ,int ,string*,int *);
void main() {
	ifstream fin("input.txt");
	string s[100];
	int m,n,now=0;
	int slect[100];
	fin>>m>>n;
	for(int i=0;i<m;i++)fin>>s[i];
	fin.close();
	for(int i=0;i<(m-n)+1;i++){
		slect[now]=i;
		F(m,n,now+1,s,slect);
	}
	system("pause");
}
void F(int m,int n,int now ,string *s,int *slect){
	if(n==now){
		for(int j=0;j<n;j++){
			cout<<s[slect[j]]<<" ";
		}
		cout<<endl;
	}
	else{
		for(int i=slect[now-1]+1;i<(now+(m-n)+1);i++){
			slect[now]=i;
			F(m,n,now+1,s,slect);
		}
	}
}