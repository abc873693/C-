#include<cstring>
#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	int n;
	double hieght,sex,s[100];
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>hieght>>sex;
		if(sex==1)
			s[i]=(hieght-80)*0.7;
		else 
			s[i]=(hieght-70)*0.6;
	}
	for(int i=0;i<n;i++)cout<<fixed<<setprecision(1)<<s[i]<<endl;
	return 0;
}
