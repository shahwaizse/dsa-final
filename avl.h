class avl{
	public:
		int id;
		avl* left;
		avl* right;
		int height;
		bool check;
		avl(){
			id = 0;
			left = 0;
			right = 0;
			check = 0;
			height = 0;
		}
		avl(int e){
			id = e;
			left = 0;
			right = 0;
			check = 0;
			height = 1;
		}
		int nodeheight(avl* root){
			if(root == 0){
				return 0;
			}
			return root->height;
		}
		int largest(int a, int b){
			if(a > b){
				return a;
			}
			return b;
		}
		avl* rotateright(avl* root){
			avl* x = root->left;
			avl* t2 = x->right;
			x->right = root;
			root->left = t2;
			root->height = largest(nodeheight(root->left), nodeheight(root->right) + 1);
			x->height = largest(nodeheight(x->left), nodeheight(x->right) + 1);
			return x;
		}
		avl* rotateleft(avl* root){
			avl* y = root->right;
			avl* t2 = y->left;
			y->left = root;
			root->right = t2;
			root->height = largest(nodeheight(root->left), nodeheight(root->right) + 1);
			y->height = largest(nodeheight(y->left), nodeheight(y->right) + 1);
			return y;
		}
		int getbalance(avl* root){
			if(root == 0){
				return 0;
			}
			return nodeheight(root->left) - nodeheight(root->right);
		} 
		avl* insert(avl* root, int e){
			if(root == 0){
				return new avl(e);
			}
			if(e > root->id){
				root->right = insert(root->right, e);
			}
			else if(e < root->id){
				root->left = insert(root->left, e);
			}
			return root;

			root->height = 1 + largest(nodeheight(root->left), nodeheight(root->right));
			int balance = getbalance(root);

			if (balance > 1 && id < root->left->id){
        		return rotateright(root);
			}

    		if (balance < -1 && id > root->right->id){
        		return rotateleft(root);
    		}
 
    		if (balance > 1 && id > root->left->id){
        		root->left = rotateleft(root->left);
        		return rotateright(root);
    		}
 
    		if (balance < -1 && id < root->right->id){
        		root->right = rotateright(root->right);
        		return rotateleft(root);
    		}
		}
		void find(avl* root, int e){
			if(root == 0){
				return;
			}
			find(root->left, e);
			if(root->id == e){
				check = 1;
			}
			find(root->right, e);
		}
		int search(avl* root, int e){
			find(root, e);
			if(check == 1){
				check = 0; //resetting the check value is necessary, otherwise the next time it's called it will still be 1.
				return 1;
			}
			return 0;
		}
		avl* minleaf(avl* root){
			avl* temp = root;
			while(temp && temp->left != 0){
				temp = temp->left;
			}
			return temp;
		}
		avl* remove(avl* root, int e){
			if(root == 0){
				return root;
			}
			if(e > root->id){
				root->right = remove(root->right, e);
			}
			else if(e < root->id){
				root->left = remove(root->left, e);
			}
			else{
				if(root->left == 0 && root->right == 0){
					return 0;
				}
				else if(root->left == 0){
					avl* temp = root->right;
					delete root;
					return temp;
				}
				else if(root->left == 0){
					avl* temp = root->left;
					delete root;
					return temp;
				}
				avl* temp = minleaf(root->right);
				root->id = temp->id;
				root->right = remove(root->right, temp->id);
			}
			return root;
		}
	};