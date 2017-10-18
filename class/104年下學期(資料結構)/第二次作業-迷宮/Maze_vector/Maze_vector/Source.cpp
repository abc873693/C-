#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
class Mazedata
{
public:
	Mazedata(int inti_i = 0,int inti_j = 0,int inti_direct = 0):i(inti_i),j(inti_j),direct(inti_direct){}
	void set(int new_i = 0 ,int new_j = 0,int new_direct = 0){
		i=new_i;
		j=new_j;
		direct=new_direct;
	}
	int i;
	int j;
	int direct;
};
void ReadMazeData(string,Mazedata & ,Mazedata &);
bool Check(int i,int j);
int MAX_i,MAX_j;
char Maze[100][100];
int main(){
	int x=0;
	vector <Mazedata> datastack;
	Mazedata start,end;
	ReadMazeData("input.txt",start,end);
	Maze[start.i][start.j]='S';
	Mazedata token(start.i,start.j);
	do{
		int i=token.i,j=token.j;
		switch (token.direct)
		{
		case 0:
			if(Check(i,j+1)){
				datastack.push_back(token);
				Maze[i][j+1]='*';
				token.set(i,j+1,-1);
			}
			break;
		case 1:
			if(Check(i+1,j)){
				datastack.push_back(token);
				Maze[i+1][j]='*';
				token.set(i+1,j,-1);
			}
			break;
		case 2:
			if(Check(i,j-1)){
				datastack.push_back(token);
				Maze[i][j-1]='*';
				token.set(i,j-1,-1);
			}
			break;
		case 3:
			if(Check(i-1,j)){
				datastack.push_back(token);
				Maze[i-1][j]='*';
				token.set(i-1,j,-1);
			}
			break;
		default:
			if(i==end.i&&j==end.j){
				x++;
				Maze[end.i][end.j]='D';
				Maze[start.i][start.j]='S';
				cout<<"第"<<x<<"種"<<endl;
				for(int i=0;i<MAX_i;i++){
					for(int j=0;j<MAX_j;j++){
						if(Maze[i][j]=='1')cout<<"■";
						else if(Maze[i][j]=='0')cout<<"  ";
						else cout<<Maze[i][j]<<" ";
					}
					cout<<endl;
				}
			}
			Maze[token.i][token.j]='0';
			int size=datastack.size()-1;
			token.set(datastack[size].i,datastack[size].j,datastack[size].direct);
			datastack.pop_back();
			break;
		}
		token.direct++;
	}while(!(datastack.size()==0 && token.direct==4));
	if(x==0)cout<<"此名迷宮無任何解"<<endl;
	system("pause");
}
void ReadMazeData(string filename,Mazedata &start,Mazedata &end){
	ifstream fin(filename);
	fin>>MAX_i>>MAX_j;
	for(int i=0;i<MAX_i;i++)
		for(int j=0;j<MAX_j;j++)
			fin>>Maze[i][j];
	fin>>start.i>>start.j>>end.i>>end.j;
	fin.close();
}
bool Check(int i,int j){
	if(Maze[i][j]=='0')return true;
	else return false;
}