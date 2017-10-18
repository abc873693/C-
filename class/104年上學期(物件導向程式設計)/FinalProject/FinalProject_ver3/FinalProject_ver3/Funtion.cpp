#include <fstream> 
#include <iostream> 
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include "Library.h"
#include "Funtion.h"
using namespace std;
bool IntergerCheck(string input){
	for(unsigned int i=0;i<input.size();i++){
		if(input[i]<'0'||input[i]>'9')return false;
	}
	return true;
}
bool DateChecker(int y,int m,int d){
	int day[14]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(y%4==0&&y%100!=0||y%400==0)day[2]=29;
	if(m<=0||m>12)return false;
	if(day[m]<=0||d>day[m])return false;
	return true;
}
void CreateAuthCode(string &authcode){
	authcode="";
	char code[38]={"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	for(int i=0;i<5;i++)authcode+=code[rand()%36];
}
void BookSort(vector <Book> &books){
	for(unsigned int i=0;i<books.size()-1;i++){
		for(unsigned int j=i+1;j<books.size();j++){
			if(books[i].ID>books[j].ID){
				swap(books[i],books[j]);
			}
		}
	}
}
string DateCovert(int date){
	return to_string(date/10000)+"/"+((date%10000/100)>=10?"":"0")+to_string(date%10000/100)+"/"+((date%100)>=10?"":"0")+to_string(date%100);
}
void ReadBookData(vector <Book> &books,string FILENAME){
	ifstream fin(FILENAME);
	while(!fin.eof()){
		string ID,name,publisher;
		int publicationDate,remaining,lendout;
		fin>>ID>>lendout>>remaining>>name>>publisher>>publicationDate;
		Book tmp(ID,name,publisher,publicationDate,remaining,lendout);
		books.push_back(tmp);
	}
	fin.close();
}
void WriteBookData(vector <Book> &books,string FILENAME){
	ofstream fout(FILENAME);
	for(unsigned int i=0;i<books.size();i++){
		fout<<books[i].ID<<" "<<books[i].lendout<<" "<<books[i].remaining<<" "<<books[i].name<<" "<<books[i].publisher<<" "<<books[i].publicationDate;
		if(i<books.size()-1)fout<<endl;
	}
	fout.close();
}
void ReadMemberData(vector <Member> &users,string FILENAME){
	ifstream fin(FILENAME);
	while(!fin.eof()){
		string account,password,ID,name,email,adress,cellNumber;
		int MAX,bookstotal,lendtotal,amount,index=users.size();
		fin>>ID>>account>>password>>name>>email>>adress>>cellNumber>>MAX>>bookstotal>>lendtotal;
		Member tmp(account,password,ID,name,email,adress,cellNumber,MAX,bookstotal,lendtotal);
		users.push_back(tmp);
		for(int i=0;i<lendtotal;i++){
			fin>>ID>>amount;
			users[index].lendid.push_back(ID);
			users[index].lendamount.push_back(amount);
		}
	}
	fin.close();
}
void WriteMemberData(vector <Member> &users,string FILENAME){
	ofstream fout(FILENAME);
	for(unsigned int i=0;i<users.size();i++){
		fout<<users[i].ID<<" "<<users[i].account<<" "<<users[i].password<<" "<<users[i].name<<" "<<users[i].email<<" "<<users[i].adress<<" "<<users[i].cellNumber<<" "<<users[i].MAX<<" "<<users[i].bookstotal<<" "<<users[i].lendtotal;
		for(int j=0;j<users[i].lendtotal;j++){
			fout<<endl<<users[i].lendid[j]<<" "<<users[i].lendamount[j];
			if(i<users.size()-1&&j==users[i].lendtotal-1)fout<<endl;
		}
	}
	fout.close();
}
void ReadAdministatorData(vector <Administator> &admins,string FILENAME){
	ifstream fin(FILENAME);
	while(!fin.eof()){
		string account,password;
		fin>>account>>password;
		Administator tmp(account,password);
		admins.push_back(tmp);
	}
	fin.close();
}
int userlogin(vector <Member> &users){
	cout<<"�|���n�J"<<endl;
	string account,password;
	cout<<"�п�J�b��:";
	cin>>account;
	cout<<"�п�J�K�X:";
	cin>>password;
	int index=accountcheck(users,account);
	if(index==-1)return -1;
	else if(password==users[index].password)return index;
	else return -1;
}
int adminlogin(vector <Administator> &admins){
	cout<<"�޲z���n�J"<<endl;
	string account,password;
	cout<<"�п�J�b��:";
	cin>>account;
	cout<<"�п�J�K�X:";
	cin>>password;
	int index=accountcheck(admins,account);
	if(index==-1)return -1;
	else if(password==admins[index].password)return index;
	else return -1;
}
int accountcheck(vector <Member> &users,string input){
	for(unsigned int i=0;i<users.size();i++){
		if(users[i].account==input)return i;
	}
	return -1;
}
int accountcheck(vector <Administator> &users,string input){
	for(unsigned int i=0;i<users.size();i++){
		if(users[i].account==input)return i;
	}
	return -1;
}
int IDcheck(vector <Member> &users,string searchID){
	for(unsigned int i=0;i<users.size();i++){
		if(users[i].ID==searchID)return i;
	}
	return -1;
}
int IDcheck(vector <Book> &books,string searchID){
	for(unsigned int i=0;i<books.size();i++){
		if(books[i].ID==searchID)return i;
	}
	return -1;
}
void BorrowFuntion(vector <Book> &books,Member &user){
	string n,ID,amountSTR;
	do{
		system("CLS");
		cout<<"�H�U�O�Ҧ��ɾ\���"<<endl;
		cout<<"�̤j�ɾ\�q:"<<user.MAX<<"\t�ثe�ɾ\�`��:"<<user.bookstotal<<endl;
		for(int x=0;x<69;x++)cout<<"-";
		cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(10)<<"�ɾ\�ƶq"<<"|"<<endl;
		for(int i=0;i < user.lendtotal;i++){
			for(int x=0;x<69;x++)cout<<"-";
			cout<<endl<<setw(6)<<user.lendid[i]<<"|"<<setw(50)<<books[IDcheck(books,user.lendid[i])].name<<"|"<<setw(10)<<user.lendamount[i]<<"|"<<endl;
		}
		for(int x=0;x<69;x++)cout<<"-";
		cout<<endl;
		cout<<"�w��"<<user.name<<"\n���ٮѥ\��\n1.���y�ɾ\\n2.���y�k��\n3.�n�X�����}"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			cout<<"���y�ɾ\"<<endl<<"�п�J�ɾ\�Ѹ�:";
			cin>>ID;
			int bookindex=IDcheck(books,ID);
			if(bookindex!=-1){
				cout<<"�п�J�ƶq:";
				cin>>amountSTR;
				if(IntergerCheck(amountSTR)){
					int amount=stoi(amountSTR);
					if((amount+user.bookstotal)>user.MAX)cout<<"���~!�W�L�̤j�ɾ\�ƶq"<<endl;
					if(amount>books[bookindex].remaining)cout<<"���~!�W�L���y�w�s�q"<<endl;
					if(!((amount+user.bookstotal)>user.MAX)&&!(amount>books[bookindex].remaining)){
						int boorowindex=user.IDcheck(ID);
						if(boorowindex==-1){
							user.lendid.push_back(ID);
							user.lendamount.push_back(amount);
							user.lendtotal++;
						}
						else user.lendamount[boorowindex]+=amount;
						books[bookindex].remaining-=amount;
						books[bookindex].lendout+=amount;
						user.bookstotal+=amount;
						cout<<"�ɾ\���\"<<endl;
					}
				}
				else cout<<"�Фſ�J�H�k�榡"<<endl;
			}
			else cout<<"�d�L���Ѹ�"<<endl;
			system("pause");
		}
		else if(n=="2"){
			cout<<"���y�k��"<<endl;
			if(user.lendtotal==0)cout<<"�z�S���ɾ\������y"<<endl;
			else{
				cout<<"�п�J�k�ٮѸ�:";
				cin>>ID;
				int bookindex=IDcheck(books,ID);
				int boorowindex=user.IDcheck(ID);
				if(bookindex!=-1&&boorowindex!=-1){
					cout<<"�п�J�k�ټƶq:";
					cin>>amountSTR;
					if(IntergerCheck(amountSTR)){
						int amount=stoi(amountSTR);
						if((amount>user.lendamount[boorowindex])||(amount<=0))cout<<"�Фſ�J���ŦX���ƶq"<<endl;
						else {
							user.lendamount[boorowindex]-=amount;
							if(user.lendamount[boorowindex]==0){
								for(int i=boorowindex;i<user.lendtotal-1;i++){
									swap(user.lendamount[i],user.lendamount[i+1]);
									swap(user.lendid[i],user.lendid[i+1]);
								}
								user.lendamount.pop_back();
								user.lendid.pop_back();
								user.lendtotal--;
							}
							books[bookindex].remaining+=amount;
							books[bookindex].lendout-=amount;
							user.bookstotal-=amount;
							cout<<"�k�٦��\"<<endl;
						}
					}
					else cout<<"�Фſ�J�H�k�榡"<<endl;
				}
				else if(bookindex==-1)cout<<"�d�L���Ѹ�"<<endl;
				else cout<<"�L�ɾ\���Ѹ�"<<endl;
			}
			system("pause");
		}
		else if(n=="3")cout<<"�Y�N�n�X���\��"<<endl;
	}while(n!="3");
}
void SearchFuntion(vector <Book> &books,string NAME){
	string n,ID,input;
	do{
		int max=0,year,month,day;
		system("CLS");
		cout<<"�w��"<<NAME<<"\n�d�ߥ\��\n1.�ѦW�d��\n2.�Ѹ��d��\n3.�X�����d��\n4.����d��\n5.�n�X���\��"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			cout<<"�п�J����r:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].name.find(input)!=string::npos){
					if(max==0){
						cout<<"�H�U�O�P\""<<input<<"\"�������ѦW"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<"�d�L�P\""<<input<<"\"�������ѦW"<<endl;
			system("pause");
		}
		else if(n=="2"){
			cout<<"�п�J�Ѹ�:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].ID==input){
					if(max==0){
						cout<<"�H�U�O�Ѹ�\""<<input<<"\"�����y"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
					break;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<"�d�L�P\""<<input<<"\"�ۦP���Ѹ�"<<endl;
			system("pause");
		}
		else if(n=="3"){
			cout<<"�п�J����r:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].publisher.find(input)!=string::npos){
					if(max==0){
						cout<<endl<<"�H�U�O�P\""<<input<<"\"�������ѦW"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<endl<<"�d�L�P\""<<input<<"\"�������X���������y"<<endl;
			system("pause");
		}
		else if(n=="4"){
			cout<<"�п�J���(YYYY/MM/DD):";
			cin>>year;
			cin.ignore();
			cin>>month;
			cin.ignore();
			cin>>day;
			for(int x=0;x<106;x++)cout<<"-";
			int searchDate=year*10000+month*100+day;
			if(DateChecker(year,month,day)){
				for(unsigned int i=0;i<books.size();i++){
					if(books[i].publicationDate>searchDate){
						if(max==0){
							cout<<endl<<"�H�U�O�j����\""<<DateCovert(searchDate)<<"\"�������ѦW"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max==0)cout<<endl<<"�d�L�j��\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"���������y"<<endl;
				for(int x=0;x<106;x++)cout<<"-";
				max=0;
				for(unsigned int i=0;i<books.size();i++){
					if(books[i].publicationDate==searchDate){
						if(max==0){
							cout<<endl<<"�H�U�O������\""<<DateCovert(searchDate)<<"\"�������ѦW"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max==0)cout<<endl<<"�d�L����\""<<year<<"/"<<DateCovert(searchDate)<<"\"���������y"<<endl;
				for(int x=0;x<106;x++)cout<<"-";
				max=0;
				for(unsigned int i=0;i<books.size();i++){
					if(books[i].publicationDate<searchDate){
						if(max==0){
							cout<<endl<<"�H�U�O�p����\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"�������ѦW"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max>0)for(int x=0;x<106;x++)cout<<"-";
				if(max>0)cout<<endl;
				if(max==0)cout<<endl<<"�d�L�p��\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"���������y"<<endl;
			}
			else cout<<"����榡���~"<<endl;
			system("pause");
		}
		else if(n=="5")cout<<"�Y�N�n�X���\��"<<endl;
		else {
			cout<<"�L���\��"<<endl;
			system("pause");
		}
	}while(n!="5");
}
void RenewFuntion(vector <Book> &books,vector <Member> &users,vector <Administator> &admins){
	string n,ID,str;
	do{
		system("CLS");
		cout<<"��s�\��\n1.��s���y���\n2.��s�|���̤j�ɾ\�q\n3.��s�|�����\n4.��^�D�e��"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"�n�J����"<<endl;
			else RenewBooksData(books,admins[index].account);
			system("pause");
		}
		else if(n=="2"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"�n�J����"<<endl;
			else {
				cout<<"�w��"<<admins[index].account<<endl<<"�H�U�O�Ҧ��ϥΪ̳̤j�ɾ\�q���"<<endl;
				for(int x=0;x<42;x++)cout<<"-";
				cout<<endl<<setw(6)<<"ID"<<"|"<<setw(10)<<"�m�W"<<"|"<<setw(12)<<"�̤j�ɾ\�q"<<"|"<<setw(10)<<"�ɾ\�`��"<<"|"<<endl;
				for(unsigned int i=0;i < users.size();i++){
					for(int x=0;x<42;x++)cout<<"-";
					cout<<endl<<setw(6)<<users[i].ID<<"|"<<setw(10)<<users[i].name<<"|"<<setw(12)<<users[i].MAX<<"|"<<setw(10)<<users[i].bookstotal<<"|"<<endl;
				}
				for(int x=0;x<42;x++)cout<<"-";
				cout<<endl<<"�п�J�ϥΪ�ID:";
				cin>>ID;
				int userindex=IDcheck(users,ID);
				if(userindex!=-1){
					cout<<"�п�J�s�̤j�ɾ\�q:";
					cin>>str;
					if(IntergerCheck(str)){
						int newMAX = stoi(str);
						if(newMAX==users[userindex].MAX)cout<<"�P�쥻�ƶq�ۦP"<<endl;
						else if(newMAX<users[userindex].bookstotal)cout<<"���~!�C��w�ɾ\�`��"<<endl;
						else{
							cout<<"��令�\"<<endl;
							users[userindex].MAX=newMAX;
						}
					}
					else cout<<"�Фſ�J�H�k�榡"<<endl;
				}
				else cout<<"�d�L��ID"<<endl;
			}
			system("pause");
		}
		else if(n=="3"){
			int index=userlogin(users);
			if(index==-1)cout<<"�n�J����"<<endl;
			else {
				RenewMembersData(users[index]);
			}
			system("pause");
		}
		else if(n=="4")cout<<"�N���}���\��"<<endl;
		else {
			cout<<"�L���\��"<<endl;
			system("pause");
		}
	}while(n!="4");
}
void AddDeleteFuntion(vector <Book> &books,vector <Member> &users,string NAME){
	string n;
	do{
		system("CLS");
		cout<<"�H�U�O�ثe�Ҧ����y���"<<endl;
		for(int i=0;i<106;i++)cout<<"-";
		cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
		for(unsigned int i=0;i < books.size();i++){
			cout<<books[i]<<endl;
		}
		for(int i=0;i<106;i++)cout<<"-";
		cout<<endl<<"�H�U�O�ثe�Ҧ��ϥΪ̸��"<<endl;
		for(int i=0;i<119;i++)cout<<"-";
		cout<<endl<<setw(6)<<"������"<<"|"<<setw(10)<<"�b��"<<"|"<<setw(10)<<"�K�X"<<"|"<<setw(8)<<"�m�W"<<"|"<<setw(20)<<"Email"<<"|"<<setw(15)<<"�a�}"<<"|"<<setw(12)<<"������X"<<"|"<<setw(10)<<"�̤j�ɾ\�q"<<"|"<<setw(9)<<"���y�`��"<<"|"<<setw(9)<<"�ɾ\�`��"<<"|"<<endl;
		for(unsigned int i=0;i < users.size();i++){
			cout<<users[i];
		}
		for(int i=0;i<119;i++)cout<<"-";
		cout<<endl<<"�w��"<<NAME<<"�s�W�\��\n1.�s�W���y\n2.�R�����y\n3.�s�W�|��\n4.�R���|��\n5.�n�X�ê�^�D���"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			string ID,name,publisher,remaining;
			int year,month,day;
			cout<<"�п�J�Ѹ�:";
			cin>>ID;
			if(IDcheck(books,ID)==-1){
				cout<<"�п�J�ѦW:";
				cin>>name;
				cout<<"�п�J�X����:";
				cin>>publisher;
				cout<<"�п�J�X�����(YYYY/MM/DD):";
				cin>>year;
				cin.ignore();
				cin>>month;
				cin.ignore();
				cin>>day;
				cout<<"�п�J���y�ƶq:";
				cin>>remaining;
				if(IntergerCheck(remaining)){
					Book tmp(ID,name,publisher,year*10000+month*100+day,stoi(remaining),0);
					books.push_back(tmp);
					BookSort(books);
					cout<<"�s�W���\!"<<endl;
				}
				else cout<<"�Фſ�J�H�k�榡"<<endl;
			}
			else cout<<"�Ѹ�����!"<<endl;
		}
		else if(n=="2"){
			string ID;
			cout<<"�п�J�R���Ѹ�:";
			cin>>ID;
			int deleteindex=IDcheck(books,ID);
			if(deleteindex!=-1){
				if(books[deleteindex].lendout==0){
					for(unsigned int i=deleteindex;i<books.size()-1;i++)
						swap(books[i],books[i+1]);
					books.pop_back();
					cout<<"�R�����\!"<<endl;
				}
				else cout<<"�|�����y�ɥX�L�k�R��"<<endl;
			}
			else cout<<"�d�L�Ѹ�!"<<endl;
		}
		else if(n=="3"){
			string account,password,ID,name,email,adress,cellNumber,MAX;
			cout<<"�п�JID:";
			cin>>ID;
			if(IDcheck(users,ID)==-1){
				cout<<"�п�J�b��";
				cin>>account;
				if(accountcheck(users,account)==-1){
					cout<<"�п�J�K�X:";
					cin>>password;
					cout<<"�п�J�m�W:";
					cin>>name;
					cout<<"�п�Jemail:";
					cin>>email;
					cout<<"�п�J�a�}:";
					cin>>adress;
					cout<<"�п�J������X:";
					cin>>cellNumber;
					cout<<"�п�J�̤j�ϥΪ̭ɾ\�q";
					cin>>MAX;
					if(IntergerCheck(MAX)){
						Member tmp(account,password,ID,name,email,adress,cellNumber,stoi(MAX),0,0);
						users.push_back(tmp);
						cout<<"�s�W���\!"<<endl;
					}
					else cout<<"�Фſ�J�H�k�榡"<<endl;
				}
				else cout<<"�b������!"<<endl;
			}
			else cout<<"ID����!"<<endl;
		}
		else if(n=="4"){
			string ID;
			cout<<"�п�J�R���ϥΪ�ID:";
			cin>>ID;
			int deleteindex=IDcheck(users,ID);
			if(deleteindex!=-1){
				if(users[deleteindex].bookstotal==0){
					for(unsigned int i=deleteindex;i<users.size()-1;i++)
						swap(users[i],users[i+1]);
					users.pop_back();
					cout<<"�R�����\!"<<endl;
				}
				else cout<<"�|�����y�ɾ\�L�k�R��"<<endl;
			}
			else cout<<"�d�L�ϥΪ�!"<<endl;
		}
		else if(n=="5")cout<<"�n�X�ê�^�D���"<<endl;
		else cout<<"�L���\��"<<endl;
		if(n!="5")system("pause");
	}while(n!="5");
}
void RenewBooksData(vector <Book> &books,string NAME){
	string n,ID,str;
	int bookindex,year,month,day;;
	do{
		system("CLS");
		cout<<"�w��"<<NAME<<endl<<"�H�U�O�Ҧ����y���"<<endl;
		for(int x=0;x<106;x++)cout<<"-";
		cout<<endl<<setw(6)<<"�Ѹ�"<<"|"<<setw(50)<<"�ѦW"<<"|"<<setw(20)<<"�X����"<<"|"<<setw(12)<<"�X�����"<<"|"<<setw(6)<<"�w�s"<<"|"<<setw(6)<<"�ɥX"<<"|"<<endl;
		for(unsigned int i=0;i < books.size();i++){
			cout<<books[i]<<endl;
		}
		for(int x=0;x<119;x++)cout<<"-";
		cout<<endl<<"��s���y���\n1.���y�W��\n2.�X�����W��\n3.���y�`��\n4.�X�����\n5.�n�X��^��s�\��"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"||n=="2"||n=="3"||n=="4"){
			cout<<"�п�J�Ѹ�:";
			cin>>ID;
			bookindex=IDcheck(books,ID);
			if(bookindex!=-1){
				if(n=="1"){
					cout<<"�п�J�s�ѦW:";
					cin>>str;
					if(str==books[bookindex].name)cout<<"�P�쥻�ѦW�ۦP"<<endl;
					else {
						cout<<"��令�\!"<<endl;
						books[bookindex].name=str;
					}
				}
				else if(n=="2"){
					cout<<"�п�J�s�X�����W��:";
					cin>>str;
					if(str==books[bookindex].publisher)cout<<"�P�쥻�X�����W�٬ۦP"<<endl;
					else {
						cout<<"��令�\!"<<endl;
						books[bookindex].publisher=str;
					}
				}
				else if(n=="3"){
					cout<<"�п�J�s�`��:";
					cin>>str;
					if(IntergerCheck(str)){
						int amount = stoi(str);
						if(amount==books[bookindex].remaining+books[bookindex].lendout)cout<<"�P�쥻�`�ƬۦP"<<endl;
						else if(amount<books[bookindex].lendout)cout<<"���~!�p��ɥX�q"<<endl;
						else {
							cout<<"��令�\!"<<endl;
							books[bookindex].remaining=amount-books[bookindex].lendout;
						}
					}
					else cout<<"�Фſ�J�H�k�榡"<<endl;
				}
				else if(n=="4"){
					cout<<"�п�J���(YYYY/MM/DD):";
					cin>>year;
					cin.ignore();
					cin>>month;
					cin.ignore();
					cin>>day;
					if(DateChecker(year,month,day)){
						int newDate=year*10000+month*100+day;
						if(newDate==books[bookindex].publicationDate)cout<<"�P�쥻����ۦP"<<endl;
						else {
							cout<<"��令�\!"<<endl;
							books[bookindex].publicationDate=newDate;
						}
					}
					else cout<<"����榡���~"<<endl;
				}
			}
			else cout<<"�d�L��ID"<<endl;
			system("pause");
		}
		else if(n=="5")cout<<"�N���}���\��"<<endl;
		else {
			cout<<"�L���\��"<<endl;
			system("pause");
		}
	}while(n!="5");
}
void RenewMembersData(Member &user){
	string authcode,n,str,authinput;
	srand((unsigned int)time(NULL));
	do{
		system("CLS");
		CreateAuthCode(authcode);
		cout<<"�w��"<<user.name<<"\n���|�����\n1.�K�X\n2.�W�r\n3.Email\n4.�a�}\n5.������X\n6.�n�X�ê�^��s�\��"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			cout<<"�п�J�s�K�X:";
			cin>>str;
			cout<<"���ҽX"<<authcode<<endl<<"�п�J���ҽX:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.password)cout<<"�P�쥻�K�X�ۦP"<<endl;
				else {
					user.password=str;
					cout<<"��令�\!"<<endl;
				}
			}
			else cout<<"���ҽX��J���~"<<endl;
		}
		else if(n=="2"){
			cout<<"�п�J�s�W�r:";
			cin>>str;
			cout<<"���ҽX"<<authcode<<endl<<"�п�J���ҽX:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.name)cout<<"�P�쥻�W�r�ۦP"<<endl;
				else {
					user.name=str;
					cout<<"��令�\!"<<endl;
				}
			}
			else cout<<"���ҽX��J���~"<<endl;
		}
		else if(n=="3"){
			cout<<"�п�J�sEmail:";
			cin>>str;
			cout<<"���ҽX"<<authcode<<endl<<"�п�J���ҽX:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.email)cout<<"�P�쥻Email�ۦP"<<endl;
				else {
					user.email=str;
					cout<<"��令�\!"<<endl;
				}
			}
			else cout<<"���ҽX��J���~"<<endl;
		}
		else if(n=="4"){
			cout<<"�п�J�s�a�}:";
			cin>>str;
			cout<<"���ҽX"<<authcode<<endl<<"�п�J���ҽX:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.adress)cout<<"�P�쥻�a�}�ۦP"<<endl;
				else {
					user.adress=str;
					cout<<"��令�\!"<<endl;
				}
			}
			else cout<<"���ҽX��J���~"<<endl;
		}
		else if(n=="5"){
			cout<<"�п�J�s������X:";
			cin>>str;
			cout<<"���ҽX"<<authcode<<endl<<"�п�J���ҽX:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.cellNumber)cout<<"�P�쥻������X�ۦP"<<endl;
				else {
					user.cellNumber=str;
					cout<<"��令�\!"<<endl;
				}
			}
			else cout<<"���ҽX��J���~"<<endl;
		}
		else if(n=="6")cout<<"�N�n�X�����}���\��"<<endl;
		else cout<<"�L���\��"<<endl;
		if(n!="6")system("pause");
	}while(n!="6");
}
ostream &operator<<(ostream &out,Book book){
	for(int i=0;i<106;i++)cout<<"-";
	out<<endl<<setw(6)<<book.ID<<"|"<<setw(50)<<book.name<<"|"<<setw(20)<<book.publisher<<"|"<<setw(12)<<DateCovert(book.publicationDate)<<"|"<<setw(6)<<book.remaining<<"|"<<setw(6)<<book.lendout<<"|";
	return out;
}
ostream &operator<<(ostream &out,Member user){
	for(int i=0;i<119;i++)cout<<"-";
	out<<endl<<setw(6)<<user.ID<<"|"<<setw(10)<<user.account<<"|"<<setw(10)<<user.password<<"|"<<setw(8)<<user.name<<"|"<<setw(20)<<user.email<<"|"<<setw(15)<<user.adress<<"|"<<setw(12)<<user.cellNumber<<"|"<<setw(10)<<user.MAX<<"|"<<setw(9)<<user.bookstotal<<"|"<<setw(9)<<user.lendtotal<<"|"<<endl;
	return out;
}