#include<iostream>
#include<fstream>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <cstring>
using namespace std;
class Member{
public:
	int id[20];	
	char account[20][20];
	char password[20][20];
	char name[20][20];
	char email[20][20];
	char adress[20][20];
	char cellNumber[20][15];
	int MAX[20];
	int currentbooktatal[20];
	int lendtatal[20];
	int lendid[20][50];
	int lendamount[20][50];
	int total;
	void ReadData(char *);
	void WriteData(char *);
	int accountcheck(char *);
	int IDcheck(int ID);
	int login();
	int bookidsearch(int,int);
	void DataRenew(int );
	void MaxRenew();
	void Add();
	void Delete();
};
class Book
{
public:
	char name[50][50];
	int id[50];
	char publisher[50][50];
	int date[50];
	int amount[50];
	int lendout[50];
	int total;
	void ReadData(char *);
	void WriteData(char *);
	void printData();
	int IDcheck(int ID);
	void SearchPrint(int ,int *);
	void DataRenew();
	void Add();
	void Delete();
};
class Administator{
public:
	char account[20][20];	
	char password[20][20];	
	int total;
	void ReadData(char *);
	int accountcheck(char *);
	int login();
};
void datedecoder(int);
bool datechecker(int,int,int);
void BorrowFuntion(Member &,Book &,int );
void ReturnFuntion(Member &,Book &,int );
void SearchFuntion(Book &);
void MemberFuntion(Member &,Book &,int );
void AdministatorFuntion(Member &,Book &,Administator &,int );
void main(){
	int n,index;
	Member users;
	Book books;
	Administator admins;
	users.ReadData("Members.dat");
	books.ReadData("Books.dat");
	admins.ReadData("Administators.dat");
	do{
		system("CLS");
		cout<<"�п��\n1.�ϥΪ�\n2.�޲z��\n3.���}���t��\n�п�J"<<endl;
		cin>>n;
		switch (n)
		{
		case 1:
			index=users.login();
			//index=0;
			if(index!=-1)MemberFuntion(users,books,index);
			else {
				cout<<"�n�J����"<<endl;
				system("pause");
			}
			break;
		case 2:
			index=admins.login();
			if(index!=-1)AdministatorFuntion(users,books,admins,index);
			else {
				cout<<"�n�J����"<<endl;
				system("pause");
			}
			break;
		case 3:
			cout<<"�N���}�t��"<<endl;
			system("pause");
			break;
		default:
			cout<<"�L���\��"<<endl;
			system("pause");
			break;
		}
	}while(n!=3);
	users.WriteData("Members.dat");
	books.WriteData("Books.dat");
} 

