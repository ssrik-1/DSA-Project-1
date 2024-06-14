#include <iostream>
#include <queue>
#include <vector>
#include "AVLTree.h"
using namespace std;

//Used geeksforgeeks https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/#preorder-traversal
//https://www.geeksforgeeks.org/deletion-in-an-avl-tree/

//Function for height of the tree
int AVLTree::height (Node* N) {
    if (N == NULL)
        return 0;
    return N -> height;
}

//Function for a right rotation
Node* AVLTree::rotateRight(Node *node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    leftChild->height = std::max(height(leftChild->left), height(leftChild->right)) + 1;

    return leftChild; 
}

//Function for a left rotation
Node* AVLTree::rotateLeft(Node *node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    rightChild->height = std::max(height(rightChild->left), height(rightChild->right)) + 1;

    return rightChild; 
}

//^^rotation code (without updating height) was taken from stepik problem part 2
//Function to get balance factor
int AVLTree::getNewBalance(Node* N)
{
    if (N == NULL)
        return 0;
    return height (N->left) - height(N->right);
}

//Function to find minimum value node
Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}


//Function to insert a node (outline was provided in Project 1 video)
void AVLTree::insert(std::string name, std::string ufid) {
    root = insertHelper(root, name, ufid); 
}


//insertHelper function was provided in the template to aid in insertion of node
Node* AVLTree::insertHelper(Node* node, std::string name, std::string ufid)
{
    if(node == nullptr) {
        return new Node(name, ufid);
    } else if (ufid < node->ufid) {
        node->left = insertHelper(node->left, name, ufid);
    } else if (ufid > node->ufid) {
        node->right = insertHelper(root->right, name, ufid);
    } else {
        return node;
    }
//^^ taken from Module 5, Video 4 on AVL:insert 
    
    //Update height for ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));
 
 //^^ taken from Module 5, Video 4 on AVL:insert 


    //Get the balance factor of this ancestor node
    int balance = getNewBalance(node);

    //4 cases if node becomes unbalanced
    
    //Left Left Case
    if (balance > 1 && ufid < node->left->ufid) {
        return rotateRight(node);
    }

    //Right Right Case
    if (balance < -1 && ufid > node->right->ufid) {
        return rotateLeft(node);
    }

    //Left Right Case
    if (balance > 1 && ufid > node->left->ufid) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //Right Left Case
    if (balance < -1 && ufid < node->right->ufid) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}


//Function to remove a node
void AVLTree::removeID(std::string ufid) {
    if(searchHelper(root, ufid) == nullptr) {
        std::cout <<"unsuccessful" << std::endl;
    } else {
        Node* node = removeHelper(node, ufid);
        std::cout <<"successful" << std::endl;
    }
}


//removeHelper function to aid in deletion of node
Node* AVLTree::removeHelper(Node* node, std::string ufid)
{
    int temp;
    if(node == nullptr) {
        return node;
    } else if (ufid < node->ufid) {
        node->left = removeHelper(node->left, ufid);
    } else if (ufid > node->ufid) {
        node->right = removeHelper(root->right, ufid);
    } else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            Node* temp = node->left ?
                         root->left :
                         root->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;

            } else {
                *node = *temp;
                free(temp);
            }
        } else {
            Node* temp = minValueNode(root->right);
            node->ufid = temp->ufid;
            node->name = temp->name;
            node->right = removeHelper(node->right, temp->ufid);
        }
    }
     

    //Update height for ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));
 
 //^^ taken from Module 5, Video 4 on AVL:insert 


    //Get the balance factor of this ancestor node
    int balance = getNewBalance(node);

    //4 cases if node becomes unbalanced
    
    //Left Left Case
    if (balance > 1 && ufid < node->left->ufid) {
        return rotateRight(node);
    }

    //Right Right Case
    if (balance < -1 && ufid > node->right->ufid) {
        return rotateLeft(node);
    }

    //Left Right Case
    if (balance > 1 && ufid > node->left->ufid) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //Right Left Case
    if (balance < -1 && ufid < node->right->ufid) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;

}

