#include "LibaryData.h"
#include "Funtion.h"
#include <fstream> 
#include <iostream>
using namespace std;
int ReadMemberData(Member *user,char *MemberDataName){
	int total=0;
	ifstream fin(MemberDataName);	//�}���ɮ�Ū��MemberDataName
	while ( !fin.eof() ) {	//����MemberDataName�̪��榡Ū���۹��������
		fin>>user[total].ID;
		fin>>user[total].account;
		fin>>user[total].password;
		fin>>user[total].name;
		fin>>user[total].email;
		fin>>user[total].adress;
		fin>>user[total].cellNumber;
		fin>>user[total].MAXlendamount;
		fin>>user[total].currentbooktatal;
		fin>>user[total].lendtatal;
		for(int i=0;i<user[total].lendtatal;i++){
			fin>>user[total].lendid[i]>>user[total].lendamount[i];
		}
		total++;
	}
	total--;
	cout<<"ReadMemberData finish"<<endl;	//Ū������ܧ���
	fin.close();	//�����ɮ�
	return total;	//�^�ǨϥΪ��`��
}
int ReadAdministatorData(Administator *admin,char *AdministatorDataName){
	int total=0;
	ifstream fin(AdministatorDataName);	//�}���ɮ�Ū��AdministatorDataName
	while ( !fin.eof() ) { //����AdministatorDataName�̪��榡Ū���۹��������
		fin>>admin[total].account;
		fin>>admin[total].password;
		fin.get();
		total++;
	}
	cout<<"ReadAdministatorData finish"<<endl;	//Ū������ܧ���
	fin.close();	//�����ɮ�
	return total;	//�^�Ǻ޲z���`��
}
int ReadBookData(Book *books,char *BookDataname){
	int total=0;
	ifstream fin(BookDataname);	//�}���ɮ�Ū��BookDataname
	while ( !fin.eof() ) { //����BookDataname�̪��榡Ū���۹��������
		fin>>books[total].ID;
		fin.get();
		fin.getline(books[total].name,50);
		fin>>books[total].lendout;
		fin>>books[total].remaining;
		fin.get();
		fin.getline(books[total].publisher,50);
		fin>>books[total].publicationDate;
		fin.get();
		total++;
	}
	cout<<"ReadBookData finish"<<endl; //Ū������ܧ���
	fin.close(); //�����ɮ�
	return total; //�^�Ǻ޲z���`��
}
void WriteMemberData(Member *user,char *MemberDataName,int total){
	ofstream fout(MemberDataName); //�}���ɮ׼g�JWriteMemberData
	for(int i=0;i<total;i++){	//�����ɮ׮榡�g�J�ɮ�
		fout<<user[i].ID<<endl;
		fout<<user[i].account<<endl;
		fout<<user[i].password<<endl;
		fout<<user[i].name<<endl;
		fout<<user[i].email<<endl;
		fout<<user[i].adress<<endl;
		fout<<user[i].cellNumber<<endl;
		fout<<user[i].MAXlendamount<<endl;
		fout<<user[i].currentbooktatal<<endl;
		fout<<user[i].lendtatal<<endl;
		for(int j=0;j<user[i].lendtatal;j++){
			fout<<user[i].lendid[j]<<" "<<user[i].lendamount[j]<<endl;
		}
		if(i<total-1)fout<<endl;
	}
	fout.close(); //�����ɮ�
}
void WriteBookData(Book *books,char *BookDataname,int total){
	ofstream fout(BookDataname);	//�}���ɮ׼g�JBookDataname
	for(int i=0;i<total;i++){ //�����ɮ׮榡�g�J�ɮ�
		fout<<books[i].ID<<endl;
		fout<<books[i].name<<endl;
		fout<<books[i].lendout<<endl;
		fout<<books[i].remaining<<endl;
		fout<<books[i].publisher<<endl;
		fout<<books[i].publicationDate;
		if(i<total-1)fout<<endl<<endl;
	}
	fout.close(); //�����ɮ�
}

