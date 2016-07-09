#include<iostream>
using namespace std;
class line{
public:
	int number;
	int station[22];
	int station_max;
	int relate[102][3];
	int relate_max;
	//relate[0] is number relate[1]is self station relate[2]is other station
	void addrelate(int a,int b,int c){
		int index = relate_max;
		relate[index][0]=a;
		relate[index][1]=b;
		relate[index][2]=c;
		relate_max++;
	}
};
class Visit{
public:
	bool s[102];
};
int Xindex(int);
void Findbestdistance(Visit,int ,int ,int ,int ,int ,int &);
line s[102];
int line_max = 0,relate_max = 0;
int main(){
	int tmp[6];
	Visit Visted;
	cin>>line_max>>relate_max;
	for(int i=0;i<line_max;i++){
		cin>>s[i].number>>s[i].station_max;
		for(int j=0;j<s[i].station_max;j++)
			cin>>s[i].station[j];
		s[i].relate_max = 0;
	}
	for(int i=0;i<relate_max;i++){
		for(int j=0;j<4;j++)
			cin>>tmp[j];
		int a = Xindex(tmp[0]);
		int b = Xindex(tmp[2]);
		s[a].addrelate(tmp[2],tmp[1],tmp[3]);
		s[b].addrelate(tmp[0],tmp[3],tmp[1]);
	}
	int hour[6],min[6],start_num[6],start_station[6],end_num[6],end_station[6];
	for(int i=0;i<5;i++){
		cin>>hour[i]>>min[i]>>start_num[i]>>start_station[i]>>end_num[i]>>end_station[i];
	}
	for(int i=0;i<5;i++){
		int sum=0,MIN=99999999;
		for(int x=0;x<line_max;x++)Visted.s[x]=false;
		Findbestdistance(Visted,start_num[i],start_station[i],end_num[i],end_station[i],sum,MIN);
		cout<<MIN<<endl;
	}
	system("pause");
	return 0;
}
int Xindex(int target){
	for(int i=0;i<line_max;i++)
		if(s[i].number==target)return i;
	return -1;
}
void Findbestdistance(Visit Visted,int current_line,int current_station,int target_line,int target_station,int sum,int &MIN){
	int index = Xindex(current_line);
	if(!Visted.s[index]){
		Visted.s[index]=true;
		if(current_line==target_line){
			if(current_line==target_line){
				//cout<<current_line<<" "<<current_station<<" "<<target_line<<" "<<target_station<<endl;
				if(current_station==target_station){
					if(sum<MIN)MIN=sum;
				}
				else if(current_station<target_station){
					for(int i=current_station;i<target_station;i++){
						sum+=(1+s[index].station[i]);
					}
					if(sum<MIN)MIN=sum;
				}
				else if(current_station>target_station){
					for(int i=current_station;i>target_station;i--){
						sum+=(1+s[index].station[i-1]);
					}
					if(sum<MIN)MIN=sum;
				}
				//cout<<"total="<<sum<<endl;
			}
		}
		else {
			int tmp = sum;
			for(int i=0;i<s[index].relate_max;i++){
				int target = s[index].relate[i][1];
				if(current_station<target){
					for(int j=current_station;j<target;j++){
						sum+=(1+s[index].station[j]);
						//cout<<sum<<endl;
					}
				}
				else if(current_station>target){
					for(int j=current_station;j>target;j--){
						sum+=(1+s[index].station[j-1]);
						//cout<<sum<<endl;
					}
				}
				int next = Xindex(s[index].relate[i][0]);
				//cout<<current_line<<" -> "<<s[index].relate[i][0]<<endl;
				Findbestdistance(Visted,s[index].relate[i][0],s[index].relate[i][2], target_line, target_station, sum,MIN);
				sum = tmp;
			}
		}
	}
}
