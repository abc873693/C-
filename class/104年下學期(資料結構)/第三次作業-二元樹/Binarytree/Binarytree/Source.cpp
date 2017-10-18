#include<iostream>
#include<string>
#include <iomanip>
#include<fstream>
#include<cmath>
#include <cstdlib>
using namespace std;
void addnode(string *,string,int &,int &);
int main()
{
	string tmp, *s;
	int max = 0 , error = 0 , count = 0;
	s = new string[100];
	ifstream fin("input.txt");
	while(!fin.eof()){
		fin>>tmp;
		if(tmp=="()"){
			cout<<"Case "<<++count<<":"<<endl;
			if(error==0){
				for(int i=max ;i>=1;i--){
					for(int j=(int)(pow(2,i));j<(pow(2,i+1));j++){
						if(s[j]!=""){
							for(int tmp=j;tmp!=0;tmp/=2){
								if(s[tmp]=="")error=1;
							}
						}
					}
				}
				if(error==1)cout<<"wrong data"<<endl;
				else {
					cout<<"correct"<<endl;
					for(int i=0 ;i<=max;i++){
						for(int space=(int)(pow(2,max-i))-2;space>=0;space--)cout<<"  ";
						for(int j=(int)(pow(2,i));j<(pow(2,i+1));j++){
							cout<<setw((int)(pow(2,max-i+2)))<<left<<s[j];
							//cout<<" ";
						}
						cout<<endl;
					}
				}
			}
			else cout<<"wrong data"<<endl;
			s = new string[100];
			max=0;
			error=0;
		}
		else addnode(s,tmp,max,error);
	}
	fin.close();
	system("pause");
	return 0;
}
void addnode(string *s,string str,int &max,int &error){
	int comma_loc;
	string num,direct;
	for(unsigned int i=1;i<str.size();i++){
		if(str[i]==',')comma_loc=i;
	}
	num.assign(str,1,comma_loc-1);
	if(str[comma_loc+1]==')')direct = "";
	else direct.assign(str,comma_loc+1,str.size()-2-comma_loc);
	int loc = (int)pow(2,direct.size()) , tmp = direct.size()-1;
	if((tmp+1)>max)max=(tmp+1);
	for(int i=tmp;i>=0;i--){
		loc += (int)((direct[i]=='R')? pow(2,tmp-i):0);
	}
	if(s[loc]!="")error=1;
	s[loc] = num;
}