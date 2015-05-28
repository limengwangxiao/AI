#ifndef _NODE_H__
#define _NODE_H__
#include <vector>
using namespace std;

class node{
	

public :
	int h_n;
	int g_n;

	vector<node> child; 
	int space;
	vector <int> v;


public:

	node(vector<int> v_) {
		v.resize(9);
		for(int i=0;i<v_.size();i++){
			v[i] = v_[i];
		}
	}
	node() {

		v.resize(9);
	}

	void fz(node n){

		for(int i=0;i<9;i++){
			this->v[i] = n.v[i];
		}
		this->space=n.space;
	}
	int getVal(int i,int j);
	bool operator==(node &n){

		if(v==n.v){

			return true;
		}

		return false;
	}

	bool operator < (node & n){

		if(h_n < n.h_n){
			return 1;
		}else{
			return 0;
		}
	}

	void set_h_n(node& target){
		int sum = 0;
		for(int i=0;i<9;i++){
			if(target.v[i]!=0&&v[i]==target.v[i]){
				sum ++;
			}
		}

		h_n = 8 - sum;
	}

};

#endif
