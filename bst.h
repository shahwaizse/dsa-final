class bst{
	public:
		int id;
		bst* left;
		bst* right;
		bool check;
		bst(){
			id = 0;
			left = 0;
			right = 0;
			check = 0;
		}
		bst(int e){
			id = e;
			left = 0;
			right = 0;
			check = 0;
		}
		bst* insert(bst* root, int e){
			if(root == 0){
				return new bst(e);
			}
			if(e > root->id){
				root->right = insert(root->right, e);
			}
			else{
				root->left = insert(root->left, e);
			}
			return root;
		}
		void find(bst* root, int e){
			if(root == 0){
				return;
			}
			find(root->left, e);
			if(root->id == e){
				check = 1;
			}
			find(root->right, e);
		}
		int search(bst* root, int e){
			find(root, e);
			if(check == 1){
				check = 0; //resetting the check value is necessary, otherwise the next time it's called it will still be 1.
				return 1;
			}
			return 0;
		}
		bst* minleaf(bst* root){
			bst* temp = root;
			while(temp && temp->left != 0){
				temp = temp->left;
			}
			return temp;
		}
		bst* remove(bst* root, int e){
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
					bst* temp = root->right;
					delete root;
					return temp;
				}
				else if(root->left == 0){
					bst* temp = root->left;
					delete root;
					return temp;
				}
				bst* temp = minleaf(root->right);
				root->id = temp->id;
				root->right = remove(root->right, temp->id);
			}
			return root;
		}
	};