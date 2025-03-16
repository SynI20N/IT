#include <fstream>
#include <vector>

template <typename T>
struct Node {
	int freq;
	char sym;
	Node* left;
	Node* right;
	Node* p;

	Node(int f) : freq(f), left(0), right(0), p(0) {}
};

template <typename T>
class BinaryTree {
private:
	Node<T>* root;
	BinaryHeap h;
public:
	BinaryTree();
	BinaryTree(std::vector<Node<int>> freqs);
	~BinaryTree();
	void inorder_print();
	void save(const std::ofstream& out);
	void load(const std::ifstream& in);
};