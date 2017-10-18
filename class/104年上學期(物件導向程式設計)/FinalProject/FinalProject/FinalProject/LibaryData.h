class Member{
public:
	int ID;	//會員ID
	char account[20]; //會員帳號
	char password[20];	//會員密碼
	char name[20];	//會員姓名
	char email[20];	//會員Email
	char adress[20];	//會員地址
	char cellNumber[15];	//會員電話
	int MAXlendamount;	//會員最大借閱數量
	int currentbooktatal;	//會員目前借閱總數
	int lendtatal;	//會員借閱不同名稱書籍的總數
	int lendid[50];	//會員所有借閱書籍的ID
	int lendamount[50];	//會員所有書籍借閱總數
};
class Administator{
public:
	char account[20];	//管理員帳號
	char password[20];	//管理員密碼
};
class Book{
public:
	int ID;	//書號
	char name[50];	//書名
	char publisher[50];	//書籍出版社
	char publicationDate[20];	//書籍出版日期
	int remaining;	//書籍庫存量
	int lendout;	//書籍借出量
};
class Total{
public:
	int Member;	//紀錄會員的總數
	int Administator;	//紀錄管理員總數
	int Book;	//紀錄書籍總數
};
int ReadMemberData(Member *,char *);
int ReadAdministatorData(Administator *,char *);
int ReadBookData(Book *,char *);
void WriteMemberData(Member *,char *,int);
void WriteBookData(Book *,char *,int);
int MemberCheck(char *,Member *,int );
int MemberAccountCheck(char *,Member *,int);
int AdministatorCheck(char *,Administator *,int);
int MemberLogin(Member *,Total &);
int AdministatorLogin(Administator *,Total &);
int BookCheck(char *,Book *,int );
int Checkuserlend(int ,int ,Member *);
void PrintAllBook(Book *,int );
void Searchfution(Book*,int,char *);
void NAMESearch(Book *,int,int *,int &);
void IDSearch(Book *,int ,int *,int &);
void PUBLISHERSearch(Book *,int ,int *,int &);
void DATASearch(Book *,int ,int *,int &);
void RenewMemberData(Member *,int );
void RenewBookData(Book *,int ,char *);
void Renewfution(Book *,Member *,Administator *,Total &);
void BorrowBook(Book *,Member *,Total &,int );
void RetuenBook(Book *,Member *,Total &,int );
void BorrowFuntion(Book *,Member *,Total ,int);
void Addfution(Book *,Member* ,Administator *,Total &);
void AddBook(Book *,Total &);
void DeleteBook(Book *,Total &);
void AddMember(Member *,Total &);
void DeleteMember(Member *,Total &);