#include "Funtion.h"
#include "LibaryData.h"
#include <ctime>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
void Numberinput(char *str,char *messge){
	cout<<"�п�J";
	if(messge!=NULL)cout<<messge;	//�Q��Ū���쪺�r����ܱ���J���
	cout<<":";
	cin>>str;
	while(!Checknum(str)){
		cout<<"��J����������ƽЭ��s��J:";
		cin>>str;	
	}
}
void CreateVerify(char *auth){
	srand(time(NULL)); //�إ߶ü��`�l
	for(int i=0;i<5;i++){
		int x=rand()%62;  //�ھڬ۹��m����5�X���ҽX�d��Ʀr�^��j�p�g
		if(x<10)auth[i]=(x+'0');
		else if(x<36&&x>=10)auth[i]=(x+'A'-10);
		else if(x<=62&&x>=36)auth[i]=(x+'a'-36);
	}
	auth[5]='\0';  //��J�r�굲���Ÿ�
}
bool AuthInput(char *str,char *messge){
	char auth[6],authinput[15];
	CreateVerify(auth);  //�������ҽX�s��auth
	cout<<"�п�J"<<messge<<":";
	cin>>str;
	cout<<auth<<endl<<"�п�J���ҽX:";
	cin>>authinput;
	if(strcmp(auth,authinput)==0)return true;  //�P�_���ҽX�O�_�ۦP
	else return false;
}
bool Checknum(char *str){  //�ˬd�O�_�Ҭ��Ʀr
	for(int i=0;i < strlen(str);i++){
		if(str[i]<'0'||str[i]>'9')return 0;
	}
	return 1;
}
bool LeapyearJudge(int y){  //�P�_�O�_���|�~
	if(y%4==0&&y%100!=0||y%400==0)return true;
	else return false;
}
int dataDECODER(char *str){  //����榡�P�_�Y�D�k�榡�Ǧ^-1
	int c=0,x;
	char *w;
	int s[10];
	w = strtok(str, "/");  //�Q��strtok�N�~���j�}
	while (w != NULL) {
		s[c]=atoi(w);
		w = strtok(NULL, "/");
		c++;
	}
	if(c==3){  //����d��P�_
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
	system("CLS");	//�C�����^�D���ɲM�����e���e��
	cout<<"�Ϯ��]�޲z�t��(Library management system)"<<endl;
	cout<<"1.�ɮ�(�ϥΪ�)"<<endl;
	cout<<"2.�d��(�ϥΪ�)"<<endl;
	cout<<"3.��s(�ϥΪ̩κ޲z��)"<<endl;
	cout<<"4.�s�W(�޲z��)"<<endl;
	cout<<"5.���}"<<endl;
	Numberinput(str,NULL);	//�I�s��ƿ�J�禡
	return atoi(str);	//�N�^�ǭȨϥ�atoi�禡�ഫ�����
}