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
		cout<<"請選擇\n1.使用者\n2.管理員\n3.離開此系統\n請輸入"<<endl;
		cin>>n;
		switch (n)
		{
		case 1:
			index=users.login();
			//index=0;
			if(index!=-1)MemberFuntion(users,books,index);
			else {
				cout<<"登入失敗"<<endl;
				system("pause");
			}
			break;
		case 2:
			index=admins.login();
			if(index!=-1)AdministatorFuntion(users,books,admins,index);
			else {
				cout<<"登入失敗"<<endl;
				system("pause");
			}
			break;
		case 3:
			cout<<"將離開系統"<<endl;
			system("pause");
			break;
		default:
			cout<<"無此功能"<<endl;
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
	cout<<"請輸入帳號:";
	cin>>str1;
	cout<<"請輸入密碼:";
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
	cout<<setw(5)<<"書號"<<setw(5)<<"庫存"<<setw(5)<<"借出"<<setw(50)<<"書名"<<setw(20)<<"出版社"<<setw(15)<<"出版日期"<<endl;
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
		cout<<setw(5)<<"書號"<<setw(5)<<"庫存"<<setw(5)<<"借出"<<setw(50)<<"書名"<<setw(20)<<"出版社"<<setw(12)<<"出版日期"<<endl;
		for(int i=0;i<total;i++){
			int tmp=arr[i];
			cout<<setw(5)<<id[tmp]<<setw(5)<<amount[tmp]<<setw(5)<<lendout[tmp]<<setw(50)<<name[tmp]<<setw(20)<<publisher[tmp]<<setw(12);
			datedecoder(date[tmp]);
			cout<<endl;
		}
	}
	else cout<<"查無相關資料"<<endl;
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
	cout<<"請輸入帳號:";
	cin>>str1;
	cout<<"請輸入密碼:";
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
	cout<<"請輸入書號:";
	cin>>borrowid;
	int bookindex=books.IDcheck(borrowid);
	if(bookindex!=-1){
		cout<<setw(5)<<"書號"<<setw(5)<<"庫存"<<setw(5)<<"借出"<<setw(50)<<"書名"<<setw(20)<<"出版社"<<setw(12)<<"出版日期"<<endl;
			cout<<setw(5)<<books.id[bookindex]<<setw(5)<<books.amount[bookindex]<<setw(5)<<books.lendout[bookindex]<<setw(50)<<books.name[bookindex]<<setw(20)<<books.publisher[bookindex]<<setw(12);
			datedecoder(books.date[bookindex]);
			cout<<endl;
		cout<<"請輸入數量:";
		cin>>amount;
		if(((amount+users.currentbooktatal[userindex])>users.MAX[userindex])){
			cout<<"超過使用者最大借閱量"<<endl;
		}
		else if(amount<0&&amount>books.amount[bookindex]){
			cout<<"超過庫存量或數量小於等於0"<<endl;
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
			cout<<"借閱成功"<<endl;
		}
	}
	else cout<<"無此書號"<<endl;
}
void ReturnFuntion(Member &users,Book &books,int userindex){
	int borrowid,amount;
	cout<<"請輸入歸還書號:";
	cin>>borrowid;
	int borrowindex=users.bookidsearch(userindex,borrowid);
	int bookindex=books.IDcheck(borrowid);
	if(borrowindex!=-1){
		cout<<"請輸入歸還數量:";
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
			cout<<"歸還成功"<<endl;
		}
		else cout<<"請勿輸入不符合的數量"<<endl;
	}
	else {
		if(bookindex==-1)cout<<"書號不存在"<<endl;
		else cout<<"無借閱此書"<<endl;
	}
}
void SearchFuntion(Book &books){
	int n,searchindex[100],total=0,num,year,month,day,state=1;
	char str[100];
	cout<<"資料搜尋\n1.書名\n2.書號\n3.出版商\n4.出版日期"<<endl;
	cin>>n;
	switch (n)
	{
	case 1:
		cout<<"請輸入關鍵字:";
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
		cout<<"請輸入書號:";
		cin>>num;
		if(books.IDcheck(num)!=-1){
			searchindex[total]=books.IDcheck(num); 
			total++;  
		}
		break;
	case 3:
		cout<<"請輸入關鍵字:";
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
		cout<<"請輸入日期(YYYY/MM/DD):";
		cin>>year;
		cin.ignore();
		cin>>month;
		cin.ignore();
		cin>>day;
		if(datechecker(year,month,day)){
			int searchdate=year*10000+month*100+day;
			cout<<"小於搜尋日期:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate>books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
			total=0;
			cout<<"等於搜尋日期:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate==books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
			total=0;
			cout<<"大於搜尋日期:"<<endl;
			for(int i=0;i<books.total;i++){
				if(searchdate<books.date[i]){
					searchindex[total]=i;
					total++;
				}
			}
			books.SearchPrint(total,searchindex);
		}
		else cout<<"日期格式錯誤"<<endl;
		break;
	default:
		cout<<"無此功能"<<endl;
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
	cout<<"更改會員資料"<<endl;
	cout<<"1.密碼\n2.名字\n3.Email\n4.地址\n5.手機號碼"<<endl;
	cout<<"請輸入:";
	cin>>n;
	switch (n)
	{
	case 1:
		cout<<"請輸入新密碼:";
		cin>>str;
		cout<<SecurityCode<<"\n請輸入驗證碼:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(password[userindex],str);
			cout<<"更改成功"<<endl;
		}
		else cout<<"驗證碼錯誤"<<endl;
		break;
	case 2:
		cout<<"請輸入新名字:";
		cin>>str;
		cout<<SecurityCode<<"\n請輸入驗證碼:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(name[userindex],str);
			cout<<"更改成功"<<endl;
		}
		else cout<<"驗證碼錯誤"<<endl;
		break;
	case 3:
		cout<<"請輸入新Email:";
		cin>>str;
		cout<<SecurityCode<<"\n請輸入驗證碼:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(email[userindex],str);
			cout<<"更改成功"<<endl;
		}
		else cout<<"驗證碼錯誤"<<endl;
		break;
	case 4:
		cout<<"請輸入新地址:";
		cin>>str;
		cout<<SecurityCode<<"\n請輸入驗證碼:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(adress[userindex],str);
			cout<<"更改成功"<<endl;
		}
		else cout<<"驗證碼錯誤"<<endl;
		break;
	case 5:
		cout<<"請輸入手機號碼:";
		cin>>str;
		cout<<SecurityCode<<"\n請輸入驗證碼:";
		cin>>inputcode;
		if(strcmp(inputcode,SecurityCode)==0){
			strcpy(cellNumber[userindex],str);
			cout<<"更改成功"<<endl;
		}
		else cout<<"驗證碼錯誤"<<endl;
		break;
	default:
		cout<<"無此功能"<<endl;
		break;
	}
}
void Book::DataRenew(){
	int n,newAmount,year,month,day,ID,bookindex;
	char str[50];
	printData();
	cout<<"更新書籍資料\n1.書籍名稱\n2.出版社名稱\n3.書籍總數\n4.出版日期"<<endl<<"請輸入:";
	cin>>n;
	cout<<"請輸入書號:";
	cin>>ID;
	bookindex=IDcheck(ID);
	if(bookindex!=-1){
		switch (n)
		{
		case 1:
			cout<<"請輸入新書名:";
			cin>>str;
			strcpy(name[bookindex],str);
			cout<<"更改成功"<<endl;
			break;
		case 2:
			cout<<"請輸入新出版社名稱:";
			cin>>str;
			strcpy(publisher[bookindex],str);
			cout<<"更改成功"<<endl;
			break;
		case 3:
			cout<<"請輸入新書籍總數:";
			cin>>newAmount;
			if(newAmount>=amount[bookindex]){
				amount[bookindex]=newAmount-lendout[bookindex];
				cout<<"更改成功"<<endl;
			}
			else cout<<"更改失敗!低於已借出書量"<<endl;
			break;
		case 4:
			cout<<"請輸入新出版日期(YYYY/MM/DD):";
			cin>>year;
			cin.ignore();
			cin>>month;
			cin.ignore();
			cin>>day;
			if(datechecker(year,month,day)){
				amount[bookindex]=year*10000+month*100+day;
				cout<<"更改成功"<<endl;
			}
			else cout<<"日期格式錯誤"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
			break;
		}
	}
	else cout<<"查無此書"<<endl;
}
void Member::MaxRenew(){
	int ID,newMAX;
	cout<<"以下是所有會員的最大借閱量"<<endl;
	cout<<setw(5)<<"ID"<<setw(10)<<"姓名"<<setw(12)<<"最大借閱量"<<setw(10)<<"借閱總數"<<endl;
	for(int i=0;i<total;i++){
		cout<<setw(5)<<id[i]<<setw(10)<<setw(10)<<name[i]<<setw(12)<<MAX[i]<<setw(10)<<currentbooktatal[i]<<endl;
	}
	cout<<"請輸入會員ID:";
	cin>>ID;
	int userindex=IDcheck(ID);
	if(userindex!=-1){
		cout<<"請輸入新的最大借閱量:";
		cin>>newMAX;
		if(newMAX>=currentbooktatal[userindex]){
			MAX[userindex]=newMAX;
			cout<<"更改成功!"<<endl;
		}
		else cout<<"失敗!低於已借閱數量"<<endl;
	}
	else cout<<"查無ID存在"<<endl;
}
void Book::Add(){
	int newID,year,month,day;
	cout<<"請輸入新書號:";
	cin>>newID;
	if(IDcheck(newID)==-1){
		id[total]=newID;
		cout<<"請輸入書名:";
		cin>>name[total];
		cout<<"請輸入出版社:";
		cin>>publisher[total];
		cout<<"請輸入出版日期(YYYY/MM/DD):";
		cin>>year;
		cin.ignore();
		cin>>month;
		cin.ignore();
		cin>>day;
		while(!datechecker(year,month,day)){
			cout<<"輸入錯誤!請重新輸入!"<<endl;
			cout<<"請輸入出版日期(YYYY/MM/DD):";
			cin>>year;
			cin.ignore();
			cin>>month;
			cin.ignore();
			cin>>day;
		}
		date[total]=year*10000+month*100+day;
		cout<<"請輸入書籍數量:";
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
		cout<<"新增成功"<<endl;
	}
	else cout<<"書號重複"<<endl;
}
void Book::Delete(){
	int clearID,bookindex;
	cout<<"請輸入刪除書號:";
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
			cout<<"刪除成功"<<endl;
		}
		else cout<<"書籍尚有借出無法刪除"<<endl;
	}
	else cout<<"查無書號"<<endl;
}
void Member::Add(){
	int newID;
	char str[50];
	cout<<"請輸入新ID:";
	cin>>newID;
	if(IDcheck(newID)==-1){
		id[total]=newID;
		cout<<"請輸入帳號:";
		cin>>str;
		if(accountcheck(str)==-1){
			strcpy(account[total],str);
			cout<<"請輸入密碼:";
			cin>>password[total];
			cout<<"請輸入姓名:";
			cin>>name[total];
			cout<<"請輸入Email:";
			cin>>email[total];
			cout<<"請輸入地址:";
			cin>>adress[total];
			cout<<"請輸入手機號碼:";
			cin>>cellNumber[total];
			cout<<"請輸入最多能借閱的書籍數量:";
			cin>>MAX[total];
			currentbooktatal[total] = 0;
			lendtatal[total] = 0;
			total++;
			cout<<"新增成功"<<endl;
		}
		else cout<<"帳號重複"<<endl;
	}
	else cout<<"ID重複"<<endl;
}
void Member::Delete(){
	int clearID,userindex;
	cout<<"請輸入刪除ID:";
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
			cout<<"刪除成功"<<endl;
		}
		else cout<<"使用者尚有借書無法刪除"<<endl;
	}
	else cout<<"查無ID"<<endl;
}
void MemberFuntion(Member &users,Book &books,int userindex){
	int n;
	do{
		system("CLS");
		cout<<"會員"<<users.name[userindex]<<"\n請選擇\n1.借書\n2.還書\n3.書籍查詢\n4.會員資料更新\n5.登出"<<endl;
		cout<<"請輸入";
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
			cout<<"將登出此功能"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
			break;
		}
		system("pause");
	}while(n!=5);
}
void AdministatorFuntion(Member &users,Book &books,Administator &admins,int adminindex){
	int n;
	do{
		system("CLS");
		cout<<"請選擇\n1.書籍資料更新\n2.會員最大借閱量更新\n3.新增書籍\n4.刪除書籍\n5.新增會員\n6.刪除會員\n7.登出"<<endl;
		cout<<"請輸入";
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
			cout<<"將登出此功能"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
			break;
		}
		system("pause");
	}while(n!=7);
}