int MemberAccountCheck(char *str,Member *user,int total){
	for(int i=0;i<total;i++){ //�Q�ΰj��j�M�|���b���O�_�s�b
		if(strcmp(user[i].account,str)==0)return i; //�s�b�^�Ǳb���Ҧb�����ޭ�
	}
	return -1; //�䤣��^��-1
}
int MemberCheck(char *str,Member *user,int total){
	if(Checknum(str)){  //�ˬd�O�_�����
		int searchID=atoi(str);  //�NŪ�����r���ഫ�����
		for(int i=0;i<total;i++){ //�Q�ΰj��j�M�|��ID�O�_�s�b
			if(user[i].ID==searchID)return i; //�s�b�^��ID�Ҧb�����ޭ�
		}
	}
	return -1;	//�䤣��^��-1
}
int AdministatorCheck(char *str,Administator *admin,int total){
	for(int i=0;i<total;i++){	//�Q�ΰj��j�M�޲z���b���O�_�s�b
		if(strcmp(admin[i].account,str)==0)return i; //�s�b�^�Ǳb���Ҧb�����ޭ�
	}
	return -1;	//�䤣��^��-1
}
int BookCheck(char *str,Book *books,int total){
	if(Checknum(str)){  //�ˬd�O�_�����
		int searchID=atoi(str); //�NŪ�����r���ഫ�����
		for(int i=0;i<total;i++){ //�Q�ΰj��j�M�Ѹ��O�_�s�b
			if(books[i].ID==searchID)return i; //�s�b�^�ǮѸ��Ҧb�����ޭ�
		}
	}
	return -1; //�䤣��^��-1
}
int Checkuserlend(int BookID,int ID,Member *user){
	for(int i=0;i<user[ID].lendtatal;i++){ //�Q�ΰj��j�M�ϥΪ̭ɾ\�Ѹ��O�_�s�b
		if(user[ID].lendid[i]==BookID)return i; //�s�b�^�ǮѸ��Ҧb�����ޭ�
	}
	return -1; //�䤣��^��-1
}
int MemberLogin(Member *user,Total &total){
	int index=0;
	bool susses=0;
	char acoont[20],password[20];
	do{ //�L���j�骽��b����J���\
		cout<<"�п�J�ϥΪ̱b��:";
		cin>>acoont;
		cout<<"�п�J�ϥΪ̱K�X:";
		cin>>password;
		index=MemberAccountCheck(acoont,user,total.Member); //�Q�η|���b���j�M�禡���o�b�������ޭ�
		if(index!=-1){
			if(strcmp(user[index].password,password)==0)susses=1;
			else cout<<"�K�X���~�Э��s��J"<<endl;
		}
		else {
			cout<<"�b�����~�Э��s��J"<<endl;
		}
	}while(!susses);
	return index;
}
int AdministatorLogin(Administator *admin,Total &total){
	int index=0;
	bool susses=0;
	char acoont[20],password[20];
	do{ //�L���j�骽��b����J���\
		cout<<"�п�J�޲z���b��:";
		cin>>acoont;
		cout<<"�п�J�޲z���K�X:";
		cin>>password;
		index=AdministatorCheck(acoont,admin,total.Member);  //�Q�κ޲z���b���j�M�禡���o�b�������ޭ�
		if(index!=-1){
			if(strcmp(admin[index].password,password)==0)susses=1;
			else cout<<"�K�X���~�Э��s��J"<<endl;
		}
		else {
			cout<<"�b�����~�Э��s��J"<<endl;
		}
	}while(!susses);
	return index;
}
void PrintAllBook(Book *books,int total){
	cout<<"�H�U�O�Ҧ����y���:"<<endl;
	printf("%5s|%45s|%25s|%12s|%10s|%10s|\n","ID","�ѦW","�X����","�X�����","�ɥX�q","�w�s�q");
	for(int i=0;i<total;i++){ //�C�L�Ҧ����y���
		cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
		printf("%5d|%45s|%25s|%12s|%10d|%10d|\n",books[i].ID,books[i].name,books[i].publisher,books[i].publicationDate,books[i].lendout,books[i].remaining);
	}
	cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
}
void NAMESearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	cout<<"�п�J����r:";
	cin>>str;
	for(int i=0;i<total;i++){
		char *loc;  
		loc=strstr(book[i].name,str);  //�j�M�O�_������r�b�ѦW��
		if(loc!=NULL){
			arr[MAX]=i; //�N���y�����ޭȶǦ^�}�C
			MAX++;  //�W�[�j�M�ƶq
		}
	}
	//�Y�L�j�M��h�C�L���~�T��
	if(MAX==0)cout<<"�S������ŦX����r��"<<str<<"�����ѦW"<<endl;
	else cout<<"�H�U�O�ŦX����r��"<<str<<"�����ѦW"<<endl;
}
void IDSearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	Numberinput(str,NULL);	//�ϥ�Numberinput�禡�T�O��J�����
	for(int i=0;i<total;i++){
		if(atoi(str)==book[i].ID){ 
			arr[0]=i;
			MAX++;
		}
	}
	//�Y�L�j�M��h�C�L���~�T��
	if(MAX==0)cout<<"�S������Ѹ��ŦX��"<<str<<"��"<<endl;
	else cout<<"�H�U�O�Ѹ��ŦX��"<<str<<"��"<<endl;
}
void PUBLISHERSearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	cout<<"�п�J����r:";
	cin>>str;
	for(int i=0;i<total;i++){
		char *loc;
		loc=strstr(book[i].publisher,str);	 //�j�M�O�_������r�b�X�����W�٤�
		if(loc!=NULL){
			arr[MAX]=i; //�j�M�O�_������r�b�X�����W�٤�
			MAX++;	 //�W�[�j�M�ƶq
		}
	}
	//�Y�L�j�M��h�C�L���~�T��
	if(MAX==0)cout<<"�S������ŦX����r��"<<str<<"�����X����"<<endl;
	else cout<<"�H�U�O�ŦX����r��"<<str<<"�����X����"<<endl;
}
void DATASearch(Book *book,int total,int *arr,int &MAX){
	cout<<"1.�p��j�M���"<<endl;
	cout<<"2.����j�M���"<<endl;
	cout<<"3.�j��j�M���"<<endl;
	char str[50];
	Numberinput(str,NULL);
	int mode=atoi(str);
	int searchdata,compare;
	char data[20],tmp[20];
	if((mode>=1&&mode<=3)){ //�P�_�Ҧ��O�_�s�b �s�b�~�~���J���
		cout<<"�п�J���(YYYY/MM/DD):";
		cin>>data;
		strcpy(str,data);
		searchdata=dataDECODER(data);  //�N�r��榡������ѽX���i�H�P�_�����
		while(searchdata==-1){ //�榡���~�N���ƿ�J
			cout<<"�榡���~�Э��s��J:";
			cin>>data;
			strcpy(str,data); //���N�n�ѽX���r��s��str �קKstrtok���r�� ���r��i�H�O�d
			searchdata=dataDECODER(data);  //�N�r��榡������ѽX���i�H�P�_�����
		}
	}
	switch (mode) //�ھڿ���\�వ�۹������ʧ@ �N�ŦX���󪺦s��arr�}�C
	{
	case 1:
		strcpy(data,"�p��");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //���N�n�ѽX���r��s��tmp �קKstrtok���r�� ���r��i�H�O�d
			compare=dataDECODER(tmp);  //�N�r��榡������ѽX���i�H�P�_�����
			if(compare<searchdata){
				arr[MAX]=i; //�ŦX���󪺮��y���ޭȦs��arr�}�C
				MAX++;
			}
		}	
		break;
	case 2:
		strcpy(data,"����");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //���N�n�ѽX���r��s��tmp �קKstrtok���r�� ���r��i�H�O�d
			compare=dataDECODER(tmp); //�N�r��榡������ѽX���i�H�P�_�����
			if(compare==searchdata){
				arr[MAX]=i; //�ŦX���󪺮��y���ޭȦs��arr�}�C
				MAX++;
			}
		}	
		break;
	case 3:
		strcpy(data,"�j��");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //���N�n�ѽX���r��s��tmp �קKstrtok���r�� ���r��i�H�O�d
			compare=dataDECODER(tmp); //�N�r��榡������ѽX���i�H�P�_�����
			if(compare>searchdata){
				arr[MAX]=i; //�ŦX���󪺮��y���ޭȦs��arr�}�C
				MAX++;
			}
		}	
		break;
	default:
		cout<<"�L���\��"<<endl;
		break;
	}
	if(MAX==0&&(mode>=1&&mode<=3)){ //�YMAX=0 �h��ܵL��������y
		strcat(data,str);
		printf("�S��������%s��\n",data);
	}
	else printf("�H�U�O�ŦX�����%s�������y\n",str);
}
void Searchfution(Book *books,int total,char *name){
	int Searcharr[200],MAX,mode;
	char str[50];
	do{
		MAX=0;
		system("CLS");
		cout<<"�w��"<<name<<endl;	
		cout<<"2.�d�ߥ\��(�ϥΪ�)"<<endl;
		cout<<"	1.�ѦW"<<endl;
		cout<<"	2.�Ѹ�"<<endl;
		cout<<"	3.�X����"<<endl;
		cout<<"	4.�X�����"<<endl;
		cout<<"	5.�n�X�ê�^�D�e��"<<endl;
		Numberinput(str,NULL);	//�ϥ�Numberinput�禡�T�O��J�����
		mode=atoi(str);	//�ഫstr�����
		switch(mode){
		case 1:
			cout<<"�j�M�ѦW"<<endl;
			NAMESearch(books,total,Searcharr,MAX); //�j�M�ѦW����r�禡
			break;
		case 2:
			cout<<"�j�M�Ѹ�"<<endl;
			IDSearch(books,total,Searcharr,MAX);  //�j�M�Ѹ��禡
			break;
		case 3:
			cout<<"�j�M�X����"<<endl;
			PUBLISHERSearch(books,total,Searcharr,MAX);	//�j�M�X�����W������r�禡
			break;
		case 4:
			cout<<"�j�M���"<<endl;
			DATASearch(books,total,Searcharr,MAX);		//�j�M����禡
			break;
		case 5:
			cout<<"�N���}�d�ߥ\��"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
		}
		if(MAX>0){	//�C�L�ҴM�쪺���y���
			printf("%5s|%45s|%25s|%12s|%10s|%10s|\n","ID","�ѦW","�X����","�X�����","�ɥX�q","�w�s�q");
			cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
			for(int i=0;i<MAX;i++){
				int tmp=Searcharr[i];
				printf("%5d|%45s|%25s|%12s|%10d|%10d|\n",books[tmp].ID,books[tmp].name,books[tmp].publisher,books[tmp].publicationDate,books[tmp].lendout,books[tmp].remaining);
				cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
			}
		}
		system("pause");
	}while(mode!=5);
}

