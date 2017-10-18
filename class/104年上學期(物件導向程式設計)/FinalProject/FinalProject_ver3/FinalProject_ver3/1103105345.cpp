#include <iostream>
#include <fstream> 
#include <string>
#include <iomanip>
#include <vector>
#include "Library.h"
#include "Funtion.h"
#define MESSAGE "物件導向期末作業 四子二丙 1103105345 房志剛"
using namespace std;
void main(){
	vector <Book> books;
	vector <Member> users;
	vector <Administator> admins;
	string n;
	ReadBookData(books,"Books.dat");
	ReadMemberData(users,"Members.dat");
	ReadAdministatorData(admins,"Administators.dat");
	BookSort(books);
	do{
		system("CLS");
		cout<<MESSAGE<<endl;
		cout<<"圖書館管理系統(Library management system)\n1.借書(使用者)\n2.查詢(使用者)\n3.更新(使用者或管理員)\n4.新增(管理員)\n5.離開"<<endl;
		cout<<"請輸入:";
		cin>>n;
		if(n=="1"){
			int index=userlogin(users);
			if(index==-1)cout<<"登入失敗"<<endl;
			else BorrowFuntion(books,users[index]);
		}
		else if(n=="2"){
			int index=userlogin(users);
			if(index==-1)cout<<"登入失敗"<<endl;
			else SearchFuntion(books,users[index].name);
		}
		else if(n=="3"){
			RenewFuntion(books,users,admins);
		}
		else if(n=="4"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"登入失敗"<<endl;
			else AddDeleteFuntion(books,users,admins[index].account);
		}
		else if(n=="5")cout<<"將離開系統"<<endl;
		else cout<<"無此功能"<<endl;
		WriteMemberData(users,"Members.dat");
		WriteBookData(books,"Books.dat");
		system("pause");
	}while(n!="5");
}