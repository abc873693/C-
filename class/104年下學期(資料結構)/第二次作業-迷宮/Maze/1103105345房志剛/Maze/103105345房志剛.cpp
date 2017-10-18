#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
class Mazedata
{
public:
	int i;
	int j;
	int direct;
};
void ReadMazeData(string,Mazedata & ,Mazedata &);
void pushdata(Mazedata);
void popdata();
bool Check(int i,int j);
int MAX=0;
Mazedata datastack[100];
int MAX_i,MAX_j;
char Maze[100][100];
int main(){
	int x=0;
	Mazedata start,end;
	ReadMazeData("input.txt",start,end);
	Maze[start.i][start.j]='S';
	Mazedata tmp;
	tmp.i=start.i;
	tmp.j=start.j;
	tmp.direct=0;
	pushdata(tmp);
	do{
		int i=datastack[MAX-1].i,j=datastack[MAX-1].j;
		switch (datastack[MAX-1].direct)
		{
		case 0:
			if(Check(i,j+1)){
				tmp.i=i;
				tmp.j=j+1;
				tmp.direct=-1;
				pushdata(tmp);
			}
			break;
		case 1:
			if(Check(i+1,j)){
				tmp.i=i+1;
				tmp.j=j;
				tmp.direct=-1;
				pushdata(tmp);
			}
			break;
		case 2:
			if(Check(i,j-1)){
				tmp.i=i;
				tmp.j=j-1;
				tmp.direct=-1;
				pushdata(tmp);
			}
			break;
		case 3:
			if(Check(i-1,j)){
				tmp.i=i-1;
				tmp.j=j;
				tmp.direct=-1;
				pushdata(tmp);
			}
			break;
		default:
			if(datastack[MAX-1].i==end.i&&datastack[MAX-1].j==end.j){
				x++;
				Maze[end.i][end.j]='D';
				Maze[start.i][start.j]='S';
				cout<<"第"<<x<<"種"<<endl;
				for(int i=0;i<MAX_i;i++){
					for(int j=0;j<MAX_j;j++){
						cout<<Maze[i][j]<<" ";
					}
					cout<<endl;
				}
			}
			popdata();
			break;
		}
		datastack[MAX-1].direct++;
	}while(datastack[0].direct!=4);
	if(x==0)cout<<"此名迷宮無任何解"<<endl;
	system("pause");
}
void ReadMazeData(string filename,Mazedata &start,Mazedata &end){
	ifstream fin(filename);
	fin>>MAX_i>>MAX_j;
	for(int i=0;i<MAX_i;i++){
		for(int j=0;j<MAX_j;j++){
			fin>>Maze[i][j];
		}
	}
	fin>>start.i>>start.j;
	fin>>end.i>>end.j;
	fin.close();
}
void pushdata(Mazedata data){
	datastack[MAX].i=data.i;
	datastack[MAX].j=data.j;
	datastack[MAX].direct=data.direct;
	Maze[data.i][data.j]='*';
	MAX++;
}
void popdata(){
	Maze[datastack[MAX-1].i][datastack[MAX-1].j]='0';
	MAX--;
	datastack[MAX].i=NULL;
	datastack[MAX].j=NULL;
	datastack[MAX].direct=NULL;
}
bool Check(int i,int j){
	if(Maze[i][j]=='0')return true;
	else return false;
}