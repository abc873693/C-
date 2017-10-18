#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;
class node
{
public:
	int data;
	int relationship[100];
};
void F(node *,int ,int );
int IStree[100]={0};
int main()
{
	node s[100];
	int n,count = 0;
	ifstream fin("input.txt");
	while(!fin.eof()){
		count++;
		fin>>n;
		for(int i=0;i<n;i++)IStree[i]=0;
		for(int i=0;i<n;i++){
			s[i].data=i;
			for(int j=0;j<n;j++){
				fin>>s[i].relationship[j];
			}
		}
		F(s,0,n);
		int check = 0;
		for(int i=0;i<n;i++)check+=IStree[i];
		cout<<"Case "<<count<<":"<<endl;
		if(check==n){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					if(s[i].relationship[j]==1)s[j].relationship[i]=1;
				}
			}
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cout<<s[i].relationship[j]<<" ";
				}
				cout<<endl;
			}
		}
		else cout<<"Not a connected graph!"<<endl;
	}
	fin.close();
	system("pause");
	return 0;
}
void F(node *s,int i,int n){
	IStree[i]=1;
	for(int j=0;j<n;j++){
		if(s[i].relationship[j]==1 && IStree[j]!=1){
			F(s,j,n);
		}
		else if(s[i].relationship[j]==1){
			s[i].relationship[j] = 0;
		}
	}
}