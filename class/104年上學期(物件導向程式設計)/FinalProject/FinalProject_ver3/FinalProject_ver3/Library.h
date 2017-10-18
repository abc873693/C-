using namespace std;
class Book{
public:
	Book(string ,string ,string ,int ,int ,int );
	string ID;	
	string name;
	string publisher;
	int publicationDate;
	int remaining;
	int lendout;
};
class Administator
{
public:
	Administator(string ,string );
	string account;
	string password;
private:
};
class Member:public Administator
{
public:
	Member(string ,string ,string ,string ,string ,string ,string ,int ,int ,int);
	string ID;	
	string name;
	string email;
	string adress;
	string cellNumber;	
	int MAX;	
	int bookstotal;
	int lendtotal;
	vector <string> lendid;
	vector <int> lendamount;
	int Member::IDcheck(string);
private:
};