#ifndef __bst_hpp_included__
#define __bst_hpp_included__

template <typename T>
class bst {
	struct node;

	node *root;
	
	private:
		node *insert (node *root, T value) {
			if (root == nullptr)
				return new node(value);

			if (root->data > value)
				root->left = insert(root->left, value);
			else if (root->data < value)
				root->right = insert(root->right, value);

			return root;
		}

		/*void printInOrder (node *root) {
			if (root == nullptr)
				return;

			printInOrder(root->left);
			cout << "[" << root->data << "] ";
			printInOrder(root->right);

			return;
		}*/

		T height (node *root) const {
			T l, r;

			if (root == nullptr)
				return 0;

			l = height(root->left);
			r = height(root->right);

			return l > r ? (l + 1):(r + 1);
		}

		bool search (node *root, T value) const {
			if (root == nullptr)
				return false;

			if (root->data == value)
				return true;

			if (root->data > value)
				return search(root->left, value);
			else
				return search(root->right, value);
		}

		node *findMin (node *root) const {
			if (root->left == nullptr)
				return root;
			else
				return findMin(root->left);
		}

		node *remove (node *root, int value) {
			if (root == nullptr)
				return nullptr;

			if (value < root->data) {
				root->left = remove(root->left, value);
			} else if (value > root->data) {
				root->right = remove(root->right, value);
			} else { //value == root->data
				if (root->left == nullptr) {
					node *temp = root->right;

					delete root;
					
					return temp;
				} else if (root->right == nullptr) {
					node *temp = root->left;

					delete root;
					
					return temp;
				} else {
					node *temp = findMin(root->right);
					root->data = temp->data;
					root->right = remove(root->right, temp->data);
				}
			}

			return root;
		}

		void deleteTree (node *root) {
			if (root == nullptr)
				return;

			deleteTree(root->left);
			deleteTree(root->right);

			if (root->left != nullptr)
				delete root->left;

			if (root->right != nullptr)
				delete root->right;
		}

	public:
		bst (): root(nullptr) {}

		~bst () {
			deleteTree(root);
		}

		/*void print () {
			printInOrder(root);
			cout << "\n";
		}*/

		inline T height () const {
			return height(root);
		}

		inline bool search (T value) const {
			return search(root, value);
		}

		inline void insert (T value) {
			root = insert(root, value);
		}

		inline void remove (T value) {
			root = remove(root, value);
		}
};

template <typename T>
struct bst<T>::node {
	T data;
	node *left;
	node *right;

	node (T value): data(value), left(nullptr), right(nullptr) {}

	node (T value, node *left, node *right): data(value), left(left), right(right) {}
};

#endif