void RenewMemberData(Member *user,int IDidnex){
	char str[50];
	int mode;
	do{
		system("CLS");
		cout<<"�|��"<<user[IDidnex].name<<endl;
		cout<<"���|�����"<<endl;
		cout<<"	1.�K�X"<<endl;
		cout<<"	2.�W�r"<<endl;
		cout<<"	3.Email"<<endl;
		cout<<"	4.�a�}"<<endl;
		cout<<"	5.������X"<<endl;
		cout<<"	6.�n�X�ê�^��s�\��"<<endl;
		Numberinput(str,"�������"); //�ϥ�Numberinput�禡�T�O��J�����
		mode = atoi(str); //�Nstr�ഫ�����
		switch (mode)
		{
		case 1:
			if(AuthInput(str,"�s�K�X")){ //���ҽX��J�P�_ �Y���ҽX��J�� �h��令�\
				if(strcmp(str,user[IDidnex].password)==0)cout<<"�P����K�X�ۦP"<<endl; //�P�_�O�_�P���ƬۦP
				else{
					strcpy(user[IDidnex].password,str);
					cout<<"�K�X��s����!"<<endl;
				}
			}
			else cout<<"���ҽX��J����"<<endl;
			break;
		case 2:
			if(AuthInput(str,"�s�W�r")){ //���ҽX��J�P�_ �Y���ҽX��J�� �h��令�\
				if(strcmp(str,user[IDidnex].name)==0)cout<<"�P����W�r�ۦP"<<endl;//�P�_�O�_�P���ƬۦP
				else {
					strcpy(user[IDidnex].name,str);
					cout<<"�W�r��s����!"<<endl;
				}
			}
			else cout<<"���ҽX��J����"<<endl;
			break;
		case 3:
			if(AuthInput(str,"�sEamil")){ //���ҽX��J�P�_ �Y���ҽX��J�� �h��令�\
				if(strcmp(str,user[IDidnex].email)==0)cout<<"�P���Email�ۦP"<<endl;//�P�_�O�_�P���ƬۦP
				else {
					strcpy(user[IDidnex].email,str);
					cout<<"Email��s����!"<<endl;
				}
			}
			else cout<<"���ҽX��J����"<<endl;
			break;
		case 4:
			if(AuthInput(str,"�s�a�}")){ //���ҽX��J�P�_ �Y���ҽX��J�� �h��令�\
				if(strcmp(str,user[IDidnex].adress)==0)cout<<"�P����a�}�ۦP"<<endl;//�P�_�O�_�P���ƬۦP
				else {
					strcpy(user[IDidnex].adress,str);
					cout<<"�a�}��s����!"<<endl;
				}
			}
			else cout<<"���ҽX��J����"<<endl;
			break;
		case 5:
			if(AuthInput(str,"�s������X")){ //���ҽX��J�P�_ �Y���ҽX��J�� �h��令�\
				if(strcmp(str,user[IDidnex].cellNumber)==0)cout<<"�P����q�ܸ��X�ۦP"<<endl;//�P�_�O�_�P���ƬۦP
				else {
					strcpy(user[IDidnex].cellNumber,str);
					cout<<"������X��s����!"<<endl;
				}
			}
			else cout<<"���ҽX��J����"<<endl;
			break;
		case 6:
			cout<<"�N���}���t��"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
			break;
		}
		system("pause");
	}while(mode!=6);
}

