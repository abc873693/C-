#include<iostream>
#include<string>
#include<vector>
#include <iomanip>
#include<fstream>
#include<cmath>
using namespace std;
typedef class list_node *list_pointer;
class list_node
{
public:
	string data;
	int index;
	list_pointer link_left;
	list_pointer link_right;
};
class untreated_node
{
public:
	untreated_node(string init_data,string init_direct):data(init_data),direct(init_direct){}
	string data;
	string direct;
};
void Node_Add(vector <untreated_node> &,string);
void Node_Link(list_pointer,vector <untreated_node> &,string,int);
int Node_Find(vector <untreated_node> &,string);
int direct2index(string);
void Node_Visit(string *,list_pointer);
void Node_Print(string *,int);
int main()
{
	string tmp;
	list_pointer root = NULL;
	vector <untreated_node> s;
	int max = 0 , count = 0;
	ifstream fin("input.txt");
	while(!fin.eof()){
		fin>>tmp;
		if(tmp=="()"){
			cout<<"Case "<<++count<<":";
			int index = Node_Find(s,"");
			if(index!=-1){
				for(unsigned int i = 0 ;i < s.size() ;i++){
					if( (int)s[i].direct.size() > max)max = (int)s[i].direct.size();
				}
				root = new list_node();
				Node_Link(root,s,"",index);
			}
			if(s.size()==0){
				cout<<"correct"<<endl;
				string *data = new string[1000];
				Node_Visit(data,root);
				Node_Print(data,max);
			}
			else cout<<"wrong data"<<endl;
			root = NULL;
			s.clear();
		}
		else Node_Add(s,tmp);
	}
	fin.close();
	system("pause");
	return 0;
}
void Node_Add(vector <untreated_node> &s,string str){
	int comma_loc = str.find(",",0) , max = s.size();
	string data,direct;
	data.assign(str,1,comma_loc-1);
	if(str[comma_loc+1]==')')direct = "";
	else direct.assign(str,comma_loc+1,str.size()-2-comma_loc);
	untreated_node tmp(data,direct);
	s.push_back(tmp);
}
void Node_Link(list_pointer node,vector <untreated_node> &s,string target,int index){
	if(node){
		node->data = s[index].data;
		node->index = direct2index(s[index].direct);
		s.erase(s.begin() + index);
		string left = target + "L" , right = target + "R";
		int index_left = Node_Find(s,left) ;
		if(index_left!=-1){
			node->link_left = new list_node();
			Node_Link(node->link_left,s,left,index_left);
		}
		else node->link_left = NULL;
		int index_right = Node_Find(s,right);
		if(index_right!=-1){
			node->link_right = new list_node();
			Node_Link(node->link_right,s,right,index_right);
		}
		else node->link_right = NULL;
	}
}
int Node_Find(vector <untreated_node> &s,string target){
	for(unsigned int i = 0 ;i < s.size();i++){
		if(s[i].direct == target)return i;
	}
	return -1;
}
int direct2index(string str){
	int loc = (int)pow(2,str.size()) , tmp = str.size()-1;
	for(int i=tmp;i>=0;i--){
		loc += (int)((str[i]=='R')? pow(2,tmp-i):0);
	}
	return loc;
}
void Node_Visit(string *s,list_pointer node){
	if(node){
		s[node->index] = node->data;
		Node_Visit(s,node->link_left);
		Node_Visit(s,node->link_right);
	}
}
void Node_Print(string *s , int max){
	for(int i=0 ;i<=max;i++){
		for(int space=(int)(pow(2,max-i))-2;space>=0;space--)cout<<"  ";
		for(int j=(int)(pow(2,i));j<(pow(2,i+1));j++){
			cout<<setw((int)(pow(2,max-i+2)))<<left<<s[j];
		}
		cout<<endl;
	}
}