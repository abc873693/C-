#include<fstream>
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	ifstream fin("input.txt");
	char s[100];
	char data[100][100];
	char direct[100][100];
	int max = 0 , error = 0;
	while(!fin.eof()){
		fin>>s;
		if(strcmp(s,"()")==0){
			char binary_tree[1024][10];
			int level = 0;
			for(int i = 0; i < 1024 ;i++){
				strcpy(binary_tree[i],"");
			}
			for(int i = 0; i < max ;i++){
				if(strlen(direct[i])>level)level = strlen(direct[i]);
				int loc = pow(2,strlen(direct[i])) ;
				for(int j = 0 ; j < strlen(direct[i]); j++){
					if(direct[i][j]=='R')loc+=pow(2,strlen(direct[i])-1-j);
				}
				if(strcmp(binary_tree[loc],"")!=0)error = 1;
				strcpy(binary_tree[loc],data[i]);
			}
			if(error == 1) cout<<"wrong data"<<endl;
			else {
				for(int i = 1 ;i < pow(2,level) ;i++){
					if(strcmp(binary_tree[i],"")!=0){
						int tmp = i;
						while(tmp!=0){
							if(strcmp(binary_tree[tmp],"")==0)error = 1;
							tmp/=2;
						}
					}
				}
				if(error == 1) cout<<"wrong data"<<endl;
				else {
					for(int i=0 ;i<=level;i++){
						for(int space=(pow(2,level-i))-2;space>=0;space--)cout<<"  ";
						for(int j=(pow(2,i));j<(pow(2,i+1));j++){
							cout<<binary_tree[j];
							for(int space=0;space<(pow(2,level-i+2)-strlen(binary_tree[j]));space++)cout<<" ";
						}
						cout<<endl;
					}
				}
			}
			max = 0;
			error = 0;
		}
		else {
			int loc;
			for(int i=0;i<strlen(s);i++){
				if(s[i]==','){
					loc=i;
					break;
				}
			}
			strncpy(data[max],s+1,loc-1);
			strncpy(direct[max],s+loc+1,strlen(s)-loc-2);
			data[max][loc-1]='\0';
			direct[max][strlen(s)-loc-2]='\0';
			max++;
		}
	}
	fin.close();
	system("pause");
	return 0;
}