void Member::ReadData(char *Filename){
	ifstream fin(Filename);
	total=0;
	while (!fin.eof()){
		fin>>id[total]>>account[total]>>password[total]>>name[total]>>email[total]>>adress[total]>>cellNumber[total]>>MAX[total]>>currentbooktatal[total]>>lendtatal[total];
		for(int i=0;i<lendtatal[total];i++){
			fin>>lendid[total][i]>>lendamount[total][i];
		}
		total++;
	}
	fin.close();
}
void Member::WriteData(char *Filename){
	ofstream fout(Filename);
	for(int i=0;i<total;i++){
		fout<<id[i]<<" "<<account[i]<<" "<<password[i]<<" "<<name[i]<<" "<<email[i]<<" "<<adress[i]<<" "<<cellNumber[i]<<" "<<MAX[i]<<" "<<currentbooktatal[i]<<" "<<lendtatal[i];
		for(int j=0;j<lendtatal[i];j++){
			fout<<endl<<lendid[i][j]<<" "<<lendamount[i][j];
		}
		if(i<total-1)fout<<endl;
	}
	fout.close();
}
int Member::accountcheck(char *str){
	for(int i=0;i<total;i++){
		if(strcmp(account[i],str)==0)return i;
	}
	return -1;
}
int Member::IDcheck(int ID){
	for(int i=0;i<total;i++){
		if(id[i]==ID)return i;
	}
	return -1;
}
int Member::login(){
	char str1[20],str2[20];
	cout<<"�п�J�b��:";
	cin>>str1;
	cout<<"�п�J�K�X:";
	cin>>str2;
	int index=accountcheck(str1);
	if(index!=-1){
		if(strcmp(password[index],str2)==0){
			return index;
		}
		return -1;
	}
	else return -1;
}
int Member::bookidsearch(int userindex,int borrowid){
	for(int i=0;i<lendtatal[userindex];i++){
		if(lendid[userindex][i]==borrowid)return i;
	}
	return -1;
}
void Book::ReadData(char *Filename){
	ifstream fin(Filename);
	total=0;
	while (!fin.eof()){
		fin>>id[total]>>lendout[total]>>amount[total]>>name[total]>>publisher[total]>>date[total];
		total++;
	}
	fin.close();
}
void Book::WriteData(char *Filename){
	ofstream fout(Filename);
	for(int i=0;i<total;i++){
		fout<<id[i]<<" "<<lendout[i]<<" "<<amount[i]<<" "<<name[i]<<" "<<publisher[i]<<" "<<date[i];
		if(i<total-1)fout<<endl;
	}
	fout.close();
}
void Book::printData(){
	cout<<setw(5)<<"�Ѹ�"<<setw(5)<<"�w�s"<<setw(5)<<"�ɥX"<<setw(50)<<"�ѦW"<<setw(20)<<"�X����"<<setw(15)<<"�X�����"<<endl;
	for(int i=0;i<total;i++){
		cout<<setw(5)<<id[i]<<setw(5)<<amount[i]<<setw(5)<<lendout[i]<<setw(50)<<name[i]<<setw(20)<<publisher[i]<<setw(15);
		datedecoder(date[i]);
		cout<<endl;
	}
}
int Book::IDcheck(int ID){
	for(int i=0;i<total;i++){
		if(id[i]==ID)return i;
	}
	return -1;
}
void Book::SearchPrint(int total,int *arr){
	if(total>0){
		cout<<setw(5)<<"�Ѹ�"<<setw(5)<<"�w�s"<<setw(5)<<"�ɥX"<<setw(50)<<"�ѦW"<<setw(20)<<"�X����"<<setw(12)<<"�X�����"<<endl;
		for(int i=0;i<total;i++){
			int tmp=arr[i];
			cout<<setw(5)<<id[tmp]<<setw(5)<<amount[tmp]<<setw(5)<<lendout[tmp]<<setw(50)<<name[tmp]<<setw(20)<<publisher[tmp]<<setw(12);
			datedecoder(date[tmp]);
			cout<<endl;
		}
	}
	else cout<<"�d�L�������"<<endl;
}
void Administator::ReadData(char *Filename){
	ifstream fin(Filename);
	total=0;
	while (!fin.eof()){
		fin>>account[total]>>password[total];
		total++;
	}
	fin.close();
}
int Administator::accountcheck(char *str){
	for(int i=0;i<total;i++){
		if(strcmp(account[i],str)==0)return i;
	}
	return -1;
}
int Administator::login(){
	char str1[20],str2[20];
	cout<<"�п�J�b��:";
	cin>>str1;
	cout<<"�п�J�K�X:";
	cin>>str2;
	int index=accountcheck(str1);
	if(index!=-1){
		if(strcmp(password[index],str2)==0){
			return index;
		}
		return -1;
	}
	else return -1;
}
void datedecoder(int date){
	char tmp[20];
	*(tmp)=char(date/10000000+'0');
	*(tmp+1)=char(date%10000000/1000000+'0');
	*(tmp+2)=char(date%1000000/100000+'0');
	*(tmp+3)=char(date%100000/10000+'0');
	*(tmp+4)='/';
	*(tmp+5)=char(date%10000/1000+'0');
	*(tmp+6)=char(date%1000/100+'0');
	*(tmp+7)='/';
	*(tmp+8)=char(date%100/10+'0');
	*(tmp+9)=char(date%10+'0');
	*(tmp+10)='\0';
	cout<<tmp;
}
bool datechecker(int y,int m,int d){
	int day[14]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(y%4==0&&y%100!=0||y%400==0)day[2]=29;
	if(m<=0||m>12)return false;
	if(day[m]<=0||d>day[m])return false;
	return true;
}
void BorrowFuntion(Member &users,Book &books,int userindex){
	int borrowid,amount;
	cout<<"�п�J�Ѹ�:";
	cin>>borrowid;
	int bookindex=books.IDcheck(borrowid);
	if(bookindex!=-1){
		cout<<setw(5)<<"�Ѹ�"<<setw(5)<<"�w�s"<<setw(5)<<"�ɥX"<<setw(50)<<"�ѦW"<<setw(20)<<"�X����"<<setw(12)<<"�X�����"<<endl;
			cout<<setw(5)<<books.id[bookindex]<<setw(5)<<books.amount[bookindex]<<setw(5)<<books.lendout[bookindex]<<setw(50)<<books.name[bookindex]<<setw(20)<<books.publisher[bookindex]<<setw(12);
			datedecoder(books.date[bookindex]);
			cout<<endl;
		cout<<"�п�J�ƶq:";
		cin>>amount;
		if(((amount+users.currentbooktatal[userindex])>users.MAX[userindex])){
			cout<<"�W�L�ϥΪ̳̤j�ɾ\�q"<<endl;
		}
		else if(amount<0&&amount>books.amount[bookindex]){
			cout<<"�W�L�w�s�q�μƶq�p�󵥩�0"<<endl;
		}
		else {
			int borrowindex=users.bookidsearch(userindex,borrowid);
			if(borrowindex==-1){
				int total=users.lendtatal[userindex];
				users.lendid[userindex][total]=borrowid;
				users.lendamount[userindex][total]=amount;
				users.lendtatal[userindex]++;
			}
			else users.lendamount[userindex][borrowindex]+=amount;
			users.currentbooktatal[userindex]+=amount;
			books.amount[bookindex]-=amount;
			books.lendout[bookindex]+=amount;
			cout<<"�ɾ\���\"<<endl;
		}
	}
	else cout<<"�L���Ѹ�"<<endl;
}
void ReturnFuntion(Member &users,Book &books,int userindex){
	int borrowid,amount;
	cout<<"�п�J�k�ٮѸ�:";
	cin>>borrowid;
	int borrowindex=users.bookidsearch(userindex,borrowid);
	int bookindex=books.IDcheck(borrowid);
	if(borrowindex!=-1){
		cout<<"�п�J�k�ټƶq:";
		cin>>amount;
		if(amount>0&&amount<=users.lendamount[userindex][borrowindex]){
			if(amount==users.lendamount[userindex][borrowindex]){
				for(int i=borrowindex+1;i<users.lendtatal[userindex];i++){
					users.lendamount[userindex][i-1]=users.lendamount[userindex][i];
					users.lendid[userindex][i-1]=users.lendid[userindex][i];
				}
				users.lendtatal[userindex]--;
			}
			else {
				users.lendamount[userindex][borrowindex]-=amount;
			}
			users.currentbooktatal[userindex]-=amount;
			books.amount[bookindex]+=amount;
			books.lendout[bookindex]-=amount;
			cout<<"�k�٦��\"<<endl;
		}
		else cout<<"�Фſ�J���ŦX���ƶq"<<endl;
	}
	else {
		if(bookindex==-1)cout<<"�Ѹ����s�b"<<endl;
		else cout<<"�L�ɾ\����"<<endl;
	}
}
void SearchFuntion(Book &books){
	int n,searchindex[100],total=0,num,year,month,day,state=1;
	char str[100];
	cout<<"��Ʒj�M\n1.�ѦW\n2.�Ѹ�\n3.�X����\n4.�X�����"<<endl;
	cin>>n;
	switch (n)
	{
	case 1:
		cout<<"�п�J����r:";
		cin>>str;
		for(int i=0;i<books.total;i++){
			char *tmp=strstr(books.name[i],str);  
			if(tmp!=NULL){
				searchindex[total]=i; 
				total++;  
			}
		}
		break;
	case 2:
		cout<<"�п�J�Ѹ�:";
		cin>>num;
		if(books.IDcheck(num)!=-1){
			searchindex[total]=books.IDcheck(num); 
			total++;  
		}
		break;
	case 3:
		cout<<"�п�J����r:";
		cin>>str;
		for(int i=0;i<books.total;i++){
			char *tmp=strstr(books.publisher[i],str);  
			if(tmp!=NULL){
				searchindex[total]=i; 
				total++;  
			}
		}
		break;
	case 4:
		cout<<"�п�J���(YYYY/MM/DD):";
		cin>>year;
		cin.ignore();
		cin>>month;
		cin.ignore();
		cin>>day;
		if(datechecker(year,month,day)){
			int searchdate=year*10000+month*100+day;
			cout<<"�p��j�M���:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate>books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
			total=0;
			cout<<"����j�M���:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate==books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
			total=0;
			cout<<"�j��j�M���:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate<books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
		}
		else cout<<"����榡���~"<<endl;
		break;
	default:
		cout<<"�L���\��"<<endl;
		break;
	}
	if(n!=4)books.SearchPrint(total,searchindex);
}
void Member::DataRenew(int userindex){
	char code[40]={"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	char SecurityCode[10]={NULL},str[50],inputcode[10];
	int n;
	srand(time(NULL));
	for(int i=0;i<5;i++)SecurityCode[i]=code[rand()%36];
	SecurityCode[5]='\0';
	cout<<"���|�����"<<endl;
	cout<<"1.�K�X\n2.�W�r\n3.Email\n4.�a�}\n5.������X"<<endl;
	cout<<"�п�J:";
	cin>>n;
	switch (n)
	{
	case 1:
		cout<<"�п�J�s�K�X:";
		cin>>str;
		cout<<SecurityCode<<"\n�п�J���ҽX:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(password[userindex],str);
			cout<<"��令�\"<<endl;
		}
		else cout<<"���ҽX���~"<<endl;
		break;
	case 2:
		cout<<"�п�J�s�W�r:";
		cin>>str;
		cout<<SecurityCode<<"\n�п�J���ҽX:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(name[userindex],str);
			cout<<"��令�\"<<endl;
		}
		else cout<<"���ҽX���~"<<endl;
		break;
	case 3:
		cout<<"�п�J�sEmail:";
		cin>>str;
		cout<<SecurityCode<<"\n�п�J���ҽX:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(email[userindex],str);
			cout<<"��令�\"<<endl;
		}
		else cout<<"���ҽX���~"<<endl;
		break;
	case 4:
		cout<<"�п�J�s�a�}:";
		cin>>str;
		cout<<SecurityCode<<"\n�п�J���ҽX:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(adress[userindex],str);
			cout<<"��令�\"<<endl;
		}
		else cout<<"���ҽX���~"<<endl;
		break;
	case 5:
		cout<<"�п�J������X:";
		cin>>str;
		cout<<SecurityCode<<"\n�п�J���ҽX:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(cellNumber[userindex],str);
			cout<<"��令�\"<<endl;
		}
		else cout<<"���ҽX���~"<<endl;
		break;
	default:
		cout<<"�L���\��"<<endl;
		break;
	}
}
void Book::DataRenew(){
	int n,newAmount,year,month,day,ID,bookindex;
	char str[50];
	printData();
	cout<<"��s���y���\n1.���y�W��\n2.�X�����W��\n3.���y�`��\n4.�X�����"<<endl<<"�п�J:";
	cin>>n;
	cout<<"�п�J�Ѹ�:";
	cin>>ID;
	bookindex=IDcheck(ID);
	if(bookindex!=-1){
		switch (n)
		{
		case 1:
			cout<<"�п�J�s�ѦW:";
			cin>>str;
			strcpy(name[bookindex],str);
			cout<<"��令�\"<<endl;
			break;
		case 2:
			cout<<"�п�J�s�X�����W��:";
			cin>>str;
			strcpy(publisher[bookindex],str);
			cout<<"��令�\"<<endl;
			break;
		case 3:
			cout<<"�п�J�s���y�`��:";
			cin>>newAmount;
			if(newAmount>=amount[bookindex]){
				amount[bookindex]=newAmount-lendout[bookindex];
				cout<<"��令�\"<<endl;
			}
			else cout<<"��異��!�C��w�ɥX�Ѷq"<<endl;
			break;
		case 4:
			cout<<"�п�J�s�X�����(YYYY/MM/DD):";
			cin>>year;
			cin.ignore();
			cin>>month;
			cin.ignore();
			cin>>day;
			if(datechecker(year,month,day)){
				amount[bookindex]=year*10000+month*100+day;
				cout<<"��令�\"<<endl;
			}
			else cout<<"����榡���~"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
			break;
		}
	}
	else cout<<"�d�L����"<<endl;
}
void Member::MaxRenew(){
	int ID,newMAX;
	cout<<"�H�U�O�Ҧ��|�����̤j�ɾ\�q"<<endl;
	cout<<setw(5)<<"ID"<<setw(10)<<"�m�W"<<setw(12)<<"�̤j�ɾ\�q"<<setw(10)<<"�ɾ\�`��"<<endl;
	for(int i=0;i<total;i++){
		cout<<setw(5)<<id[i]<<setw(10)<<setw(10)<<name[i]<<setw(12)<<MAX[i]<<setw(10)<<currentbooktatal[i]<<endl;
	}
	cout<<"�п�J�|��ID:";
	cin>>ID;
	int userindex=IDcheck(ID);
	if(userindex!=-1){
		cout<<"�п�J�s���̤j�ɾ\�q:";
		cin>>newMAX;
		if(newMAX>=currentbooktatal[userindex]){
			MAX[userindex]=newMAX;
			cout<<"��令�\!"<<endl;
		}
		else cout<<"����!�C��w�ɾ\�ƶq"<<endl;
	}
	else cout<<"�d�LID�s�b"<<endl;
}
void Book::Add(){
	int newID,year,month,day;
	cout<<"�п�J�s�Ѹ�:";
	cin>>newID;
	if(IDcheck(newID)==-1){
		id[total]=newID;
		cout<<"�п�J�ѦW:";
		cin>>name[total];
		cout<<"�п�J�X����:";
		cin>>publisher[total];
		cout<<"�п�J�X�����(YYYY/MM/DD):";
		cin>>year;
		cin.ignore();
		cin>>month;
		cin.ignore();
		cin>>day;
		while(!datechecker(year,month,day)){
			cout<<"��J���~!�Э��s��J!"<<endl;
			cout<<"�п�J�X�����(YYYY/MM/DD):";
			cin>>year;
			cin.ignore();
			cin>>month;
			cin.ignore();
			cin>>day;
		}
		date[total]=year*10000+month*100+day;
		cout<<"�п�J���y�ƶq:";
		cin>>amount[total];
		lendout[total] = 0;
		total++;
		for(int i=0;i<total-1;i++){
			for(int j=i+1;j<total;j++){
				if(id[i]>id[j]){
					swap(id[i],id[j]);
					swap(name[i],name[j]);
					swap(publisher[i],publisher[j]);
					swap(date[i],date[j]);
					swap(amount[i],amount[j]);
					swap(lendout[i],lendout[j]);
				}
			}
		}
		cout<<"�s�W���\"<<endl;
	}
	else cout<<"�Ѹ�����"<<endl;
}
void Book::Delete(){
	int clearID,bookindex;
	cout<<"�п�J�R���Ѹ�:";
	cin>>clearID;
	if(IDcheck(clearID)!=-1){
		bookindex=IDcheck(clearID);
		if(lendout[bookindex]==0){
			for(int i=bookindex;i<total-1;i++){
				swap(id[i],id[i+1]);
				swap(name[i],name[i+1]);
				swap(publisher[i],publisher[i+1]);
				swap(date[i],date[i+1]);
				swap(amount[i],amount[i+1]);
				swap(lendout[i],lendout[i+1]);
			}
			total--;
			cout<<"�R�����\"<<endl;
		}
		else cout<<"���y�|���ɥX�L�k�R��"<<endl;
	}
	else cout<<"�d�L�Ѹ�"<<endl;
}
void Member::Add(){
	int newID;
	char str[50];
	cout<<"�п�J�sID:";
	cin>>newID;
	if(IDcheck(newID)==-1){
		id[total]=newID;
		cout<<"�п�J�b��:";
		cin>>str;
		if(accountcheck(str)==-1){
			strcpy(account[total],str);
			cout<<"�п�J�K�X:";
			cin>>password[total];
			cout<<"�п�J�m�W:";
			cin>>name[total];
			cout<<"�п�JEmail:";
			cin>>email[total];
			cout<<"�п�J�a�}:";
			cin>>adress[total];
			cout<<"�п�J������X:";
			cin>>cellNumber[total];
			cout<<"�п�J�̦h��ɾ\�����y�ƶq:";
			cin>>MAX[total];
			currentbooktatal[total] = 0;
			lendtatal[total] = 0;
			total++;
			cout<<"�s�W���\"<<endl;
		}
		else cout<<"�b������"<<endl;
	}
	else cout<<"ID����"<<endl;
}
void Member::Delete(){
	int clearID,userindex;
	cout<<"�п�J�R��ID:";
	cin>>clearID;
	if(IDcheck(clearID)!=-1){
		userindex=IDcheck(clearID);
		if(currentbooktatal[userindex]==0){
			for(int i=userindex;i<total-1;i++){
				swap(id[i],id[i+1]);
				swap(account[i],account[i+1]);
				swap(password[i],password[i+1]);
				swap(name[i],name[i+1]);
				swap(email[i],email[i+1]);
				swap(adress[i],adress[i+1]);
				swap(cellNumber[i],cellNumber[i+1]);
				swap(MAX[i],MAX[i+1]);
				swap(currentbooktatal[i],currentbooktatal[i+1]);
				swap(lendtatal[i],lendtatal[i+1]);
				int max=lendtatal[i]>lendtatal[i+1]?lendtatal[i]:lendtatal[i+1];
				for(int j=0;j<max;j++){
					swap(lendid[i][j],lendid[i+1][j]);
					swap(lendamount[i][j],lendamount[i+1][j]);
				}
			}
			total--;
			cout<<"�R�����\"<<endl;
		}
		else cout<<"�ϥΪ̩|���ɮѵL�k�R��"<<endl;
	}
	else cout<<"�d�LID"<<endl;
}
void MemberFuntion(Member &users,Book &books,int userindex){
	int n;
	do{
		system("CLS");
		cout<<"�|��"<<users.name[userindex]<<"\n�п��\n1.�ɮ�\n2.�ٮ�\n3.���y�d��\n4.�|����Ƨ�s\n5.�n�X"<<endl;
		cout<<"�п�J";
		cin>>n;
		switch (n)
		{
		case 1:
			BorrowFuntion(users,books,userindex);
			break;
		case 2:
			ReturnFuntion(users,books,userindex);
			break;
		case 3:
			SearchFuntion(books);
			break;
		case 4:
			users.DataRenew(userindex);
			break;
		case 5:
			cout<<"�N�n�X���\��"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
			break;
		}
		system("pause");
	}while(n!=5);
}
void AdministatorFuntion(Member &users,Book &books,Administator &admins,int adminindex){
	int n;
	do{
		system("CLS");
		cout<<"�п��\n1.���y��Ƨ�s\n2.�|���̤j�ɾ\�q��s\n3.�s�W���y\n4.�R�����y\n5.�s�W�|��\n6.�R���|��\n7.�n�X"<<endl;
		cout<<"�п�J";
		cin>>n;
		switch (n)
		{
		case 1:
			books.DataRenew();
			break;
		case 2:
			users.MaxRenew();
			break;
		case 3:
			books.Add();
			break;
		case 4:
			books.Delete();
			break;
		case 5:
			users.Add();
			break;
		case 6:
			users.Delete();
			break;
		case 7:
			cout<<"�N�n�X���\��"<<endl;
			break;
		default:
			cout<<"�L���\��"<<endl;
			break;
		}
		system("pause");
	}while(n!=7);
}