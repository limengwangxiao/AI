#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "node.h"
using namespace std;
class Ger{

public:
	vector<int> g;  //��������
	float bit;
	float fit;
	node cur;
	Ger(){
		for(int i=0;i<40;i++){
			g.push_back(rand()%2);
		} //�����ߵ�·��
	}
	int index; //�ڼ���
	void Render(node from){
		node t(from);
		for(int i=0;i<40;i+=2){
			if(g[i]==0&&g[i+1]==0){ //��

				int x = from.space / 3;
				int y = from.space % 3;

				if(x-1>=0){  //��������
					t.space = (x-1)*3 + y;
					t.v[t.space] = 0;
					t.v[from.space] = from.v[t.space];
				}
			}else if(g[i]==0&&g[i+1]==1){  //��
				int x = from.space / 3;
				int y = from.space % 3;

				if(x+1<=2){  //��������
					t.space = (x+1)*3 + y;
					t.v[t.space] = 0;
					t.v[from.space] = from.v[t.space];
				}
			}else if(g[i]==1&&g[i+1]==0){ //��
				int x = from.space / 3;
				int y = from.space % 3;

				if(y-1>=0){  //��������
					t.space = (x)*3 + y-1;
					t.v[t.space] = 0;
					t.v[from.space] = from.v[t.space];
				}
			}else if(g[i]==1&&g[i+1]==1){//��
				int x = from.space / 3;
				int y = from.space % 3;

				if(y+1<=2){  //��������
					t.space = (x)*3 + y+1;
					t.v[t.space] = 0;
					t.v[from.space] = from.v[t.space];
				}
			}
			from.fz(t);
		}

		cur.fz(from);
	}
	void fitness(node target){
		cur.set_h_n(target); //������Ӧ��
	}
	void Xwith(Ger & n){ //��n����
		int t = rand()%39+1;  //�����λ��
		for(int i=0;i<t;i++){
			swap(this->g[i], n.g[i]);
		}
	}
	void print(){
		for(int i=0;i<40;i++){
			cout << g[i] << "-";
		}
	}
	void bianyi(){
		int t = rand()%40+1;  //�����λ��	
		g[t-1] = !g[t-1];
	}
};
