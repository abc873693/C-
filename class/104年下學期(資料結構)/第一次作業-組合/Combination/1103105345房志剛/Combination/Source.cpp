#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int factorial(int);
int C(int ,int );
void F(int ,int ,string*);
void main() {
	ifstream fin("input.txt");
	string s[100];
	int m,n;
	fin>>m>>n;
	for(int i=0;i<m;i++)fin>>s[i];
	cout<<"C"<<m<<"¨ú"<<n<<"="<<C(m,n)<<endl;
	F(m,n,s);
	system("pause");
}
int factorial(int n){
	if(n==1)return 1;
	else return n*factorial(n-1);
}
int C(int m,int n){
	return (factorial(m))/(factorial(n)*factorial(m-n));
}
void F(int m,int n,string *s){
	int select[100],x=m-n;;
	for(int i=0;i<n;i++)select[i]=i;
	do{
		for(int i=0;i<n;i++)cout<<s[select[i]]<<" ";
		cout<<endl;
		for(int i=n-1;i>=0;i--){
			if(select[i]<i+x){
				select[i]++;
				for(int j=i+1;j<m;j++)
					select[j]=select[j-1]+1;
				break;
			}
		}
		
	}while(select[0]<(x));	
	for(int i=0;i<n;i++)cout<<s[select[i]]<<" ";
	cout<<endl;
}