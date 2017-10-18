#include "Funtion.h"
#include "LibaryData.h"
#include <ctime>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
void Numberinput(char *str,char *messge){
	cout<<"請輸入";
	if(messge!=NULL)cout<<messge;	//利用讀取到的字串顯示欲輸入資料
	cout<<":";
	cin>>str;
	while(!Checknum(str)){
		cout<<"輸入必須為正整數請重新輸入:";
		cin>>str;	
	}
}
void CreateVerify(char *auth){
	srand(time(NULL)); //建立亂數總子
	for(int i=0;i<5;i++){
		int x=rand()%62;  //根據相對位置產生5碼驗證碼範圍數字英文大小寫
		if(x<10)auth[i]=(x+'0');
		else if(x<36&&x>=10)auth[i]=(x+'A'-10);
		else if(x<=62&&x>=36)auth[i]=(x+'a'-36);
	}
	auth[5]='\0';  //放入字串結尾符號
}
bool AuthInput(char *str,char *messge){
	char auth[6],authinput[15];
	CreateVerify(auth);  //產生驗證碼存到auth
	cout<<"請輸入"<<messge<<":";
	cin>>str;
	cout<<auth<<endl<<"請輸入驗證碼:";
	cin>>authinput;
	if(strcmp(auth,authinput)==0)return true;  //判斷驗證碼是否相同
	else return false;
}
bool Checknum(char *str){  //檢查是否皆為數字
	for(int i=0;i < strlen(str);i++){
		if(str[i]<'0'||str[i]>'9')return 0;
	}
	return 1;
}
bool LeapyearJudge(int y){  //判斷是否為閏年
	if(y%4==0&&y%100!=0||y%400==0)return true;
	else return false;
}
int dataDECODER(char *str){  //日期格式判斷若非法格式傳回-1
	int c=0,x;
	char *w;
	int s[10];
	w = strtok(str, "/");  //利用strtok將年月日隔開
	while (w != NULL) {
		s[c]=atoi(w);
		w = strtok(NULL, "/");
		c++;
	}
	if(c==3){  //日期範圍判斷
		x=s[0]*10000;
		if(s[1]>=1&&s[1]<=12){
			x+=s[1]*100;
			if((s[1]==1||s[1]==3||s[1]==5||s[1]==7||s[1]==8||s[1]==10||s[1]==12)&&(s[2]>=1&&s[2]<=31))x+=s[2];
			else if((s[1]==4||s[1]==6||s[1]==9||s[1]==11)&&(s[2]>=1&&s[2]<=30))x+=s[2];
			else if((s[1]==2)&&(LeapyearJudge(s[0]))&&(s[2]>=1&&s[2]<=29))x+=s[2];
			else if((s[1]==2)&&(!LeapyearJudge(s[0]))&&(s[2]>=1&&s[2]<=28))x+=s[2];
			else return -1;
		}
		else return -1;
		return x;
	}
	else return -1;
}
int MenuInput(){
	char str[20];
	system("CLS");	//每次跳回主選單時清除之前的畫面
	cout<<"圖書館管理系統(Library management system)"<<endl;
	cout<<"1.借書(使用者)"<<endl;
	cout<<"2.查詢(使用者)"<<endl;
	cout<<"3.更新(使用者或管理員)"<<endl;
	cout<<"4.新增(管理員)"<<endl;
	cout<<"5.離開"<<endl;
	Numberinput(str,NULL);	//呼叫整數輸入函式
	return atoi(str);	//將回傳值使用atoi函式轉換成整數
}