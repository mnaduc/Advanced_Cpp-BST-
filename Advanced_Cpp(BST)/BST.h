#ifndef BST_H_
#define BST_H_

#include "Car.h"
#include <fstream>
#include <vector>
using namespace std;

/*
	struct quản lý một node trong tree
*/
struct Node
{
	Car* data;
	Node* left;
	Node* right;
	Node(Car* car);
};

/*
	Lớp quản lý binary search tree - Lưu trữ dữ liệu các xe
*/
class BST
{
private:
	Node* root_;
	Node* Insert(Car* car, Node* node);
	Node* searchByKey(string key, Node* node);
	void searchByName(string name, Node* node, vector<Car*>& v);
	void writeDataToFile(ofstream& file, Node* node);
	void inOrder(Node* node);
public:
	BST();
	Node* Insert(Car* car);
	Node* searchByKey(string key);
	vector<Car*> searchByName(string name);
	void writeDataToFile(string file_path);
	void readDataFromFile(string file_path);
	void inOrder();
};

#endif // !BST_H_



