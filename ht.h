#include"bst.h"
#include<string>
using namespace std;
class ht{
	public:
		bst* tree;
		int size;
		ht(int e){
			size = e;
			tree = new bst[size];
			for(int i=0; i<size; i++){
				tree[i] = 0;
			}
		}
		int hash(string fname){
			int hashval = 0;
			int factorial = 1;
			for(int i=0; i<fname.size(); i++){
				hashval += fname[i]*factorial;
				factorial++;
			}
			return hashval;
		}
		int look(string fname){
			if(tree[hash(fname)%size].search(&tree[hash(fname)%size], hash(fname)) == 1){
				return 1;
			}
			return 0;
		} 
		int add(string fname){
			if(tree[hash(fname)%size].search(&tree[hash(fname)%size], hash(fname)) == 1){
				return 0;
			}
			tree[hash(fname)%size].insert(&tree[hash(fname)%size], hash(fname));
			return 1;
		}
		int del(string fname){
			if(tree[hash(fname)%size].search(&tree[hash(fname)%size], hash(fname)) == 1){
				tree[hash(fname)%size].remove(&tree[hash(fname)%size], hash(fname));
				return 1;
			}
			return 0;
		}
};