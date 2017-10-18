class Member{
public:
	int ID;	//�|��ID
	char account[20]; //�|���b��
	char password[20];	//�|���K�X
	char name[20];	//�|���m�W
	char email[20];	//�|��Email
	char adress[20];	//�|���a�}
	char cellNumber[15];	//�|���q��
	int MAXlendamount;	//�|���̤j�ɾ\�ƶq
	int currentbooktatal;	//�|���ثe�ɾ\�`��
	int lendtatal;	//�|���ɾ\���P�W�ٮ��y���`��
	int lendid[50];	//�|���Ҧ��ɾ\���y��ID
	int lendamount[50];	//�|���Ҧ����y�ɾ\�`��
};
class Administator{
public:
	char account[20];	//�޲z���b��
	char password[20];	//�޲z���K�X
};
class Book{
public:
	int ID;	//�Ѹ�
	char name[50];	//�ѦW
	char publisher[50];	//���y�X����
	char publicationDate[20];	//���y�X�����
	int remaining;	//���y�w�s�q
	int lendout;	//���y�ɥX�q
};
class Total{
public:
	int Member;	//�����|�����`��
	int Administator;	//�����޲z���`��
	int Book;	//�������y�`��
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