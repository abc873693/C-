#include <fstream> 
#include <string>
#include <iomanip>
#include <vector>
#include "Library.h"
using namespace std;
Book::Book(string newID,string newname,string newpublisher,int newpublicationDate,int newremaining,int newlendout){
	ID=newID;
	name=newname;
	publisher=newpublisher;
	publicationDate=newpublicationDate;
	remaining=newremaining;
	lendout=newlendout;
}
Administator::Administator(string newaccount,string newpassword){
	account=newaccount;
	password=newpassword;
}
Member::Member(string newaccount,string newpassword,string newID,string newname,string newemail,string newadress,string newcellNumber,int newMAX,int newbookstotal,int newlendtotal):Administator(newaccount,newpassword){
	ID=newID;	
	name=newname;
	email=newemail;
	adress=newadress;
	cellNumber=newcellNumber;	
	MAX=newMAX;	
	bookstotal=newbookstotal;
	lendtotal=newlendtotal;
}
int Member::IDcheck(string ID){
	for(int i=0;i<lendtotal;i++){
		if(lendid[i]==ID)return i;
	}
	return -1;
}