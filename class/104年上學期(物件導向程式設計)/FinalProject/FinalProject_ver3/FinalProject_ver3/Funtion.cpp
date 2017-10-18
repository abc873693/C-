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
	cout<<"會員登入"<<endl;
	string account,password;
	cout<<"請輸入帳號:";
	cin>>account;
	cout<<"請輸入密碼:";
	cin>>password;
	int index=accountcheck(users,account);
	if(index==-1)return -1;
	else if(password==users[index].password)return index;
	else return -1;
}
int adminlogin(vector <Administator> &admins){
	cout<<"管理員登入"<<endl;
	string account,password;
	cout<<"請輸入帳號:";
	cin>>account;
	cout<<"請輸入密碼:";
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
		cout<<"以下是所有借閱資料"<<endl;
		cout<<"最大借閱量:"<<user.MAX<<"\t目前借閱總數:"<<user.bookstotal<<endl;
		for(int x=0;x<69;x++)cout<<"-";
		cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(10)<<"借閱數量"<<"|"<<endl;
		for(int i=0;i < user.lendtotal;i++){
			for(int x=0;x<69;x++)cout<<"-";
			cout<<endl<<setw(6)<<user.lendid[i]<<"|"<<setw(50)<<books[IDcheck(books,user.lendid[i])].name<<"|"<<setw(10)<<user.lendamount[i]<<"|"<<endl;
		}
		for(int x=0;x<69;x++)cout<<"-";
		cout<<endl;
		cout<<"歡迎"<<user.name<<"\n借還書功能\n1.書籍借閱\n2.書籍歸還\n3.登出並離開"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			cout<<"書籍借閱"<<endl<<"請輸入借閱書號:";
			cin>>ID;
			int bookindex=IDcheck(books,ID);
			if(bookindex!=-1){
				cout<<"請輸入數量:";
				cin>>amountSTR;
				if(IntergerCheck(amountSTR)){
					int amount=stoi(amountSTR);
					if((amount+user.bookstotal)>user.MAX)cout<<"錯誤!超過最大借閱數量"<<endl;
					if(amount>books[bookindex].remaining)cout<<"錯誤!超過書籍庫存量"<<endl;
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
						cout<<"借閱成功"<<endl;
					}
				}
				else cout<<"請勿輸入違法格式"<<endl;
			}
			else cout<<"查無此書號"<<endl;
			system("pause");
		}
		else if(n=="2"){
			cout<<"書籍歸還"<<endl;
			if(user.lendtotal==0)cout<<"您沒有借閱任何書籍"<<endl;
			else{
				cout<<"請輸入歸還書號:";
				cin>>ID;
				int bookindex=IDcheck(books,ID);
				int boorowindex=user.IDcheck(ID);
				if(bookindex!=-1&&boorowindex!=-1){
					cout<<"請輸入歸還數量:";
					cin>>amountSTR;
					if(IntergerCheck(amountSTR)){
						int amount=stoi(amountSTR);
						if((amount>user.lendamount[boorowindex])||(amount<=0))cout<<"請勿輸入不符合的數量"<<endl;
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
							cout<<"歸還成功"<<endl;
						}
					}
					else cout<<"請勿輸入違法格式"<<endl;
				}
				else if(bookindex==-1)cout<<"查無此書號"<<endl;
				else cout<<"無借閱此書號"<<endl;
			}
			system("pause");
		}
		else if(n=="3")cout<<"即將登出此功能"<<endl;
	}while(n!="3");
}
void SearchFuntion(vector <Book> &books,string NAME){
	string n,ID,input;
	do{
		int max=0,year,month,day;
		system("CLS");
		cout<<"歡迎"<<NAME<<"\n查詢功能\n1.書名查詢\n2.書號查詢\n3.出版社查詢\n4.日期查詢\n5.登出此功能"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			cout<<"請輸入關鍵字:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].name.find(input)!=string::npos){
					if(max==0){
						cout<<"以下是與\""<<input<<"\"相關的書名"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<"查無與\""<<input<<"\"相關的書名"<<endl;
			system("pause");
		}
		else if(n=="2"){
			cout<<"請輸入書號:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].ID==input){
					if(max==0){
						cout<<"以下是書號\""<<input<<"\"的書籍"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
					break;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<"查無與\""<<input<<"\"相同的書號"<<endl;
			system("pause");
		}
		else if(n=="3"){
			cout<<"請輸入關鍵字:";
			cin>>input;
			for(unsigned int i=0;i<books.size();i++){
				if(books[i].publisher.find(input)!=string::npos){
					if(max==0){
						cout<<endl<<"以下是與\""<<input<<"\"相關的書名"<<endl;
						for(int x=0;x<106;x++)cout<<"-";
						cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
					}
					cout<<books[i]<<endl;
					max++;
				}
			}
			if(max>0)for(int x=0;x<106;x++)cout<<"-";
			if(max>0)cout<<endl;
			if(max==0)cout<<endl<<"查無與\""<<input<<"\"相關的出版社的書籍"<<endl;
			system("pause");
		}
		else if(n=="4"){
			cout<<"請輸入日期(YYYY/MM/DD):";
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
							cout<<endl<<"以下是大於日期\""<<DateCovert(searchDate)<<"\"相關的書名"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max==0)cout<<endl<<"查無大於\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"相關的書籍"<<endl;
				for(int x=0;x<106;x++)cout<<"-";
				max=0;
				for(unsigned int i=0;i<books.size();i++){
					if(books[i].publicationDate==searchDate){
						if(max==0){
							cout<<endl<<"以下是等於日期\""<<DateCovert(searchDate)<<"\"相關的書名"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max==0)cout<<endl<<"查無等於\""<<year<<"/"<<DateCovert(searchDate)<<"\"相關的書籍"<<endl;
				for(int x=0;x<106;x++)cout<<"-";
				max=0;
				for(unsigned int i=0;i<books.size();i++){
					if(books[i].publicationDate<searchDate){
						if(max==0){
							cout<<endl<<"以下是小於日期\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"相關的書名"<<endl;
							for(int x=0;x<106;x++)cout<<"-";
							cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
						}
						cout<<books[i]<<endl;
						max++;
					}
				}
				if(max>0)for(int x=0;x<106;x++)cout<<"-";
				if(max>0)cout<<endl;
				if(max==0)cout<<endl<<"查無小於\""<<year<<"/"<<(month>=10?"":"0")<<month<<"/"<<(day>=10?"":"0")<<day<<"\"相關的書籍"<<endl;
			}
			else cout<<"日期格式錯誤"<<endl;
			system("pause");
		}
		else if(n=="5")cout<<"即將登出此功能"<<endl;
		else {
			cout<<"無此功能"<<endl;
			system("pause");
		}
	}while(n!="5");
}
void RenewFuntion(vector <Book> &books,vector <Member> &users,vector <Administator> &admins){
	string n,ID,str;
	do{
		system("CLS");
		cout<<"更新功能\n1.更新書籍資料\n2.更新會員最大借閱量\n3.更新會員資料\n4.返回主畫面"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"登入失敗"<<endl;
			else RenewBooksData(books,admins[index].account);
			system("pause");
		}
		else if(n=="2"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"登入失敗"<<endl;
			else {
				cout<<"歡迎"<<admins[index].account<<endl<<"以下是所有使用者最大借閱量資料"<<endl;
				for(int x=0;x<42;x++)cout<<"-";
				cout<<endl<<setw(6)<<"ID"<<"|"<<setw(10)<<"姓名"<<"|"<<setw(12)<<"最大借閱量"<<"|"<<setw(10)<<"借閱總數"<<"|"<<endl;
				for(unsigned int i=0;i < users.size();i++){
					for(int x=0;x<42;x++)cout<<"-";
					cout<<endl<<setw(6)<<users[i].ID<<"|"<<setw(10)<<users[i].name<<"|"<<setw(12)<<users[i].MAX<<"|"<<setw(10)<<users[i].bookstotal<<"|"<<endl;
				}
				for(int x=0;x<42;x++)cout<<"-";
				cout<<endl<<"請輸入使用者ID:";
				cin>>ID;
				int userindex=IDcheck(users,ID);
				if(userindex!=-1){
					cout<<"請輸入新最大借閱量:";
					cin>>str;
					if(IntergerCheck(str)){
						int newMAX = stoi(str);
						if(newMAX==users[userindex].MAX)cout<<"與原本數量相同"<<endl;
						else if(newMAX<users[userindex].bookstotal)cout<<"錯誤!低於已借閱總數"<<endl;
						else{
							cout<<"更改成功"<<endl;
							users[userindex].MAX=newMAX;
						}
					}
					else cout<<"請勿輸入違法格式"<<endl;
				}
				else cout<<"查無此ID"<<endl;
			}
			system("pause");
		}
		else if(n=="3"){
			int index=userlogin(users);
			if(index==-1)cout<<"登入失敗"<<endl;
			else {
				RenewMembersData(users[index]);
			}
			system("pause");
		}
		else if(n=="4")cout<<"將離開此功能"<<endl;
		else {
			cout<<"無此功能"<<endl;
			system("pause");
		}
	}while(n!="4");
}
void AddDeleteFuntion(vector <Book> &books,vector <Member> &users,string NAME){
	string n;
	do{
		system("CLS");
		cout<<"以下是目前所有書籍資料"<<endl;
		for(int i=0;i<106;i++)cout<<"-";
		cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
		for(unsigned int i=0;i < books.size();i++){
			cout<<books[i]<<endl;
		}
		for(int i=0;i<106;i++)cout<<"-";
		cout<<endl<<"以下是目前所有使用者資料"<<endl;
		for(int i=0;i<119;i++)cout<<"-";
		cout<<endl<<setw(6)<<"身分證"<<"|"<<setw(10)<<"帳號"<<"|"<<setw(10)<<"密碼"<<"|"<<setw(8)<<"姓名"<<"|"<<setw(20)<<"Email"<<"|"<<setw(15)<<"地址"<<"|"<<setw(12)<<"手機號碼"<<"|"<<setw(10)<<"最大借閱量"<<"|"<<setw(9)<<"書籍總數"<<"|"<<setw(9)<<"借閱總數"<<"|"<<endl;
		for(unsigned int i=0;i < users.size();i++){
			cout<<users[i];
		}
		for(int i=0;i<119;i++)cout<<"-";
		cout<<endl<<"歡迎"<<NAME<<"新增功能\n1.新增書籍\n2.刪除書籍\n3.新增會員\n4.刪除會員\n5.登出並返回主選單"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			string ID,name,publisher,remaining;
			int year,month,day;
			cout<<"請輸入書號:";
			cin>>ID;
			if(IDcheck(books,ID)==-1){
				cout<<"請輸入書名:";
				cin>>name;
				cout<<"請輸入出版商:";
				cin>>publisher;
				cout<<"請輸入出版日期(YYYY/MM/DD):";
				cin>>year;
				cin.ignore();
				cin>>month;
				cin.ignore();
				cin>>day;
				cout<<"請輸入書籍數量:";
				cin>>remaining;
				if(IntergerCheck(remaining)){
					Book tmp(ID,name,publisher,year*10000+month*100+day,stoi(remaining),0);
					books.push_back(tmp);
					BookSort(books);
					cout<<"新增成功!"<<endl;
				}
				else cout<<"請勿輸入違法格式"<<endl;
			}
			else cout<<"書號重複!"<<endl;
		}
		else if(n=="2"){
			string ID;
			cout<<"請輸入刪除書號:";
			cin>>ID;
			int deleteindex=IDcheck(books,ID);
			if(deleteindex!=-1){
				if(books[deleteindex].lendout==0){
					for(unsigned int i=deleteindex;i<books.size()-1;i++)
						swap(books[i],books[i+1]);
					books.pop_back();
					cout<<"刪除成功!"<<endl;
				}
				else cout<<"尚有書籍借出無法刪除"<<endl;
			}
			else cout<<"查無書號!"<<endl;
		}
		else if(n=="3"){
			string account,password,ID,name,email,adress,cellNumber,MAX;
			cout<<"請輸入ID:";
			cin>>ID;
			if(IDcheck(users,ID)==-1){
				cout<<"請輸入帳號";
				cin>>account;
				if(accountcheck(users,account)==-1){
					cout<<"請輸入密碼:";
					cin>>password;
					cout<<"請輸入姓名:";
					cin>>name;
					cout<<"請輸入email:";
					cin>>email;
					cout<<"請輸入地址:";
					cin>>adress;
					cout<<"請輸入手機號碼:";
					cin>>cellNumber;
					cout<<"請輸入最大使用者借閱量";
					cin>>MAX;
					if(IntergerCheck(MAX)){
						Member tmp(account,password,ID,name,email,adress,cellNumber,stoi(MAX),0,0);
						users.push_back(tmp);
						cout<<"新增成功!"<<endl;
					}
					else cout<<"請勿輸入違法格式"<<endl;
				}
				else cout<<"帳號重複!"<<endl;
			}
			else cout<<"ID重複!"<<endl;
		}
		else if(n=="4"){
			string ID;
			cout<<"請輸入刪除使用者ID:";
			cin>>ID;
			int deleteindex=IDcheck(users,ID);
			if(deleteindex!=-1){
				if(users[deleteindex].bookstotal==0){
					for(unsigned int i=deleteindex;i<users.size()-1;i++)
						swap(users[i],users[i+1]);
					users.pop_back();
					cout<<"刪除成功!"<<endl;
				}
				else cout<<"尚有書籍借閱無法刪除"<<endl;
			}
			else cout<<"查無使用者!"<<endl;
		}
		else if(n=="5")cout<<"登出並返回主選單"<<endl;
		else cout<<"無此功能"<<endl;
		if(n!="5")system("pause");
	}while(n!="5");
}
void RenewBooksData(vector <Book> &books,string NAME){
	string n,ID,str;
	int bookindex,year,month,day;;
	do{
		system("CLS");
		cout<<"歡迎"<<NAME<<endl<<"以下是所有書籍資料"<<endl;
		for(int x=0;x<106;x++)cout<<"-";
		cout<<endl<<setw(6)<<"書號"<<"|"<<setw(50)<<"書名"<<"|"<<setw(20)<<"出版社"<<"|"<<setw(12)<<"出版日期"<<"|"<<setw(6)<<"庫存"<<"|"<<setw(6)<<"借出"<<"|"<<endl;
		for(unsigned int i=0;i < books.size();i++){
			cout<<books[i]<<endl;
		}
		for(int x=0;x<119;x++)cout<<"-";
		cout<<endl<<"更新書籍資料\n1.書籍名稱\n2.出版社名稱\n3.書籍總數\n4.出版日期\n5.登出返回更新功能"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"||n=="2"||n=="3"||n=="4"){
			cout<<"請輸入書號:";
			cin>>ID;
			bookindex=IDcheck(books,ID);
			if(bookindex!=-1){
				if(n=="1"){
					cout<<"請輸入新書名:";
					cin>>str;
					if(str==books[bookindex].name)cout<<"與原本書名相同"<<endl;
					else {
						cout<<"更改成功!"<<endl;
						books[bookindex].name=str;
					}
				}
				else if(n=="2"){
					cout<<"請輸入新出版社名稱:";
					cin>>str;
					if(str==books[bookindex].publisher)cout<<"與原本出版社名稱相同"<<endl;
					else {
						cout<<"更改成功!"<<endl;
						books[bookindex].publisher=str;
					}
				}
				else if(n=="3"){
					cout<<"請輸入新總數:";
					cin>>str;
					if(IntergerCheck(str)){
						int amount = stoi(str);
						if(amount==books[bookindex].remaining+books[bookindex].lendout)cout<<"與原本總數相同"<<endl;
						else if(amount<books[bookindex].lendout)cout<<"錯誤!小於借出量"<<endl;
						else {
							cout<<"更改成功!"<<endl;
							books[bookindex].remaining=amount-books[bookindex].lendout;
						}
					}
					else cout<<"請勿輸入違法格式"<<endl;
				}
				else if(n=="4"){
					cout<<"請輸入日期(YYYY/MM/DD):";
					cin>>year;
					cin.ignore();
					cin>>month;
					cin.ignore();
					cin>>day;
					if(DateChecker(year,month,day)){
						int newDate=year*10000+month*100+day;
						if(newDate==books[bookindex].publicationDate)cout<<"與原本日期相同"<<endl;
						else {
							cout<<"更改成功!"<<endl;
							books[bookindex].publicationDate=newDate;
						}
					}
					else cout<<"日期格式錯誤"<<endl;
				}
			}
			else cout<<"查無此ID"<<endl;
			system("pause");
		}
		else if(n=="5")cout<<"將離開此功能"<<endl;
		else {
			cout<<"無此功能"<<endl;
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
		cout<<"歡迎"<<user.name<<"\n更改會員資料\n1.密碼\n2.名字\n3.Email\n4.地址\n5.手機號碼\n6.登出並返回更新功能"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			cout<<"請輸入新密碼:";
			cin>>str;
			cout<<"驗證碼"<<authcode<<endl<<"請輸入驗證碼:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.password)cout<<"與原本密碼相同"<<endl;
				else {
					user.password=str;
					cout<<"更改成功!"<<endl;
				}
			}
			else cout<<"驗證碼輸入錯誤"<<endl;
		}
		else if(n=="2"){
			cout<<"請輸入新名字:";
			cin>>str;
			cout<<"驗證碼"<<authcode<<endl<<"請輸入驗證碼:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.name)cout<<"與原本名字相同"<<endl;
				else {
					user.name=str;
					cout<<"更改成功!"<<endl;
				}
			}
			else cout<<"驗證碼輸入錯誤"<<endl;
		}
		else if(n=="3"){
			cout<<"請輸入新Email:";
			cin>>str;
			cout<<"驗證碼"<<authcode<<endl<<"請輸入驗證碼:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.email)cout<<"與原本Email相同"<<endl;
				else {
					user.email=str;
					cout<<"更改成功!"<<endl;
				}
			}
			else cout<<"驗證碼輸入錯誤"<<endl;
		}
		else if(n=="4"){
			cout<<"請輸入新地址:";
			cin>>str;
			cout<<"驗證碼"<<authcode<<endl<<"請輸入驗證碼:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.adress)cout<<"與原本地址相同"<<endl;
				else {
					user.adress=str;
					cout<<"更改成功!"<<endl;
				}
			}
			else cout<<"驗證碼輸入錯誤"<<endl;
		}
		else if(n=="5"){
			cout<<"請輸入新手機號碼:";
			cin>>str;
			cout<<"驗證碼"<<authcode<<endl<<"請輸入驗證碼:";
			cin>>authinput;
			if(authinput==authcode){
				if(str==user.cellNumber)cout<<"與原本手機號碼相同"<<endl;
				else {
					user.cellNumber=str;
					cout<<"更改成功!"<<endl;
				}
			}
			else cout<<"驗證碼輸入錯誤"<<endl;
		}
		else if(n=="6")cout<<"將登出並離開此功能"<<endl;
		else cout<<"無此功能"<<endl;
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