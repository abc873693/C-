#include "LibaryData.h"
#include "Funtion.h"
#include <fstream> 
#include <iostream>
using namespace std;
int ReadMemberData(Member *user,char *MemberDataName){
	int total=0;
	ifstream fin(MemberDataName);	//開啟檔案讀取MemberDataName
	while ( !fin.eof() ) {	//按照MemberDataName裡的格式讀取相對應的資料
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
	cout<<"ReadMemberData finish"<<endl;	//讀取完顯示完成
	fin.close();	//關閉檔案
	return total;	//回傳使用者總數
}
int ReadAdministatorData(Administator *admin,char *AdministatorDataName){
	int total=0;
	ifstream fin(AdministatorDataName);	//開啟檔案讀取AdministatorDataName
	while ( !fin.eof() ) { //按照AdministatorDataName裡的格式讀取相對應的資料
		fin>>admin[total].account;
		fin>>admin[total].password;
		fin.get();
		total++;
	}
	cout<<"ReadAdministatorData finish"<<endl;	//讀取完顯示完成
	fin.close();	//關閉檔案
	return total;	//回傳管理員總數
}
int ReadBookData(Book *books,char *BookDataname){
	int total=0;
	ifstream fin(BookDataname);	//開啟檔案讀取BookDataname
	while ( !fin.eof() ) { //按照BookDataname裡的格式讀取相對應的資料
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
	cout<<"ReadBookData finish"<<endl; //讀取完顯示完成
	fin.close(); //關閉檔案
	return total; //回傳管理員總數
}
void WriteMemberData(Member *user,char *MemberDataName,int total){
	ofstream fout(MemberDataName); //開啟檔案寫入WriteMemberData
	for(int i=0;i<total;i++){	//按照檔案格式寫入檔案
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
	fout.close(); //關閉檔案
}
void WriteBookData(Book *books,char *BookDataname,int total){
	ofstream fout(BookDataname);	//開啟檔案寫入BookDataname
	for(int i=0;i<total;i++){ //按照檔案格式寫入檔案
		fout<<books[i].ID<<endl;
		fout<<books[i].name<<endl;
		fout<<books[i].lendout<<endl;
		fout<<books[i].remaining<<endl;
		fout<<books[i].publisher<<endl;
		fout<<books[i].publicationDate;
		if(i<total-1)fout<<endl<<endl;
	}
	fout.close(); //關閉檔案
}

int MemberAccountCheck(char *str,Member *user,int total){
	for(int i=0;i<total;i++){ //利用迴圈搜尋會員帳號是否存在
		if(strcmp(user[i].account,str)==0)return i; //存在回傳帳號所在的索引值
	}
	return -1; //找不到回傳-1
}
int MemberCheck(char *str,Member *user,int total){
	if(Checknum(str)){  //檢查是否為整數
		int searchID=atoi(str);  //將讀取的字串轉換成整數
		for(int i=0;i<total;i++){ //利用迴圈搜尋會員ID是否存在
			if(user[i].ID==searchID)return i; //存在回傳ID所在的索引值
		}
	}
	return -1;	//找不到回傳-1
}
int AdministatorCheck(char *str,Administator *admin,int total){
	for(int i=0;i<total;i++){	//利用迴圈搜尋管理員帳號是否存在
		if(strcmp(admin[i].account,str)==0)return i; //存在回傳帳號所在的索引值
	}
	return -1;	//找不到回傳-1
}
int BookCheck(char *str,Book *books,int total){
	if(Checknum(str)){  //檢查是否為整數
		int searchID=atoi(str); //將讀取的字串轉換成整數
		for(int i=0;i<total;i++){ //利用迴圈搜尋書號是否存在
			if(books[i].ID==searchID)return i; //存在回傳書號所在的索引值
		}
	}
	return -1; //找不到回傳-1
}
int Checkuserlend(int BookID,int ID,Member *user){
	for(int i=0;i<user[ID].lendtatal;i++){ //利用迴圈搜尋使用者借閱書號是否存在
		if(user[ID].lendid[i]==BookID)return i; //存在回傳書號所在的索引值
	}
	return -1; //找不到回傳-1
}
int MemberLogin(Member *user,Total &total){
	int index=0;
	bool susses=0;
	char acoont[20],password[20];
	do{ //無限迴圈直到帳號輸入成功
		cout<<"請輸入使用者帳號:";
		cin>>acoont;
		cout<<"請輸入使用者密碼:";
		cin>>password;
		index=MemberAccountCheck(acoont,user,total.Member); //利用會員帳號搜尋函式取得帳號的索引值
		if(index!=-1){
			if(strcmp(user[index].password,password)==0)susses=1;
			else cout<<"密碼錯誤請重新輸入"<<endl;
		}
		else {
			cout<<"帳號錯誤請重新輸入"<<endl;
		}
	}while(!susses);
	return index;
}
int AdministatorLogin(Administator *admin,Total &total){
	int index=0;
	bool susses=0;
	char acoont[20],password[20];
	do{ //無限迴圈直到帳號輸入成功
		cout<<"請輸入管理員帳號:";
		cin>>acoont;
		cout<<"請輸入管理員密碼:";
		cin>>password;
		index=AdministatorCheck(acoont,admin,total.Member);  //利用管理員帳號搜尋函式取得帳號的索引值
		if(index!=-1){
			if(strcmp(admin[index].password,password)==0)susses=1;
			else cout<<"密碼錯誤請重新輸入"<<endl;
		}
		else {
			cout<<"帳號錯誤請重新輸入"<<endl;
		}
	}while(!susses);
	return index;
}
void PrintAllBook(Book *books,int total){
	cout<<"以下是所有書籍資料:"<<endl;
	printf("%5s|%45s|%25s|%12s|%10s|%10s|\n","ID","書名","出版社","出版日期","借出量","庫存量");
	for(int i=0;i<total;i++){ //列印所有書籍資料
		cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
		printf("%5d|%45s|%25s|%12s|%10d|%10d|\n",books[i].ID,books[i].name,books[i].publisher,books[i].publicationDate,books[i].lendout,books[i].remaining);
	}
	cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
}
void NAMESearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	cout<<"請輸入關鍵字:";
	cin>>str;
	for(int i=0;i<total;i++){
		char *loc;  
		loc=strstr(book[i].name,str);  //搜尋是否有關鍵字在書名內
		if(loc!=NULL){
			arr[MAX]=i; //將書籍的索引值傳回陣列
			MAX++;  //增加搜尋數量
		}
	}
	//若無搜尋到則列印錯誤訊息
	if(MAX==0)cout<<"沒有任何符合關鍵字“"<<str<<"”的書名"<<endl;
	else cout<<"以下是符合關鍵字“"<<str<<"”的書名"<<endl;
}
void IDSearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	Numberinput(str,NULL);	//使用Numberinput函式確保輸入為整數
	for(int i=0;i<total;i++){
		if(atoi(str)==book[i].ID){ 
			arr[0]=i;
			MAX++;
		}
	}
	//若無搜尋到則列印錯誤訊息
	if(MAX==0)cout<<"沒有任何書號符合“"<<str<<"”"<<endl;
	else cout<<"以下是書號符合“"<<str<<"”"<<endl;
}
void PUBLISHERSearch(Book *book,int total,int *arr,int &MAX){
	char str[50];
	cout<<"請輸入關鍵字:";
	cin>>str;
	for(int i=0;i<total;i++){
		char *loc;
		loc=strstr(book[i].publisher,str);	 //搜尋是否有關鍵字在出版社名稱內
		if(loc!=NULL){
			arr[MAX]=i; //搜尋是否有關鍵字在出版社名稱內
			MAX++;	 //增加搜尋數量
		}
	}
	//若無搜尋到則列印錯誤訊息
	if(MAX==0)cout<<"沒有任何符合關鍵字“"<<str<<"”的出版社"<<endl;
	else cout<<"以下是符合關鍵字“"<<str<<"”的出版社"<<endl;
}
void DATASearch(Book *book,int total,int *arr,int &MAX){
	cout<<"1.小於搜尋日期"<<endl;
	cout<<"2.等於搜尋日期"<<endl;
	cout<<"3.大於搜尋日期"<<endl;
	char str[50];
	Numberinput(str,NULL);
	int mode=atoi(str);
	int searchdata,compare;
	char data[20],tmp[20];
	if((mode>=1&&mode<=3)){ //判斷模式是否存在 存在才繼續輸入日期
		cout<<"請輸入日期(YYYY/MM/DD):";
		cin>>data;
		strcpy(str,data);
		searchdata=dataDECODER(data);  //將字串格式的日期解碼成可以判斷的整數
		while(searchdata==-1){ //格式錯誤將重複輸入
			cout<<"格式錯誤請重新樹入:";
			cin>>data;
			strcpy(str,data); //先將要解碼的字串存到str 避免strtok更改字串 讓字串可以保留
			searchdata=dataDECODER(data);  //將字串格式的日期解碼成可以判斷的整數
		}
	}
	switch (mode) //根據選取功能做相對應的動作 將符合條件的存到arr陣列
	{
	case 1:
		strcpy(data,"小於“");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //先將要解碼的字串存到tmp 避免strtok更改字串 讓字串可以保留
			compare=dataDECODER(tmp);  //將字串格式的日期解碼成可以判斷的整數
			if(compare<searchdata){
				arr[MAX]=i; //符合條件的書籍索引值存到arr陣列
				MAX++;
			}
		}	
		break;
	case 2:
		strcpy(data,"等於“");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //先將要解碼的字串存到tmp 避免strtok更改字串 讓字串可以保留
			compare=dataDECODER(tmp); //將字串格式的日期解碼成可以判斷的整數
			if(compare==searchdata){
				arr[MAX]=i; //符合條件的書籍索引值存到arr陣列
				MAX++;
			}
		}	
		break;
	case 3:
		strcpy(data,"大於“");
		for(int i=0;i<total;i++){
			strcpy(tmp,book[i].publicationDate); //先將要解碼的字串存到tmp 避免strtok更改字串 讓字串可以保留
			compare=dataDECODER(tmp); //將字串格式的日期解碼成可以判斷的整數
			if(compare>searchdata){
				arr[MAX]=i; //符合條件的書籍索引值存到arr陣列
				MAX++;
			}
		}	
		break;
	default:
		cout<<"無此功能"<<endl;
		break;
	}
	if(MAX==0&&(mode>=1&&mode<=3)){ //若MAX=0 則顯示無找到任何書籍
		strcat(data,str);
		printf("沒有任何日期%s”\n",data);
	}
	else printf("以下是符合日期“%s”的書籍\n",str);
}
void Searchfution(Book *books,int total,char *name){
	int Searcharr[200],MAX,mode;
	char str[50];
	do{
		MAX=0;
		system("CLS");
		cout<<"歡迎"<<name<<endl;	
		cout<<"2.查詢功能(使用者)"<<endl;
		cout<<"	1.書名"<<endl;
		cout<<"	2.書號"<<endl;
		cout<<"	3.出版商"<<endl;
		cout<<"	4.出版日期"<<endl;
		cout<<"	5.登出並返回主畫面"<<endl;
		Numberinput(str,NULL);	//使用Numberinput函式確保輸入為整數
		mode=atoi(str);	//轉換str成整數
		switch(mode){
		case 1:
			cout<<"搜尋書名"<<endl;
			NAMESearch(books,total,Searcharr,MAX); //搜尋書名關鍵字函式
			break;
		case 2:
			cout<<"搜尋書號"<<endl;
			IDSearch(books,total,Searcharr,MAX);  //搜尋書號函式
			break;
		case 3:
			cout<<"搜尋出版社"<<endl;
			PUBLISHERSearch(books,total,Searcharr,MAX);	//搜尋出版社名稱關鍵字函式
			break;
		case 4:
			cout<<"搜尋日期"<<endl;
			DATASearch(books,total,Searcharr,MAX);		//搜尋日期函式
			break;
		case 5:
			cout<<"將離開查詢功能"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
		}
		if(MAX>0){	//列印所尋到的書籍資料
			printf("%5s|%45s|%25s|%12s|%10s|%10s|\n","ID","書名","出版社","出版日期","借出量","庫存量");
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
		cout<<"會員"<<user[IDidnex].name<<endl;
		cout<<"更改會員資料"<<endl;
		cout<<"	1.密碼"<<endl;
		cout<<"	2.名字"<<endl;
		cout<<"	3.Email"<<endl;
		cout<<"	4.地址"<<endl;
		cout<<"	5.手機號碼"<<endl;
		cout<<"	6.登出並返回更新功能"<<endl;
		Numberinput(str,"欲更改資料"); //使用Numberinput函式確保輸入為整數
		mode = atoi(str); //將str轉換成整數
		switch (mode)
		{
		case 1:
			if(AuthInput(str,"新密碼")){ //驗證碼輸入判斷 若驗證碼輸入成 則更改成功
				if(strcmp(str,user[IDidnex].password)==0)cout<<"與原先密碼相同"<<endl; //判斷是否與原資料相同
				else{
					strcpy(user[IDidnex].password,str);
					cout<<"密碼更新完成!"<<endl;
				}
			}
			else cout<<"驗證碼輸入失敗"<<endl;
			break;
		case 2:
			if(AuthInput(str,"新名字")){ //驗證碼輸入判斷 若驗證碼輸入成 則更改成功
				if(strcmp(str,user[IDidnex].name)==0)cout<<"與原先名字相同"<<endl;//判斷是否與原資料相同
				else {
					strcpy(user[IDidnex].name,str);
					cout<<"名字更新完成!"<<endl;
				}
			}
			else cout<<"驗證碼輸入失敗"<<endl;
			break;
		case 3:
			if(AuthInput(str,"新Eamil")){ //驗證碼輸入判斷 若驗證碼輸入成 則更改成功
				if(strcmp(str,user[IDidnex].email)==0)cout<<"與原先Email相同"<<endl;//判斷是否與原資料相同
				else {
					strcpy(user[IDidnex].email,str);
					cout<<"Email更新完成!"<<endl;
				}
			}
			else cout<<"驗證碼輸入失敗"<<endl;
			break;
		case 4:
			if(AuthInput(str,"新地址")){ //驗證碼輸入判斷 若驗證碼輸入成 則更改成功
				if(strcmp(str,user[IDidnex].adress)==0)cout<<"與原先地址相同"<<endl;//判斷是否與原資料相同
				else {
					strcpy(user[IDidnex].adress,str);
					cout<<"地址更新完成!"<<endl;
				}
			}
			else cout<<"驗證碼輸入失敗"<<endl;
			break;
		case 5:
			if(AuthInput(str,"新手機號碼")){ //驗證碼輸入判斷 若驗證碼輸入成 則更改成功
				if(strcmp(str,user[IDidnex].cellNumber)==0)cout<<"與原先電話號碼相同"<<endl;//判斷是否與原資料相同
				else {
					strcpy(user[IDidnex].cellNumber,str);
					cout<<"手機號碼更新完成!"<<endl;
				}
			}
			else cout<<"驗證碼輸入失敗"<<endl;
			break;
		case 6:
			cout<<"將離開此系統"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
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
		cout<<"歡迎 "<<name<<endl;
		PrintAllBook(books,total); //列印所有書籍資料
		cout<<"更新書籍資料"<<endl;
		cout<<"	1.書籍名稱"<<endl;
		cout<<"	2.出版社名稱"<<endl;
		cout<<"	3.書籍總數"<<endl;
		cout<<"	4.出版日期"<<endl;
		cout<<"	5.登出返回更新功能"<<endl;
		Numberinput(str,NULL); //使用Numberinput函式確保輸入為整數
		mode=atoi(str); //將str轉換成整數
		if(mode>=1&&mode<=4){
			Numberinput(str,"書號"); //使用Numberinput函式確保輸入為整數
			BookIndex=BookCheck(str,books,total); //搜尋書號是否存在
			if(BookIndex!=-1){
				switch (mode)
				{
				case 1:
					cout<<"請輸入愈更改書籍名稱:";
					cin.get();  //將上次的buffer的字串清除 避免cin.getline讀取到
					cin.getline(str,50); //整行讀取(包含換行字元)
					if(strcmp(books[BookIndex].name,str)==0)cout<<"與原先書名相同"<<endl; //判斷是否與原資料相同
					else {
						strcpy(books[BookIndex].name,str);
						cout<<"更改成功!"<<endl;
					}
					break;
				case 2:
					cout<<"請輸入愈更改出版社名稱:";
					cin.get();  //將上次的buffer的字串清除 避免cin.getline讀取到
					cin.getline(str,50); //整行讀取(包含換行字元)
					if(strcmp(books[BookIndex].publisher,str)==0)cout<<"與原先出版社相同"<<endl; //判斷是否與原資料相同
					else {
						strcpy(books[BookIndex].publisher,str);
						cout<<"更改成功!"<<endl;
					}
					break;
				case 3:
					Numberinput(str,"愈更改數量"); //使用Numberinput函式確保輸入為整數
					amount=atoi(str);  //將str轉換成整數
					if(amount<(books[BookIndex].lendout)||(amount<(books[BookIndex].lendout+books[BookIndex].remaining))){
						cout<<"錯誤!!數量小於借出的數量或總數"<<endl;  //判斷更改數量是否低於借出量
					}
					else if(amount==(books[BookIndex].remaining+books[BookIndex].lendout))cout<<"與原先數量相同"<<endl; //判斷是否與原資料相同
					else {
						books[BookIndex].remaining=amount-books[BookIndex].lendout;
						cout<<"更改成功"<<endl;
					}
					break;
				case 4:
					cout<<"請輸入愈更改日期(YYYY/MM/DD):";
					char tmp[20];
					cin>>str;
					strcpy(tmp,str);
					if(dataDECODER(str)==-1)cout<<"錯誤格式!更改失敗"<<endl; //判斷日期格式是否正確
					else {
						if(strcmp(books[BookIndex].publicationDate,tmp)==0)cout<<"與原先出版日期相同"<<endl;
						else {
							strcpy(books[BookIndex].publicationDate,tmp);
							cout<<"更改成功!"<<endl;
						}
					}
					break;
				default:
					break;
				}
			}
			else cout<<"無搜尋此書"<<endl;
		}
		else if(mode==5)cout<<"將離開更新功能"<<endl;
		else cout<<"無此功能"<<endl;
		system("pause");
	}while(mode!=5);
}
void Renewfution(Book *books,Member *user,Administator *admin,Total &total){
	char str[20];
	int IDindex,mode;
	do{
		system("CLS");
		cout<<"3更新功能"<<endl;
		cout<<"	1.更新書籍資料(管理員)"<<endl;
		cout<<"	2.更新會員最大借閱量(管理員)"<<endl;
		cout<<"	3.更新會員資料(使用者)"<<endl;
		cout<<"	4.返回主畫面"<<endl;
		Numberinput(str,NULL);	//使用Numberinput函式確保輸入為整數
		mode=atoi(str); //str轉整數
		switch(mode){
		case 1:
			cout<<"更新書籍資料"<<endl;
			IDindex=AdministatorLogin(admin,total); //管理員登入回傳管理員索引值
			strcpy(str,admin[IDindex].account); //將管理員名字放在str
			RenewBookData(books,total.Book,str); //呼叫書籍更新軟體
			break;
		case 2:
			cout<<"更新會員最大借閱數量資料"<<endl;
			IDindex=AdministatorLogin(admin,total); //管理員登入回傳管理員索引值
			cout<<"歡迎 "<<admin[IDindex].account<<endl;
			cout<<"以下是所有會員的最大借閱數量:"<<endl;
			printf("%5s|%20s|%12s|\n","ID","名字","最大借閱量");
			for(int i=0;i<total.Member;i++){	//顯示所有使用者的最大借閱量
				cout<<"-----------------------------------------"<<endl;
				printf("%5d|%20s|%12d|\n",user[i].ID,user[i].name,user[i].MAXlendamount);
			}
			cout<<"-----------------------------------------"<<endl;
			Numberinput(str,"欲更改的使用者ID");
			IDindex=MemberCheck(str,user,total.Member);	//檢查使用者ID回傳其所在索引值
			if(IDindex!=-1){
				Numberinput(str,"欲更改數量");	//使用Numberinput函式確保輸入為整數
				int amount=atoi(str);	//str轉整數
				if(amount<(user[IDindex].lendtatal)){	//判斷數量是否低於目前借閱總數
					cout<<"錯誤!!數量小於已借入數量"<<endl;
				}
				else {
					user[IDindex].MAXlendamount=amount;
					cout<<"更改成功"<<endl;
				}
			}
			else {
				cout<<"查無此ID"<<endl;
			}
			system("pause");
			break;
		case 3:
			cout<<"更新會員個人資料"<<endl;
			IDindex=MemberLogin(user,total); //會員登入回傳管理員索引值
			RenewMemberData(user,IDindex);
			break;
		case 4:
			cout<<"將離開並回到主選單"<<endl;
			system("pause");
			break;
		default:
			cout<<"無此功能"<<endl;
			system("pause");
			break;
		}
	}while(mode!=4);
}

void BorrowBook(Book *books,Member *user,Total &total,int userIDindex){
	char str[50];
	cout<<"借書功能"<<endl;
	Numberinput(str,"欲借閱書號");	//使用Numberinput函式確保輸入為整數
	int arrPosition=BookCheck(str,books,total.Book);	//搜尋書號是否存在是回傳書號的索引值否則回傳-1
	int BookID=books[arrPosition].ID,max;
	if(arrPosition!=-1){	//判斷是否有此書
		cout<<"--------------------------------------"<<endl;
		cout<<"書號:"<<books[arrPosition].ID<<endl;
		cout<<"書名:"<<books[arrPosition].name<<endl;
		cout<<"出版商:"<<books[arrPosition].publisher<<endl;
		cout<<"出版日期:"<<books[arrPosition].publicationDate<<endl;
		cout<<"已借出數量:"<<books[arrPosition].lendout<<endl;
		cout<<"館內庫存數量:"<<books[arrPosition].remaining<<endl;
		cout<<"--------------------------------------"<<endl;
		Numberinput(str,"欲借閱數量");	//使用Numberinput函式確保輸入為整數
		int amount = atoi(str);
		if((amount+user[userIDindex].currentbooktatal)>user[userIDindex].MAXlendamount){ //判斷借閱數量是否超過使用者最大借閱量
			cout<<"錯誤!!借閱數量超過使用者最大借閱量"<<endl;	
		}
		else if((amount)>books[arrPosition].remaining){  //判斷借閱數量是否超過庫存數量
			cout<<"錯誤!!借閱數量超過館內庫存數量"<<endl;	
		}
		else if(amount==0){		//判斷輸入為0
			cout<<"請勿輸入0"<<endl;
		}
		else { //成功借書
			books[arrPosition].lendout+=amount;
			books[arrPosition].remaining-=amount;
			if(Checkuserlend(BookID,userIDindex,user)==-1){ 
				//呼叫Checkuserlend函式檢查使用者是否有借這本書
				//若無則新增書號至陣列
				max=user[userIDindex].lendtatal;
				user[userIDindex].lendid[max]=BookID;
				user[userIDindex].lendamount[max]=amount;
				user[userIDindex].lendtatal++;
			}
			else{
				//搜尋在使用借閱的陣列增加數量
				max=Checkuserlend(BookID,userIDindex,user);
				user[userIDindex].lendamount[max]+=amount;
			}
			user[userIDindex].currentbooktatal+=amount; //在使用者借閱書籍總數增加數量
			cout<<"借閱成功!!"<<endl; //成功訊息
		}
	}
	else {
		cout<<"錯誤!!查無此書"<<endl;
	}
}
void RetuenBook(Book *books,Member *user,Total &total,int userIDindex){
	cout<<"還書功能"<<endl<<"以下是您所有借閱的書籍"<<endl;
	printf("%5s|%45s|%10s|\n","書號","書名","借閱數量");	//列印所有借閱書籍
	for(int i=0;i<user[userIDindex].lendtatal;i++){
		int bookid=user[userIDindex].lendid[i];
		char IDstr[10];
		itoa(bookid, IDstr,10);		//將書號轉成字串格式
		int position= BookCheck(IDstr,books,total.Book);	//呼叫BookCheck函式搜尋書號的索引值
		cout<<"--------------------------------------------------------------------"<<endl;
		printf("%5d|%45s|%10d|\n",bookid,books[position].name,user[userIDindex].lendamount[i]);
	}
	cout<<"--------------------------------------------------------------------"<<endl;
	char str[20];
	Numberinput(str,"欲歸還書號");	//使用Numberinput函式確保輸入為整數
	int ReturnID=atoi(str);
	int lendIDposition=Checkuserlend(ReturnID,userIDindex,user);	//檢查使用者是否借閱此書
	int arrPosition=BookCheck(str,books,total.Book);	//呼叫BookCheck函式搜尋書號的索引值
	if(lendIDposition!=-1){		//執行還書動作
		books[arrPosition].remaining+=user[userIDindex].lendamount[lendIDposition];
		books[arrPosition].lendout-=user[userIDindex].lendamount[lendIDposition];
		user[userIDindex].currentbooktatal-=user[userIDindex].lendamount[lendIDposition];
		for(int i=lendIDposition;i<user[userIDindex].lendtatal-1;i++){	//刪除原先資料
			user[userIDindex].lendamount[i]=user[userIDindex].lendamount[i+1];
			user[userIDindex].lendid[i]=user[userIDindex].lendid[i+1];
		}
		user[userIDindex].lendtatal--;
		cout<<"完成還書!"<<endl;
	}
	else {
		cout<<"無借此書"<<endl;
	}
}
void BorrowFuntion(Book *books,Member *user,Total total,int IDindex){
	char str[10];
	int mode;
	do{
		system("CLS");
		cout<<"歡迎"<<user[IDindex].name<<endl;
		cout<<"2借還書功能"<<endl;
		cout<<"	1.書籍借閱"<<endl;
		cout<<"	2.書籍歸還"<<endl;
		cout<<"	3.登出並離開"<<endl;
		Numberinput(str,"欲使用功能");	//使用Numberinput函式確保輸入為整數
		mode=atoi(str);	//將字串轉換成整數
		switch (mode)	//按照選的模式執行不同的功能
		{
		case 1:
			BorrowBook(books,user,total,IDindex);	//呼叫借書函式
			break;
		case 2:
			if(user[IDindex].lendtatal==0)cout<<"使用者無借閱任何書籍"<<endl;	//判斷使用者是否有借閱書籍
			else RetuenBook(books,user,total,IDindex);	//還書函式
			break;
		case 3:
			cout<<"將離開借還書功能"<<endl;	//輸入3結束借閱功能
			break;
		default:
			cout<<"無此功能"<<endl;	//其他數字時選項
			break;
		}
		system("pause");
	}while(mode!=3); //輸入3 離開無限迴圈
}

void AddBook(Book *books,Total &total){
	char str[20],tmp[20];
	Numberinput(str,"欲新增書號");  //使用Numberinput函式確保輸入為整數
	int arrID=BookCheck(str,books,total.Book);  //搜尋書號是否存在
	if(arrID==-1){  //新增書籍
		int index=total.Book;
		books[index].ID=atoi(str);
		cin.get();	//將上次的buffer的字串清除 避免cin.getline讀取到
		cout<<"請輸入書名:";
		cin.getline(books[index].name,50); //整行讀取(包含換行字元)
		cout<<"請輸入出版社:";
		cin.getline(books[index].publisher,50); //整行讀取(包含換行字元)
		cout<<"請輸入出版日期(YYYY/MM/DD):";
		cin>>str;
		strcpy(tmp,str);
		while(dataDECODER(str)==-1){  //判斷日期格式是否正確
			cout<<"輸入錯誤!請重新輸入!"<<endl;
			cout<<"請輸入出版日期(YYYY/MM/DD):";
			cin>>str;
			strcpy(tmp,str);
		}
		strcpy(books[index].publicationDate,tmp);
		Numberinput(str,"書籍數量");  //使用Numberinput函式確保輸入為整數
		books[index].remaining = atoi(str);
		books[index].lendout = 0;
		total.Book++;
		cout<<"新增成功!!"<<endl;
		for(int i=0;i<total.Book-1;i++){   //根據書號排列
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
		cout<<"錯誤!!書號重複"<<endl;
	}
}

void DeleteBook(Book *books,Total &total){
	char str[20];
	PrintAllBook(books,total.Book);  //列印所有書籍
	Numberinput(str,"欲刪除書號");	//使用Numberinput函式確保輸入為整數
	int arrID=BookCheck(str,books,total.Book);  //尋書號是否存在
	if(arrID==-1){
		cout<<"錯誤!查無此書號"<<endl;
	}
	else if(books[arrID].lendout>0){  //若還有書借出則無法刪除
		cout<<"錯誤!書籍尚有借出 無法刪除"<<endl;
	}
	else {
		for(int i=arrID;i<total.Book-1;i++){ //利用迴圈將原本的資料覆蓋
			books[i]=books[i+1];
		}
		total.Book--;
		cout<<"刪除成功!!"<<endl;

	}
}

void AddMember(Member *user,Total &total){
	char str[20];
	Numberinput(str,"欲新增ID"); //使用Numberinput函式確保輸入為整數
	int arrID=MemberCheck(str,user,total.Member); //搜尋會員是否存在
	if(arrID==-1){
		int index=total.Member;
		user[index].ID = atoi(str);
		cout<<"請輸入帳號:";
		cin>>str;
		arrID=MemberAccountCheck(str,user,total.Member); //搜尋帳號是否有使用過
		if(arrID==-1){
			strcpy(user[index].account,str);
			cout<<"請輸入密碼:";
			cin>>user[index].password;
			cout<<"請輸入姓名:";
			cin>>user[index].name;
			cout<<"請輸入email:";
			cin>>user[index].email;
			cout<<"請輸入地址:";
			cin>>user[index].adress;
			cout<<"請輸入手機號碼:";
			cin>>user[index].cellNumber;
			Numberinput(str,"最大使用者借閱量");  //使用Numberinput函式確保輸入為整數
			user[index].MAXlendamount = atoi(str);
			user[index].currentbooktatal=0;
			user[index].lendtatal=0;
			total.Member++;
			cout<<"新增成功!!"<<endl;
			for(int i=0;i<total.Member-1;i++){  //根據ID排序
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
		else cout<<"錯誤!!帳號重複"<<endl;
	}
	else {
		cout<<"錯誤!!ID重複"<<endl;
	}
}
void DeleteMember(Member *user,Total &total){
	char str[20];
	Numberinput(str,"欲刪除使用者ID"); //使用Numberinput函式確保輸入為整數
	int arrID=MemberCheck(str,user,total.Member); //搜尋ID是否存在
	if(arrID==-1){
		cout<<"錯誤!查無此ID"<<endl;
	}
	else if(user[arrID].lendamount>0){ //若使用者仍有借閱書籍 則無法刪除
		cout<<"錯誤!使用者尚有借閱書籍 無法刪除"<<endl;
	}
	else {
		for(int i=arrID;i<total.Member-1;i++){	//利用迴圈將原本的資料覆蓋
			user[i]=user[i+1];
		}
		total.Member--;
		cout<<"刪除成功!!"<<endl;
	}
}
void Addfution(Book *books,Member* user,Administator *admin,Total &total){
	char str[50];
	int mode,arrID;
	arrID=AdministatorLogin(admin,total);  //管理員登入回傳管理員所在索引值
	do{
		system("CLS");
		cout<<"歡迎"<<admin[arrID].account<<endl;
		cout<<"4新增功能"<<endl;
		cout<<"	1.新增書籍"<<endl;
		cout<<"	2.刪除書籍"<<endl;
		cout<<"	3.新增會員"<<endl;
		cout<<"	4.刪除會員"<<endl;
		cout<<"	5.登出並返回主選單"<<endl;
		Numberinput(str,NULL);  //使用Numberinput函式確保輸入為整數
		mode=atoi(str);
		switch (mode)
		{
		case 1:
			cout<<"新增書籍"<<endl;
			AddBook(books,total); //呼叫新增書籍函式
			break;
		case 2:
			cout<<"刪除書籍"<<endl;
			DeleteBook(books,total); //呼叫刪除書籍函式
			break;
		case 3:
			cout<<"新增會員"<<endl;
			AddMember(user,total);  //呼叫新增會員函式
			break;
		case 4:
			cout<<"新增會員"<<endl;
			DeleteMember(user,total); //呼叫刪除會員函式
			break;
		case 5:
			cout<<"將結束新增功能並返回主選單"<<endl;
			break;
		default:
			cout<<"無此功能"<<endl;
			break;
		}
		system("pause");
	}while(mode!=5);
}