void RenewBookData(Book *books,int total,char *name){
	int BookIndex,mode,amount;
	char str[50];
	do{
		system("CLS");
		cout<<"�w�� "<<name<<endl;
		PrintAllBook(books,total); //�C�L�Ҧ����y���
		cout<<"��s���y���"<<endl;
		cout<<"	1.���y�W��"<<endl;
		cout<<"	2.�X�����W��"<<endl;
		cout<<"	3.���y�`��"<<endl;
		cout<<"	4.�X�����"<<endl;
		cout<<"	5.�n�X��^��s�\��"<<endl;
		Numberinput(str,NULL); //�ϥ�Numberinput�禡�T�O��J�����
		mode=atoi(str); //�Nstr�ഫ�����
		if(mode>=1&&mode<=4){
			Numberinput(str,"�Ѹ�"); //�ϥ�Numberinput�禡�T�O��J�����
			BookIndex=BookCheck(str,books,total); //�j�M�Ѹ��O�_�s�b
			if(BookIndex!=-1){
				switch (mode)
				{
				case 1:
					cout<<"�п�J�U�����y�W��:";
					cin.get();  //�N�W����buffer���r��M�� �קKcin.getlineŪ����
					cin.getline(str,50); //���Ū��(�]�t����r��)
					if(strcmp(books[BookIndex].name,str)==0)cout<<"�P����ѦW�ۦP"<<endl; //�P�_�O�_�P���ƬۦP
					else {
						strcpy(books[BookIndex].name,str);
						cout<<"��令�\!"<<endl;
					}
					break;
				case 2:
					cout<<"�п�J�U���X�����W��:";
					cin.get();  //�N�W����buffer���r��M�� �קKcin.getlineŪ����
					cin.getline(str,50); //���Ū��(�]�t����r��)
					if(strcmp(books[BookIndex].publisher,str)==0)cout<<"�P����X�����ۦP"<<endl; //�P�_�O�_�P���ƬۦP
					else {
						strcpy(books[BookIndex].publisher,str);
						cout<<"��令�\!"<<endl;
					}
					break;
				case 3:
					Numberinput(str,"�U���ƶq"); //�ϥ�Numberinput�禡�T�O��J�����
					amount=atoi(str);  //�Nstr�ഫ�����
					if(amount<(books[BookIndex].lendout)||(amount<(books[BookIndex].lendout+books[BookIndex].remaining))){
						cout<<"���~!!�ƶq�p��ɥX���ƶq���`��"<<endl;  //�P�_���ƶq�O�_�C��ɥX�q
					}
					else if(amount==(books[BookIndex].remaining+books[BookIndex].lendout))cout<<"�P����ƶq�ۦP"<<endl; //�P�_�O�_�P���ƬۦP
					else {
						books[BookIndex].remaining=amount-books[BookIndex].lendout;
						cout<<"��令�\"<<endl;
					}
					break;
				case 4:
					cout<<"�п�J�U�����(YYYY/MM/DD):";
					char tmp[20];
					cin>>str;
					strcpy(tmp,str);
					if(dataDECODER(str)==-1)cout<<"���~�榡!��異��"<<endl; //�P�_����榡�O�_���T
					else {
						if(strcmp(books[BookIndex].publicationDate,tmp)==0)cout<<"�P����X������ۦP"<<endl;
						else {
							strcpy(books[BookIndex].publicationDate,tmp);
							cout<<"��令�\!"<<endl;
						}
					}
					break;
				default:
					break;
				}
			}
			else cout<<"�L�j�M����"<<endl;
		}
		else if(mode==5)cout<<"�N���}��s�\��"<<endl;
		else cout<<"�L���\��"<<endl;
		system("pause");
	}while(mode!=5);
}
void Renewfution(Book *books,Member *user,Administator *admin,Total &total){
	char str[20];
	int IDindex,mode;
	do{
		system("CLS");
		cout<<"3��s�\��"<<endl;
		cout<<"	1.��s���y���(�޲z��)"<<endl;
		cout<<"	2.��s�|���̤j�ɾ\�q(�޲z��)"<<endl;
		cout<<"	3.��s�|�����(�ϥΪ�)"<<endl;
		cout<<"	4.��^�D�e��"<<endl;
		Numberinput(str,NULL);	//�ϥ�Numberinput�禡�T�O��J�����
		mode=atoi(str); //str����
		switch(mode){
		case 1:
			cout<<"��s���y���"<<endl;
			IDindex=AdministatorLogin(admin,total); //�޲z���n�J�^�Ǻ޲z�����ޭ�
			strcpy(str,admin[IDindex].account); //�N�޲z���W�r��bstr
			RenewBookData(books,total.Book,str); //�I�s���y��s�n��
			break;
		case 2:
			cout<<"��s�|���̤j�ɾ\�ƶq���"<<endl;
			IDindex=AdministatorLogin(admin,total); //�޲z���n�J�^�Ǻ޲z�����ޭ�
			cout<<"�w�� "<<admin[IDindex].account<<endl;
			cout<<"�H�U�O�Ҧ��|�����̤j�ɾ\�ƶq:"<<endl;
			printf("%5s|%20s|%12s|\n","ID","�W�r","�̤j�ɾ\�q");
			for(int i=0;i<total.Member;i++){	//��ܩҦ��ϥΪ̪��̤j�ɾ\�q
				cout<<"-----------------------------------------"<<endl;
				printf("%5d|%20s|%12d|\n",user[i].ID,user[i].name,user[i].MAXlendamount);
			}
			cout<<"-----------------------------------------"<<endl;
			Numberinput(str,"����諸�ϥΪ�ID");
			IDindex=MemberCheck(str,user,total.Member);	//�ˬd�ϥΪ�ID�^�Ǩ�Ҧb���ޭ�
			if(IDindex!=-1){
				Numberinput(str,"�����ƶq");	//�ϥ�Numberinput�禡�T�O��J�����
				int amount=atoi(str);	//str����
				if(amount<(user[IDindex].lendtatal)){	//�P�_�ƶq�O�_�C��ثe�ɾ\�`��
					cout<<"���~!!�ƶq�p��w�ɤJ�ƶq"<<endl;
				}
				else {
					user[IDindex].MAXlendamount=amount;
					cout<<"��令�\"<<endl;
				}
			}
			else {
				cout<<"�d�L��ID"<<endl;
			}
			system("pause");
			break;
		case 3:
			cout<<"��s�|���ӤH���"<<endl;
			IDindex=MemberLogin(user,total); //�|���n�J�^�Ǻ޲z�����ޭ�
			RenewMemberData(user,IDindex);
			break;
		case 4:
			cout<<"�N���}�æ^��D���"<<endl;
			system("pause");
			break;
		default:
			cout<<"�L���\��"<<endl;
			system("pause");
			break;
		}
	}while(mode!=4);
}

