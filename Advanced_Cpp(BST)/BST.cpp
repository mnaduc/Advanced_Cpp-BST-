#include "BST.h"

#include <iostream>


Node::Node(Car* car)
{
	data = car;
	left = NULL;
	right = NULL;
}

Node* BST::Insert(Car* car, Node* node)
{
	if (car->getPersonalKey() < node->data->getPersonalKey())
	{
		if (node->left != NULL)
			return Insert(car, node->left);
		else
		{
			node->left = new Node(car);
			return node->left;
		}
	}
	else
	{
		if (node->right != NULL)
			return Insert(car, node->right);
		else
		{
			node->right = new Node(car);
			return node->right;
		}
	}
}

Node* BST::searchByKey(string key, Node* node)
{
	if (node != NULL)
	{
		if (key == node->data->getPersonalKey())
			return node;
		if (key < node->data->getPersonalKey())
			return searchByKey(key, node->left);
		else
			return searchByKey(key, node->right);
	}
	else
		return NULL;
}

void BST::searchByName(string name, Node* node, vector<Car*>& v)
{
	if (node != NULL)
	{
		searchByName(name, node->left, v);
		if (name == node->data->getOwnerName())
			v.push_back(node->data) ;
		searchByName(name, node->right, v);
	}
}

void BST::writeDataToFile(ofstream& file, Node* node)
{
	if (node != NULL)
	{
		if (node != root_)
			file << endl;
		Car* car = node->data;
		file << "Common: "
			<< car->getPersonalKey() << ","
			<< car->getOwnerName() << ","
			<< car->getEmail() << ","
			<< car->getODO() << ","
			<< car->getRemindService() << "; ";
		Display* display = car->getDisplay();
		file << "Display: "
			<< display->get_light_level() << ","
			<< display->get_screen_light_level() << ","
			<< display->get_taplo_light_level() << "; ";
		Sound* sound = car->getSound();
		file << "Sound: "
			<< sound->get_media_level() << ","
			<< sound->get_call_level() << ","
			<< sound->get_navi_level() << ","
			<< sound->get_notification_level() << "; ";
		General* general = car->getGeneral();
		file << "General: "
			<< general->get_timezone() << ","
			<< general->get_language();
		writeDataToFile(file, node->left);
		writeDataToFile(file, node->right);
	}
}

void BST::inOrder(Node* node)
{
	if (node != NULL)
	{
		inOrder(node->left);
		std::cout << "***************************************************************************************************" << std::endl;
		node->data->info();
		inOrder(node->right);
	}
}

BST::BST()
{
	root_ = NULL;
}

Node* BST::Insert(Car* car)
{
	if (root_ != NULL)
		return Insert(car, root_);
	else
	{
		root_ = new Node(car);
		return root_;
	}
}

Node* BST::searchByKey(string key)
{
	return searchByKey(key, root_);
}

vector<Car*> BST::searchByName(string name)
{
	vector<Car*> res;
	searchByName(name, root_, res);
	return res;
}

void BST::writeDataToFile(string file_path)
{
	// Mở file xóa toàn bộ data và ghi lại
	// Nếu file không tồn tại thì tạo file mới
	ofstream file;
	file.exceptions(ofstream::failbit | ofstream::badbit);
	try
	{
		file.open(file_path, ios::out | ios::trunc);
		writeDataToFile(file, root_);
	}
	catch (const ofstream::failure& e)
	{
		cout << "--> Failed to write data to the file - " << e.what() << endl;
		system("pause");
	}
	catch (...)
	{
		cout << "--> Failed to write data to the file" << endl;
		system("pause");
	}
}

void BST::readDataFromFile(string file_path)
{
	ifstream file;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		file.open(file_path);
		string temp = "";
		while (!file.eof())
		{
			getline(file, temp, ' ');
			if (temp == "Common:")
			{
				// Personal key
				getline(file, temp, ',');
				Node* node = Insert(new Car(temp));
				// Owner name
				getline(file, temp, ',');
				node->data->setOwnerName(temp);
				// Email
				getline(file, temp, ',');
				node->data->setEmail(temp);
				// ODO
				getline(file, temp, ',');
				node->data->setODO(temp);
				// Remind service
				getline(file, temp, ';');
				node->data->setRemindService(temp);

				// DISPLAY
				Display* display = node->data->getDisplay();
				file.seekg(10, ios::cur);
				getline(file, temp, ',');
				display->set_light_level(stoi(temp));
				getline(file, temp, ',');
				display->set_screen_light_level(stoi(temp));
				getline(file, temp, ';');
				display->set_taplo_light_level(stoi(temp));

				//SOUND
				Sound* sound = node->data->getSound();
				file.seekg(8, ios::cur);
				getline(file, temp, ',');
				sound->set_media_level(stoi(temp));
				getline(file, temp, ',');
				sound->set_call_level(stoi(temp));
				getline(file, temp, ',');
				sound->set_navi_level(stoi(temp));
				getline(file, temp, ';');
				sound->set_notification_level(stoi(temp));

				//GENERAL
				General* general = node->data->getGeneral();
				file.seekg(10, ios::cur);
				getline(file, temp, ',');
				general->set_timezone(temp);
				getline(file, temp);
				general->set_language(temp);
			}
		}
	}
	catch (const ifstream::failure& e)
	{
		cout << "--> Failed to read data from the file - " << e.what() << endl;
		system("pause");
	}
	catch (...)
	{
		cout << "--> Failed to read data from the file" << endl;
		system("pause");
	}
}

void BST::inOrder()
{
	inOrder(root_);
}
