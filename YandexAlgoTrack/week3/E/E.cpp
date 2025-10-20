#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <fstream>

struct node {
	node* left_child;
	node* right_sibling;
	int value;

	node(int value) : left_child(nullptr), right_sibling(nullptr), value(value) {}
};

void add_children(node* parent, std::vector<node*> children) {
    if (children.empty()) return;
    
    parent->left_child = children[0];
    for (size_t i = 1; i < children.size(); ++i) {
        children[i-1]->right_sibling = children[i];
    }
}

void delete_tree(node* root) {
    if (!root) return;

    node* child = root->left_child;
    while (child) {
        node* next = child->right_sibling;
        delete_tree(child);
        child = next;
    }

    delete root;
}

long long minedict(node* root) {
	long long count = 0;
	if(root->left_child) {
		root->value -= root->left_child->value;
		count += minedict(root->left_child);
		node* next = root->left_child->right_sibling;
		while(next) {
			root->value -= next->value;
			count += minedict(next);
			next = next->right_sibling;
		}
	}
	return abs(root->value) + count;
}

void test1() {
	node* root = new node(2);
	node* v1 = new node(1);
	node* v2 = new node(3);
	add_children(root, {v1, v2});
	long long res = minedict(root);
	long long answ = 6;
	assert(res == answ);
	delete_tree(root);
	std::cout << "OK!\n";
}

void test2() {
	node* root = new node(2);
	node* v1 = new node(1);
	node* v2 = new node(-1);
	node* v3 = new node(-1);
	node* v4 = new node(1);
	node* v5 = new node(-2);
	node* v6 = new node(1);
	add_children(root, {v1, v2});
	add_children(v1, {v3, v4});
	add_children(v4, {v5, v6});
	long long res = minedict(root);
	long long answ = 10;
	assert(res == answ);
	delete_tree(root);
	std::cout << "OK!\n";
}

void test3() {
	node* root = new node(5);
	node* v1 = new node(3);
	node* v2 = new node(2);
	add_children(root, {v1});
	add_children(v1, {v2});
	long long res = minedict(root);
	long long answ = 5;
	assert(res == answ);
	delete_tree(root);
	std::cout << "OK!\n";
}

void test4() {
	node* root = new node(-58696);
	node* v1 = new node(-84845);
	node* v2 = new node(4890);
	node* v3 = new node(-80991);
	node* v4 = new node(-6177);
	node* v5 = new node(-71108);
	node* v6 = new node(-36794);
	node* v7 = new node(81952);
	node* v8 = new node(28859);
	node* v9 = new node(-42781);
	add_children(root, {v1, v2, v3, v5, v7, v9});
	add_children(v1, {v4, v6});
	add_children(v3, {v8});
	long long res = minedict(root);
	long long answ = 558472;
	assert(res == answ);
	delete_tree(root);
	std::cout << "OK!\n";
}

void test5() {
	node* root = new node(0);
	std::vector<node*> nodes(999, new node(0));
	add_children(root, nodes);
	long long res = minedict(root);
	long long answ = 0;
	assert(res == answ);
	delete_tree(root);
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2();
	test3();
	test4();
	test5();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
    int n;
    std::cin >> n;
    std::vector<node*> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = new node(0);
    }
    std::vector<std::vector<int>> children(n);
    for (int i = 1; i < n; ++i) {
        int parent;
        std::cin >> parent;
        children[parent].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> nodes[i]->value;
    }
    for (int i = 0; i < n; ++i) {
        std::vector<node*> child_nodes;
        for (int idx : children[i]) {
            child_nodes.push_back(nodes[idx]);
        }
        add_children(nodes[i], child_nodes);
    }

    node* root = nodes[0];
    long long result = minedict(root);
    std::cout << result;
    delete_tree(root);
    return 0;
}