void BorrowBook(Book *books,Member *user,Total &total,int userIDindex){
	char str[50];
	cout<<"�ɮѥ\��"<<endl;
	Numberinput(str,"���ɾ\�Ѹ�");	//�ϥ�Numberinput�禡�T�O��J�����
	int arrPosition=BookCheck(str,books,total.Book);	//�j�M�Ѹ��O�_�s�b�O�^�ǮѸ������ޭȧ_�h�^��-1
	int BookID=books[arrPosition].ID,max;
	if(arrPosition!=-1){	//�P�_�O�_������
		cout<<"--------------------------------------"<<endl;
		cout<<"�Ѹ�:"<<books[arrPosition].ID<<endl;
		cout<<"�ѦW:"<<books[arrPosition].name<<endl;
		cout<<"�X����:"<<books[arrPosition].publisher<<endl;
		cout<<"�X�����:"<<books[arrPosition].publicationDate<<endl;
		cout<<"�w�ɥX�ƶq:"<<books[arrPosition].lendout<<endl;
		cout<<"�]���w�s�ƶq:"<<books[arrPosition].remaining<<endl;
		cout<<"--------------------------------------"<<endl;
		Numberinput(str,"���ɾ\�ƶq");	//�ϥ�Numberinput�禡�T�O��J�����
		int amount = atoi(str);
		if((amount+user[userIDindex].currentbooktatal)>user[userIDindex].MAXlendamount){ //�P�_�ɾ\�ƶq�O�_�W�L�ϥΪ̳̤j�ɾ\�q
			cout<<"���~!!�ɾ\�ƶq�W�L�ϥΪ̳̤j�ɾ\�q"<<endl;	
		}
		else if((amount)>books[arrPosition].remaining){  //�P�_�ɾ\�ƶq�O�_�W�L�w�s�ƶq
			cout<<"���~!!�ɾ\�ƶq�W�L�]���w�s�ƶq"<<endl;	
		}
		else if(amount==0){		//�P�_��J��0
			cout<<"�Фſ�J0"<<endl;
		}
		else { //���\�ɮ�
			books[arrPosition].lendout+=amount;
			books[arrPosition].remaining-=amount;
			if(Checkuserlend(BookID,userIDindex,user)==-1){ 
				//�I�sCheckuserlend�禡�ˬd�ϥΪ̬O�_���ɳo����
				//�Y�L�h�s�W�Ѹ��ܰ}�C
				max=user[userIDindex].lendtatal;
				user[userIDindex].lendid[max]=BookID;
				user[userIDindex].lendamount[max]=amount;
				user[userIDindex].lendtatal++;
			}
			else{
				//�j�M�b�ϥέɾ\���}�C�W�[�ƶq
				max=Checkuserlend(BookID,userIDindex,user);
				user[userIDindex].lendamount[max]+=amount;
			}
			user[userIDindex].currentbooktatal+=amount; //�b�ϥΪ̭ɾ\���y�`�ƼW�[�ƶq
			cout<<"�ɾ\���\!!"<<endl; //���\�T��
		}
	}
	else {
		cout<<"���~!!�d�L����"<<endl;
	}
}
void RetuenBook(Book *books,Member *user,Total &total,int userIDindex){
	cout<<"�ٮѥ\��"<<endl<<"�H�U�O�z�Ҧ��ɾ\�����y"<<endl;
	printf("%5s|%45s|%10s|\n","�Ѹ�","�ѦW","�ɾ\�ƶq");	//�C�L�Ҧ��ɾ\���y
	for(int i=0;i<user[userIDindex].lendtatal;i++){
		int bookid=user[userIDindex].lendid[i];
		char IDstr[10];
		itoa(bookid, IDstr,10);		//�N�Ѹ��ন�r��榡
		int position= BookCheck(IDstr,books,total.Book);	//�I�sBookCheck�禡�j�M�Ѹ������ޭ�
		cout<<"--------------------------------------------------------------------"<<endl;
		printf("%5d|%45s|%10d|\n",bookid,books[position].name,user[userIDindex].lendamount[i]);
	}
	cout<<"--------------------------------------------------------------------"<<endl;
	char str[20];
	Numberinput(str,"���k�ٮѸ�");	//�ϥ�Numberinput�禡�T�O��J�����
	int ReturnID=atoi(str);
	int lendIDposition=Checkuserlend(ReturnID,userIDindex,user);	//�ˬd�ϥΪ̬O�_�ɾ\����
	int arrPosition=BookCheck(str,books,total.Book);	//�I�sBookCheck�禡�j�M�Ѹ������ޭ�
	if(lendIDposition!=-1){		//�����ٮѰʧ@
		books[arrPosition].remaining+=user[userIDindex].lendamount[lendIDposition];
		books[arrPosition].lendout-=user[userIDindex].lendamount[lendIDposition];
		user[userIDindex].currentbooktatal-=user[userIDindex].lendamount[lendIDposition];
		for(int i=lendIDposition;i<user[userIDindex].lendtatal-1;i++){	//�R��������
			user[userIDindex].lendamount[i]=user[userIDindex].lendamount[i+1];
			user[userIDindex].lendid[i]=user[userIDindex].lendid[i+1];
		}
		user[userIDindex].lendtatal--;
		cout<<"�����ٮ�!"<<endl;
	}
	else {
		cout<<"�L�ɦ���"<<endl;
	}
}
void BorrowFuntion(Book *books,Member *user,Total total,int IDindex){
	char str[10];
	int mode;
	do{
		system("CLS");
		cout<<"�w��"<<user[IDindex].name<<endl;
		cout<<"2���ٮѥ\��"<<endl;
		cout<<"	1.���y�ɾ\"<<endl;
		cout<<"	2.���y�k��"<<endl;
		cout<<"	3.�n�X�����}"<<endl;
		Numberinput(str,"���ϥΥ\��");	//�ϥ�Numberinput�禡�T�O��J�����
		mode=atoi(str);	//�N�r���ഫ�����
		switch (mode)	//���ӿ諸�Ҧ����椣�P���\��
		{
		case 1:
			BorrowBook(books,user,total,IDindex);	//�I�s�ɮѨ禡
			break;
		case 2:
			if(user[IDindex].lendtatal==0)cout<<"�ϥΪ̵L�ɾ\������y"<<endl;	//�P�_�ϥΪ̬O�_���ɾ\���y
			else RetuenBook(books,user,total,IDindex);	//�ٮѨ禡
			break;
		case 3:
			cout<<"�N���}���ٮѥ\��"<<endl;	//��J3�����ɾ\�\��
			break;
		default:
			cout<<"�L���\��"<<endl;	//��L�Ʀr�ɿﶵ
			break;
		}
		system("pause");
	}while(mode!=3); //��J3 ���}�L���j��
}

