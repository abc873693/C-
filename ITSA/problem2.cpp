#include<cstring>
#include<iostream>
using namespace std;
int compare(char *a,char *b){
	if(strlen(a)>strlen(b))return 1;
	else if(strlen(a)<strlen(b))return -1;
	else {
		for(int i=0;i<(int)strlen(a);i++){
			if(a[i]>b[i])return 1;
			else if(a[i]<b[i])return -1;
		}
		return 0;
	}
}
void swapa(int &a,int &b,char *stra,char *strb){
	int c=a;
	a=b;
	b=c;
	char s[1000];
	strcpy(s,stra);
	strcpy(stra,strb);
	strcpy(strb,s);
}
int main(){
	char s[11][1000];
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s[i];
	}
	int sum[11]={0};
	for(int i=0;i<n;i++){
		for(int j=0;j<(int)strlen(s[i]);j++){
			sum[i]+=(s[i][j]-'0');
		}
	}
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(sum[i]>sum[j]){
				swapa(sum[i],sum[j],s[i],s[j]);
			}
			else if(sum[i]==sum[j]){
				if(compare(s[i],s[j])==1){
					swapa(sum[i],sum[j],s[i],s[j]);
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<s[i];
		if(i<n-1)cout<<" ";
	}
	cout<<endl;
	return 0;
}
