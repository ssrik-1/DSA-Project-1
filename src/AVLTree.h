#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

struct Node {

	std::string name;
	std::string ufid;
	Node *left;
	Node *right;
	int height;

	Node(std::string name, std::string ufid) {
		this->name = name;
		this->ufid = ufid;
		this->left = nullptr;
		this->right = nullptr;
		this->height = 1;
	}
};

class AVLTree {

	private:
    int max();
	Node* root;
    int height(Node* N);
    int getNewBalance(Node* N);
    Node* balance(Node* node); 
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);  
    Node* minValueNode(Node* node);
    Node* removeHelper(Node* node, std::string ufid);
    Node* searchHelper(Node* node, std::string ufid);
    Node* searchIDHelper(Node* node, std::string ufid, bool& found);
    Node* searchNameHelper(Node* node, std::string name, bool& found);
    Node* removeIDHelper(Node* node, std::string ufid, bool& found);
    void printInorderHelper(Node *node);
    void printPreorderHelper(Node *node);
    void printPostorderHelper(Node *node);
    int printLevelCountHelper(Node *node);
    Node* insertHelper(Node* node, std::string name, std::string ufid);
    void inorderHelper(Node *node, std::vector<Node*> & nodes);
    
    
	public:
	void insert(std::string name, std::string ufid);
    void printInorder(); 
    void printPreorder(); 
    void printPostorder(); 
    int printLevelCount();
    int removeInorder(int result);
    Node* inorder2(int index);
    void removeID(std::string ufid);
    void searchID(std::string ufid);
    void searchName(std::string name); 
    void clear(Node *node);
    Node *getRoot() {
        return root;
    }

	AVLTree() : root(nullptr) {}
    ~AVLTree() {
        clear(root);
    }
};

#endif