void AddBook(Book *books,Total &total){
	char str[20],tmp[20];
	Numberinput(str,"���s�W�Ѹ�");  //�ϥ�Numberinput�禡�T�O��J�����
	int arrID=BookCheck(str,books,total.Book);  //�j�M�Ѹ��O�_�s�b
	if(arrID==-1){  //�s�W���y
		int index=total.Book;
		books[index].ID=atoi(str);
		cin.get();	//�N�W����buffer���r��M�� �קKcin.getlineŪ����
		cout<<"�п�J�ѦW:";
		cin.getline(books[index].name,50); //���Ū��(�]�t����r��)
		cout<<"�п�J�X����:";
		cin.getline(books[index].publisher,50); //���Ū��(�]�t����r��)
		cout<<"�п�J�X�����(YYYY/MM/DD):";
		cin>>str;
		strcpy(tmp,str);
		while(dataDECODER(str)==-1){  //�P�_����榡�O�_���T
			cout<<"��J���~!�Э��s��J!"<<endl;
			cout<<"�п�J�X�����(YYYY/MM/DD):";
			cin>>str;
			strcpy(tmp,str);
		}
		strcpy(books[index].publicationDate,tmp);
		Numberinput(str,"���y�ƶq");  //�ϥ�Numberinput�禡�T�O��J�����
		books[index].remaining = atoi(str);
		books[index].lendout = 0;
		total.Book++;
		cout<<"�s�W���\!!"<<endl;
		for(int i=0;i<total.Book-1;i++){   //�ھڮѸ��ƦC
			for(int j=i+1;j<total.Book;j++){
				if(books[i].ID>books[j].ID){
					Book tmp; 
					tmp=books[i];
					books[i]=books[j];
					books[j]=tmp;
				}
			}
		}
	}
	else {
		cout<<"���~!!�Ѹ�����"<<endl;
	}
}

