#include <iostream>
#include <fstream> 
#include <string>
#include <iomanip>
#include <vector>
#include "Library.h"
#include "Funtion.h"
#define MESSAGE "����ɦV�����@�~ �|�l�G�� 1103105345 �Чӭ�"
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
		cout<<"�Ϯ��]�޲z�t��(Library management system)\n1.�ɮ�(�ϥΪ�)\n2.�d��(�ϥΪ�)\n3.��s(�ϥΪ̩κ޲z��)\n4.�s�W(�޲z��)\n5.���}"<<endl;
		cout<<"�п�J:";
		cin>>n;
		if(n=="1"){
			int index=userlogin(users);
			if(index==-1)cout<<"�n�J����"<<endl;
			else BorrowFuntion(books,users[index]);
		}
		else if(n=="2"){
			int index=userlogin(users);
			if(index==-1)cout<<"�n�J����"<<endl;
			else SearchFuntion(books,users[index].name);
		}
		else if(n=="3"){
			RenewFuntion(books,users,admins);
		}
		else if(n=="4"){
			int index=adminlogin(admins);
			if(index==-1)cout<<"�n�J����"<<endl;
			else AddDeleteFuntion(books,users,admins[index].account);
		}
		else if(n=="5")cout<<"�N���}�t��"<<endl;
		else cout<<"�L���\��"<<endl;
		WriteMemberData(users,"Members.dat");
		WriteBookData(books,"Books.dat");
		system("pause");
	}while(n!="5");
}