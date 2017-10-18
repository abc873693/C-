#include <iostream>
#include "LibaryData.h"
#include "Funtion.h"
#define MemberDataName "Members.dat"
#define AdministatorDataName "Administators.dat"
#define BookDataname "Books.dat"
using namespace std;
void main() {
	int mode;
	Member user[100]={NULL};	//宣告Member類別的陣列
	Book books[1000]={NULL};	//宣告Book類別的陣列
	Administator admin[10]={NULL};	//宣告Administator類別的陣列
	Total total;	//宣告Total類別
	total.Member = ReadMemberData(user,MemberDataName);	//讀取使用者檔案的函式
	total.Administator = ReadAdministatorData(admin,AdministatorDataName);	//讀取管理員檔案的函式
	total.Book = ReadBookData(books,BookDataname);	//讀取書籍檔案的函式
	system("pause");
	do{
		mode=MenuInput();	//主選單輸入函式將回傳模式在n
		switch (mode)	//根據輸入的不同選取功能
		{
			int ID;	
		case 1:
			ID=MemberLogin(user,total);	//會員登入函式回傳會員在類別陣列的索引值
			BorrowFuntion(books,user,total,ID); //呼叫借閱函式
			break;
		case 2:
			ID=MemberLogin(user,total);	//會員登入函式回傳會員在類別陣列的索引值
			Searchfution(books,total.Book,user[ID].name);	//呼叫查詢函式
			break;
		case 3:
			Renewfution(books,user,admin,total);	//呼叫更新函式
			break;
		case 4:
			Addfution(books,user,admin,total);	//呼叫新增功能
			break;
		case 5:		//若為5則離開程式
			cout<<"將離開圖書館管理系統"<<endl;
			system("pause");
			break;
		default:
			cout<<"無此功能"<<endl;
			system("pause");
			break;
		}
		WriteMemberData(user,MemberDataName,total.Member);	//寫入的使用者檔案
		WriteBookData(books,BookDataname,total.Book);	//寫入的書籍者檔案
	}while(mode!=5);	//使用無線迴圈判斷是否離開
	system("pause");
}