void DeleteBook(Book *books,Total &total){
	char str[20];
	PrintAllBook(books,total.Book);  //�C�L�Ҧ����y
	Numberinput(str,"���R���Ѹ�");	//�ϥ�Numberinput�禡�T�O��J�����
	int arrID=BookCheck(str,books,total.Book);  //�M�Ѹ��O�_�s�b
	if(arrID==-1){
		cout<<"���~!�d�L���Ѹ�"<<endl;
	}
	else if(books[arrID].lendout>0){  //�Y�٦��ѭɥX�h�L�k�R��
		cout<<"���~!���y�|���ɥX �L�k�R��"<<endl;
	}
	else {
		for(int i=arrID;i<total.Book-1;i++){ //�Q�ΰj��N�쥻������л\
			books[i]=books[i+1];
		}
		total.Book--;
		cout<<"�R�����\!!"<<endl;

	}
}

void AddMember(Member *user,Total &total){
	char str[20];
	Numberinput(str,"���s�WID"); //�ϥ�Numberinput�禡�T�O��J�����
	int arrID=MemberCheck(str,user,total.Member); //�j�M�|���O�_�s�b
	if(arrID==-1){
		int index=total.Member;
		user[index].ID = atoi(str);
		cout<<"�п�J�b��:";
		cin>>str;
		arrID=MemberAccountCheck(str,user,total.Member); //�j�M�b���O�_���ϥιL
		if(arrID==-1){
			strcpy(user[index].account,str);
			cout<<"�п�J�K�X:";
			cin>>user[index].password;
			cout<<"�п�J�m�W:";
			cin>>user[index].name;
			cout<<"�п�Jemail:";
			cin>>user[index].email;
			cout<<"�п�J�a�}:";
			cin>>user[index].adress;
			cout<<"�п�J������X:";
			cin>>user[index].cellNumber;
			Numberinput(str,"�̤j�ϥΪ̭ɾ\�q");  //�ϥ�Numberinput�禡�T�O��J�����
			user[index].MAXlendamount = atoi(str);
			user[index].currentbooktatal=0;
			user[index].lendtatal=0;
			total.Member++;
			cout<<"�s�W���\!!"<<endl;
			for(int i=0;i<total.Member-1;i++){  //�ھ�ID�Ƨ�
				for(int j=i+1;j<total.Member;j++){
					if(user[i].ID>user[j].ID){
						Member tmp;
						tmp=user[i];
						user[i]=user[j];
						user[j]=tmp;
					}
				}
			}
		}
		else cout<<"���~!!�b������"<<endl;
	}
	else {
		cout<<"���~!!ID����"<<endl;
	}
}
void DeleteMember(Member *user,Total &total){
	char str[20];
	Numberinput(str,"���R���ϥΪ�ID"); //�ϥ�Numberinput�禡�T�O��J�����
	int arrID=MemberCheck(str,user,total.Member); //�j�MID�O�_�s�b
	if(arrID==-1){
		cout<<"���~!�d�L��ID"<<endl;
	}
	else if(user[arrID].lendamount>0){ //�Y�ϥΪ̤����ɾ\���y �h�L�k�R��
		cout<<"���~!�ϥΪ̩|���ɾ\���y �L�k�R��"<<endl;
	}
	else {
		for(int i=arrID;i<total.Member-1;i++){	//�Q�ΰj��N�쥻������л\
			user[i]=user[i+1];
		}
		total.Member--;
		cout<<"�R�����\!!"<<endl;
	}
}
void Addfution(Book *books,Member* user,Administator *admin,Total &total){
	char str[50];
	int mode,arrID;
	arrID=AdministatorLogin(admin,total);  //�޲z���n�J�^�Ǻ޲z���Ҧb���ޭ�
	do{
		system("CLS");
		cout<<"�w��"<<admin[arrID].account<<endl;
		cout<<"4�s�W�\��"<<endl;
		cout<<"	1.�s�W���y"<<endl;
		cout<<"	2.�R�����y"<<endl;
		cout<<"	3.�s�W�|��"<<endl;
		cout<<"	4.�R���|��"<<endl;
		cout<<"	5.�n�X�ê�^�D���"<<endl;
		Numberinput(str,NULL);  //�ϥ�Numberinput�禡�T�O��J�����
		mode=atoi(str);
		switch (mode)
		{
		case 1:
			cout<<"�s�W���y"<<endl;
			AddBook(books,total); //�I�s�s�W���y�禡
			break;
		case 2:
			cout<<"�R�����y"<<endl;
			DeleteBook(books,total); //�I�s�R�����y�禡
			break;
		case 3:
			cout<<"�s�W�|��"<<endl;
			AddMember(user,total);  //�I�s�s�W�|���禡
			break;
		case 4:
			cout<<"�s�W�|��"<<endl;
			DeleteMember(user,total); //�I�s�R���|���禡
			break;
		case 5:
			cout<<"�N�����s�W�\��ê�^�D���"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
			break;
		}
		system("pause");
	}while(mode!=5);
}