#include "node.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include "ger.h"
#include <time.h>
using namespace std;

vector<node> close_bfs;
vector <node> close_dfs;
vector<node> close_ax;
vector<vector<int> > is2move;
queue<node> q_ax;

int num = 0;
void move_ax(queue<node> qu, node &target){
	vector<node> v_;
	while(!qu.empty()){
		node n = qu.front();
		qu.pop();
		close_ax.push_back(n);
		cout << "(" << n.space /3 << "," << n.space %3 << ")" << endl;
		if(n==target){
			 cout << "get One" << endl;
			 return;
		}
		int i = n.space / 3;
		int j = n.space % 3;

		vector<int> te;
		if(i-1>=0){
			te.push_back((i-1)*3+j);
		}if(i+1<=2){
			te.push_back((i+1)*3+j);
		}if(j-1>=0){
			te.push_back((i)*3+j-1);   
		}if(j+1<=2){
			te.push_back((i)*3+j+1);
		}

		for(int i=0;i<te.size();i++){

			int h = te[i] / 3;
			int w = te[i] % 3;
			node n_(n.v);
			n_.v.at(n.space) = n.v.at(te[i]);
			n_.v.at(te[i]) = 0;
			n_.space = te[i];
			n_.set_h_n(target);
			n_.g_n = n.g_n + 1;

			int j;
			for(j=0;j<close_ax.size();j++){
				if(close_ax[j]==n_){
					break;
				}
			}
			if(j==close_ax.size()){
				v_.push_back(n_);
			}
		}
	}

	sort(v_.begin(),v_.end());

	queue<node> qu_;
	if(v_.size()>1){
		qu_.push(v_[0]);
		for(int i=1;i<v_.size();i++){

			if(v_[i].h_n==v_[i-1].h_n){
				qu_.push(v_[i]);
			}else{
				break;
			}
		}
	}else if(v_.size()==1){
		qu_.push(v_[0]);
	}

	move_ax(qu_, target);
} 

void move_bfs(node &n,node& target){


	queue<node> q;

	q.push(n);


	while(!q.empty()){

		node no = q.front();
		q.pop();
		close_bfs.push_back(no);
		if(no==target){
			cout << "(" <<no.space/3 << "," << no.space%3 << ")-->" << endl;
			cout << "get One" << endl;
			return;
		}
		cout << "(" <<no.space/3 << "," << no.space%3 << ")-->" << endl;


		int i = no.space / 3;
		int j = no.space % 3;

		vector<int> te;

		if(i-1>=0){
			te.push_back((i-1)*3+j);
		}if(i+1<=2){
			te.push_back((i+1)*3+j);
		}if(j-1>=0){
			te.push_back((i)*3+j-1);
		}if(j+1<=2){
			te.push_back((i)*3+j+1);
		}

		for(int i=0;i<te.size();i++){

			int h = te[i] / 3;
			int w = te[i] % 3;
			node n_(no.v);
			n_.v.at(no.space) = no.v.at(te[i]);
			n_.v.at(te[i]) = 0;
			n_.space = te[i];
			n_.set_h_n(target);
			n_.g_n = no.g_n + 1;

			int j;
			for(j=0;j<close_bfs.size();j++){
				if(close_bfs[j]==n_){
					break;
				}
			}
			if(j==close_bfs.size()){
				q.push(n_);
			}	
		}
	}

}


int isgetOne = 0;
void move_dfs(node& n,node & target){

	if(isgetOne==1){

		return ;
	}
	close_dfs.push_back(n);
	if(n.g_n>5){
		return;
	}
	if(n.h_n==0){
		isgetOne = 1;
		cout <<"get One-----------------------------------------------" << endl;
		return;
	}

	int i = n.space / 3;
	int j = n.space % 3;

	vector<int> te;

	if(i-1>=0){
		te.push_back((i-1)*3+j);
	}if(i+1<=2){
		te.push_back((i+1)*3+j);
	}if(j-1>=0){
		te.push_back((i)*3+j-1);
	}if(j+1<=2){
		te.push_back((i)*3+j+1);
	}

	for(int i=0;i<te.size();i++){

		int h = te[i] / 3;
		int w = te[i] % 3;
		node n_(n.v);
		n_.v.at(n.space) = n.v.at(te[i]);
		n_.v.at(te[i]) = 0;
		n_.space = te[i];
		n_.set_h_n(target);
		n_.g_n = n.g_n + 1;

		int j;
		for(j=0;j<close_dfs.size();j++){
			if(close_dfs[j]==n_){
				break;
			}
		}
		if(j==close_dfs.size()){
			n.child.push_back(n_);
			cout << "(" <<n.space/3 << "," << n.space%3 << ")-->" <<   endl;
			move_dfs(n_,target);
		}	
	}
}

