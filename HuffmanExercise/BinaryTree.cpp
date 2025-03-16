#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include <iostream>

BinaryTree<int>::BinaryTree() : root(0) {
}

BinaryTree<int>::BinaryTree(std::vector<Node<int>> freqs) : root(0) {
	h = new BinaryHeap(freqs);
	//make heap for all starting nodes
	while (h.getSize() != 1) {
		Node<int>* first = new Node<int>(h.getMin());
		h.deleteMin();
		Node<int>* second = h.getMin();
		h.deleteMin();
		Node<int> parent(first->freq + second->freq);
		h.insert(parent);
	}
	root = h.getMin();
}

BinaryTree<int>::~BinaryTree() {
	Node<int>* curr = root;
	while (curr != nullptr) {
		while (curr->left || curr->right) {
			if (curr->left) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		Node<int>* del = curr;
		curr = curr->p;
		delete del;
	}
}

void BinaryTree<int>::inorder_print() {
	std::vector<int> res;
	Node<int>* curr = root;
	while (curr != nullptr) {
		if (curr->left == nullptr) {
			res.push_back(curr->freq);
			curr = curr->right;
		}
		else {
			Node<int>* prev = curr->left;
			while (prev->right != nullptr &&
				prev->right != curr) {
				prev = prev->right;
			}
			if (prev->right == nullptr) {
				prev->right = curr;
				curr = curr->left;
			}
			else {
				prev->right = nullptr;
				res.push_back(curr->freq);
				curr = curr->right;
			}
		}
	}
	for (int i : res) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

void BinaryTree<int>::load(const std::ifstream& in) {

}

void BinaryTree<int>::save(const std::ofstream& out) {

}