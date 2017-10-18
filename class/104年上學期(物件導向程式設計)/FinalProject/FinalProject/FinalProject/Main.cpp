#include <iostream>
#include "LibaryData.h"
#include "Funtion.h"
#define MemberDataName "Members.dat"
#define AdministatorDataName "Administators.dat"
#define BookDataname "Books.dat"
using namespace std;
void main() {
	int mode;
	Member user[100]={NULL};	//�ŧiMember���O���}�C
	Book books[1000]={NULL};	//�ŧiBook���O���}�C
	Administator admin[10]={NULL};	//�ŧiAdministator���O���}�C
	Total total;	//�ŧiTotal���O
	total.Member = ReadMemberData(user,MemberDataName);	//Ū���ϥΪ��ɮת��禡
	total.Administator = ReadAdministatorData(admin,AdministatorDataName);	//Ū���޲z���ɮת��禡
	total.Book = ReadBookData(books,BookDataname);	//Ū�����y�ɮת��禡
	system("pause");
	do{
		mode=MenuInput();	//�D����J�禡�N�^�ǼҦ��bn
		switch (mode)	//�ھڿ�J�����P����\��
		{
			int ID;	
		case 1:
			ID=MemberLogin(user,total);	//�|���n�J�禡�^�Ƿ|���b���O�}�C�����ޭ�
			BorrowFuntion(books,user,total,ID); //�I�s�ɾ\�禡
			break;
		case 2:
			ID=MemberLogin(user,total);	//�|���n�J�禡�^�Ƿ|���b���O�}�C�����ޭ�
			Searchfution(books,total.Book,user[ID].name);	//�I�s�d�ߨ禡
			break;
		case 3:
			Renewfution(books,user,admin,total);	//�I�s��s�禡
			break;
		case 4:
			Addfution(books,user,admin,total);	//�I�s�s�W�\��
			break;
		case 5:		//�Y��5�h���}�{��
			cout<<"�N���}�Ϯ��]�޲z�t��"<<endl;
			system("pause");
			break;
		default:
			cout<<"�L���\��"<<endl;
			system("pause");
			break;
		}
		WriteMemberData(user,MemberDataName,total.Member);	//�g�J���ϥΪ��ɮ�
		WriteBookData(books,BookDataname,total.Book);	//�g�J�����y���ɮ�
	}while(mode!=5);	//�ϥεL�u�j��P�_�O�_���}
	system("pause");
}