//Function to search for ID
Node* AVLTree::searchIDHelper(Node* node, std::string ufid, bool& found) {

    if (node == nullptr){
       return node; 
    }

    if (node->ufid == ufid) {
        found = true;
        cout << node -> name << endl;
        return node;
    } else if (node->ufid > ufid) {
        return searchIDHelper (node->left, ufid, found);
    } else {
        return searchIDHelper (node->right, ufid, found);
    }
    return node;
}


//Printing search outcomes
void AVLTree::searchID(std::string ufid) {
    bool found = false;
    Node* outcome = searchIDHelper(outcome, ufid, found); 
    if(!found){
        std::cout << "unsuccessful" << std::endl;
    }
}


//Function to search for Name
Node* AVLTree::searchNameHelper(Node* node, std::string name, bool& found) {
    if (node == nullptr){
       return node; 
    } 
    if(node->name == name) {
        found = true;
        cout << node->ufid << endl;
    }
    searchNameHelper(node->left, name, found);
    searchNameHelper(node->right, name, found);
    return node;
}


void AVLTree::searchName(std::string ufid) {
    bool found = false;
    Node* outcome = searchNameHelper(outcome, ufid, found); 
    if(!found){
        std::cout << "unsuccessful" << std::endl;
    }
}



//Function for searching in order to delete
Node* AVLTree::searchHelper(Node* node, std::string ufid) {
    bool found = false;
    return searchIDHelper(node, ufid, found); 
}


//Function to print preorder transversal (logic is also based on lecture)
void AVLTree::printPreorderHelper(Node *node) {
    if (node != nullptr) {
        std::cout << node->name << ",";
        printPostorderHelper(node->left);
        printPostorderHelper(node->right);
    }
}


void AVLTree::printPreorder() {
    printPreorderHelper(root);
    std::cout << std::endl;
}


//Function to print inorder transversal (logic is also based on lecture) (Include Transversal too)
void AVLTree::inorderHelper(Node *node, std::vector<Node*> & nodes) {
    if (node != nullptr) {
        inorderHelper(node->left, nodes);
        nodes.push_back(node);
        inorderHelper(node->right, nodes);
    }
}


void AVLTree::printInorderHelper(Node *node) {
    if (node != nullptr) {
        printInorderHelper(node->left);
        std::cout <<node->name << ",";
        printInorderHelper(node->right);
    }
    
}


void AVLTree::printInorder() {
    printInorderHelper(root);
    std::cout << std::endl;
}


//Function to print postorder transversal (logic is also based on lecture)
void AVLTree::printPostorderHelper(Node *node) {
    if (node != nullptr) {
        printPostorderHelper(node->left);
        printPostorderHelper(node->right);
        std::cout << node->name << ",";
    }
}


void AVLTree::printPostorder() {
    printPostorderHelper(root);
    std::cout << std::endl;
}


//Function to print number of levels that exist in the tree
int AVLTree::printLevelCountHelper(Node *node) {
    if (node == NULL) {
        return 0; 
    }

    std::queue<Node*> q;
    q.push(node);
    int levelCount = 0;


    while(!q.empty()) {
        int nodeCount = q.size();

        while(nodeCount > 0) {
            Node* current = q.front();
            q.pop();

            if(current->left != nullptr) {
                q.push(current->left);
            } 
            if(current->right != nullptr) {
                q.push(current->right);
            } 

            nodeCount--;
        }
        levelCount++;
    }
    return levelCount;

} 


//Function to print levels
int AVLTree::printLevelCount() {
    return printLevelCountHelper(root);
}


//Functions to remove the nth node
int AVLTree::removeInorder(int result) {
    std::vector<Node*> nodes;
    inorderHelper(root, nodes);
    int n = result;

    if (n >= 0 && n < nodes.size()) {
        root = removeHelper(root, nodes[n]->ufid);
        std::cout <<"successful" <<std::endl;
    } else {
        std::cout <<"unsuccessful" <<std::endl;
    }
    return 0;
}

//Clear Tree
void AVLTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
    root = nullptr;
}