vector<Ger> a_ger;
vector<Ger> a_ger_;
void cal_bit(){

	float sum=0;
	for(int i=0;i<4;i++){
		sum += (10-a_ger[i].cur.h_n);
	}

	for(int i=0;i<4;i++){
		a_ger[i].bit = (float(10-a_ger[i].cur.h_n)) / sum;
	}
}

int rand_d(int f, int t){
	int range = t - f + 1;   //5-1+1=5
	return rand()%range+f; //rand()%5+1;
}
float rand_f(float f, float t){

	//srand( (unsigned)time( NULL ) ); 
	float num = (rand()%100)*0.01;
	return num;
}

int wheelSelect(){
	float cur_bit = rand_f(0,1);

	int i;
	//	cout << cur_bit << endl;
	float sum_bit = 0;
	for( i=0;i<4;i++){
		sum_bit += a_ger[i].bit;
		if(sum_bit < cur_bit){
			continue;
		}else{
			break;
		}
	}
	return i;
}

int main(){


	node from;
	node target;


	from.v[0] = 2;
	from.v[1] = 8;
	from.v[2] = 3;
	from.v[3] = 1;
	from.v[4] = 6;
	from.v[5] = 4;
	from.v[6] = 7;
	from.v[7] = 0;	
	from.v[8] = 5;
	from.space = 7;

	from.g_n = 0;

	target.v[0] = 1;
	target.v[1] = 2;
	target.v[2] = 3;
	target.v[3] = 8;
	target.v[4] = 0;
	target.v[5] = 4;
	target.v[6] = 7;
	target.v[7] = 6;
	target.v[8] = 5;

	target.space = 4;

	from.set_h_n(target);

	srand( (unsigned)time( NULL ) );
	for(int i=0;i<4;i++){
		Ger g;
		a_ger.push_back(g);
	}//初始化种群
	

	int x=1;
	while(x){
		x++;
		for(int i=0;i<4;i++){
			a_ger[i].Render(from); 
			a_ger[i].fitness(target);//计算适应度


			cout << a_ger[i].cur.h_n << endl;
			if(a_ger[i].cur.h_n==0){
				cout << "get one" << endl;
				a_ger[i].print();
				cout << endl << x << endl;
				x = 0; 
				break;
			}
		}


		cal_bit();
		//随机选取两个种群进行

		int i1[4];
		i1[0] = wheelSelect();
		i1[1] = wheelSelect();
		i1[2] = wheelSelect();
		i1[3] = wheelSelect();  //选择4个个体

		int x = rand_d(1,4);
		int x1=x;
		while(x1==x){
			x1 = rand_d(1,4);
		}
		Ger g1 = a_ger[i1[x-1]];
		Ger g2 = a_ger[i1[x1-1]];
		g1.Xwith(g2);
		vector<int> sx;
		for(int k=0;k<4;k++){
			if(k!=x-1&&k!=x1-1){
				sx.push_back(k);
			}
		} 
		Ger g3 = a_ger[i1[sx[0]]];
		Ger g4 = a_ger[i1[sx[1]]];

		a_ger.clear();
		g1.bianyi();
		a_ger.push_back(g1);
		a_ger.push_back(g2);
		a_ger.push_back(g3);
		a_ger.push_back(g4);


	}



	
//	vector<node> v;
//	v.push_back(from);
//	queue <node> qu;
//	qu.push(from);
////	move_dfs(from,target);
////	move_bfs(from,target);
//	move_ax(qu,target);
//
//	////cout << num << endl;


}