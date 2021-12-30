#include <iostream>
#include <regex>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Car.h"
#include "BST.h"

// screen lưu id màn hình hiện thời
enum class Screen { kScreen1, kScreen2, kScreen3 };
Screen screen = Screen::kScreen1;
bool is_running = true;

BST btree;

void menu();
unsigned int inputSelection(unsigned int num_of_choices);
bool YNQuestion();
string inputPersonalKey();

void inputDisplay();
void inputSound();
void inputGeneral();
Car* inputDataCar();

void printDisplay();
void printSound();
void printGeneral();
void printAllSetting();


int main()
{
	General::downloadLanguage("languages.txt");
	General::downloadTimezone("timezones.txt");
	btree.readDataFromFile("Setting.txt");
	while (is_running) menu();
	system("cls");
	cout << "--- GOODBYE, SEE YOU LATER! ---" << endl;
	return 0;
}

/*
	Hiển thị menu và xử lý chuyển màn hình
*/
void menu()
{
	system("cls");
	switch (screen)
	{
	case Screen::kScreen1:
		cout << "--- SECLECT MENU ---\n";
		cout << "1. Input setting information\n";
		cout << "2. Print setting information\n";
		cout << "3. Exit\n";
		// Nhập lựa chọn
		switch (inputSelection(3))
		{
		case 1:
			screen = Screen::kScreen2;
			break;
		case 2:
			screen = Screen::kScreen3;
			break;
		case 3:
			is_running = false;
			break;
		}
		break;
	case Screen::kScreen2:
		cout << "--- SECLECT MENU ---\n";
		cout << "1. Display setting\n";
		cout << "2. Sound setting\n";
		cout << "3. General setting\n";
		cout << "4. Exit\n";
		// Nhập lựa chọn
		switch (inputSelection(4))
		{
		case 1:
			inputDisplay();
			break;
		case 2:
			inputSound();
			break;
		case 3:
			inputGeneral();
			break;
		case 4:
			screen = Screen::kScreen1;
			break;
		}
		break;
	case Screen::kScreen3:
		cout << "--- SECLECT MENU ---\n";
		cout << "1. Print Display setting information\n";
		cout << "2. Print Sound setting information\n";
		cout << "3. Print General setting information\n";
		cout << "4. Print all setting information\n";
		cout << "5. Exit\n";
		// Nhập lựa chọn
		switch (inputSelection(5))
		{
		case 1:
			system("cls");
			cout << "--- Display setting ---\n";
			printDisplay();
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "--- Sound setting ---" << endl;
			printSound();
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "--- General setting ---" << endl;
			printGeneral();
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "--- All setting ---" << endl;
			printAllSetting();
			system("pause");
			break;
		case 5:
			screen = Screen::kScreen1;
			break;
		}
		break;
	}
}

/*
	Yêu cầu nhập và kiểm tra lựa chọn menu
	@param num_of_choices số lượng các lựa chọn
	@return vị trí lựa chọn
*/
unsigned int inputSelection(unsigned int num_of_choices)
{
	string selection = "";
	while (true)
	{
		cout << "Your selection: ";
		getline(cin, selection);
		// Kiểm tra nhập hợp lệ
		if (regex_match(selection, regex("[1-" + to_string(num_of_choices) + "]")))
		{
			return stoi(selection);
		}
		else
			cout << "  * Invalid! ";
	}
}

/*
	Yêu cầu nhập và kiểm tra lựa chọn Y/N
	@return true nếu chọn yes (y/Y)
	@return false nếu chọn no (n/N)
*/
bool YNQuestion()
{
	string temp = "";
	while (true)
	{
		cout << "Your selection: ";
		getline(cin, temp);
		if (temp == "n" || temp == "N")
			return false;
		else if (temp == "y" || temp == "Y")
			return true;
		else
			cout << "  * Invalid! ";
	}
}

string inputPersonalKey()
{
	//Nhập và kiểm tra Key number
	string key_number = "";
	cout << "   Key number: ";
	getline(cin, key_number);
	while (!Car::checkPersonalKey(key_number))
	{
		cout << "     * Invalid! Key number: ";
		getline(cin, key_number);
	}
	return key_number;
}

void inputDisplay()
{
	while (true)
	{
		system("cls");
		cout << "--- Input Display setting ---" << endl;

		// Nhập thông tin của xe
		cout << "Data Car:" << endl;
		Car* car = inputDataCar();
		// Nhập cài đặt display
		cout << "Display setting:" << endl;
		car->getDisplay()->input();

		// Thông báo kết quả
		system("cls");
		cout << "--- Input Display setting ---" << endl;
		car->Setting::info();
		car->getDisplay()->info();
		//Cập nhật vào file
		btree.writeDataToFile("Setting.txt");

		cout << "Will you input for next car (y/n)?" << endl;
		if (YNQuestion() == false)
		{
			// Lựa chọn no chuyển về màn hình 1
			screen = Screen::kScreen1;
			return;
		}
	}
}

void inputSound()
{
	while (true)
	{
		system("cls");
		cout << "--- Input Sound setting ---" << endl;

		// Nhập thông tin xe
		cout << "Data Car:" << endl;
		Car* car = inputDataCar();
		// Nhập cài đặt Sound
		cout << "Sound setting:" << endl;
		car->getSound()->input();

		// Thông báo kết quả
		system("cls");
		cout << "--- Input Sound setting ---" << endl;
		car->Setting::info();
		car->getSound()->info();
		// Cập nhật vào file
		btree.writeDataToFile("Setting.txt");

		cout << "Will you input for next car (y/n)?" << endl;
		if (YNQuestion() == false)
		{
			// Lựa chọn no chuyển về màn hình 1
			screen = Screen::kScreen1;
			return;
		}
	}
}

void inputGeneral()
{
	while (true)
	{
		system("cls");
		cout << "--- Input General setting ---" << endl;

		// Nhập thông tin xe
		cout << "Data Car:" << endl;
		Car* car = inputDataCar();
		system("pause");
		// Nhập cài đặt General
		car->getGeneral()->input();

		// Thông báo kết quả
		system("cls");
		cout << "--- Input General setting ---" << endl;
		car->Setting::info();
		car->getGeneral()->info();
		// Cập nhật vào file
		btree.writeDataToFile("Setting.txt");

		cout << "Will you input for next car (y/n)?" << endl;
		if (YNQuestion() == false)
		{
			// Lựa chọn no chuyển về màn hình 1
			screen = Screen::kScreen1;
			return;
		}
	}
}

/*
	Nhập thông tin chung của xe
	@return Car* xe đã nhập
*/
Car* inputDataCar()
{
	string key_number = inputPersonalKey();
	// Tìm kiếm xe trong BST
	Node* res = btree.searchByKey(key_number);
	string msg = "";
	if (res != NULL)
	{
		msg = "--> This car has already existed, data will be overriten";
	}
	else
	{
		msg = "--> This is a new car, data will be appended to your list";
		res = btree.Insert(new Car(key_number));
	}
	// Nhập các thông tin khác
	// Cập nhật cho xe cũ hoặc nhập cho xe mới
	res->data->inputData();
	cout << msg << endl;
	return res->data;
}

void printDisplay()
{
	system("cls");
	cout << "--- Display setting ---" << endl;
	string key_number = inputPersonalKey();
	Node* node = btree.searchByKey(key_number);
	if (node != NULL)
	{
		system("cls");
		cout << "--- Display setting ---" << endl;
		cout << left;
		cout << setw(20) << "Owner name"
			<< setw(25) << "Email"
			<< setw(15) << "Key"
			<< setw(10) << "ODO"
			<< setw(15) << "Service(km)"
			<< setw(10) << "Light"
			<< setw(10) << "Screen"
			<< setw(10) << "Taplo" << endl;
		node->data->infoDisplay();
	}
	else
	{
		cout << "   --> This car does not exist!" << endl;
	}
}

void printSound()
{
	system("cls");
	cout << "--- Sound setting ---" << endl;
	string key_number = inputPersonalKey();
	Node* node = btree.searchByKey(key_number);
	if (node != NULL)
	{
		system("cls");
		cout << "--- Sound setting ---" << endl;
		cout << left;
		cout << setw(20) << "Owner name"
			<< setw(25) << "Email"
			<< setw(15) << "Key"
			<< setw(10) << "ODO"
			<< setw(15) << "Service(km)"
			<< setw(10) << "Media"
			<< setw(10) << "Call"
			<< setw(10) << "Navi"
			<< setw(10) << "Notify" << endl;
		node->data->infoSound();
	}
	else
	{
		cout << "   --> This car does not exist!" << endl;
	}
}

void printGeneral()
{
	system("cls");
	cout << "--- General setting ---" << endl;
	string key_number = inputPersonalKey();
	Node* node = btree.searchByKey(key_number);
	if (node != NULL)
	{
		system("cls");
		cout << "--- General setting ---" << endl;
		cout << left;
		cout << setw(20) << "OWNER NAME"
			<< setw(25) << "Email"
			<< setw(15) << "Key"
			<< setw(10) << "ODO"
			<< setw(15) << "Service(km)"
			<< setw(20) << "TimeZone"
			<< setw(20) << "Language" << endl;
		node->data->infoGeneral();
	}
	else
	{
		cout << "   --> This car does not exist!" << endl;
	}
}

void printAllSetting()
{
	system("cls");
	cout << "--- All setting ---" << endl;
	// Đưa ra lựa chọn tìm kiếm
	cout << "1. Search by Personal Key\n";
	cout << "2. Search by Owner Name\n";
	if (inputSelection(2) == 1)
	{
		system("cls");
		cout << "--- All setting ---" << endl;
		// Nhập và tìm kiếm personal key
		string key_number = inputPersonalKey();
		Node* node = btree.searchByKey(key_number);
		// Kết quả tìm kiếm
		if (node != NULL)
		{
			system("cls");
			cout << "--- All setting ---" << endl;
			node->data->info();
		}
		else
		{
			cout << "   --> This car does not exist!" << endl;
		}
	}
	else
	{
		system("cls");
		cout << "--- All setting ---" << endl;
		// Nhập và tìm kiếm Owner name
		string owner_name = "";
		cout << "   Owner name: ";
		getline(cin, owner_name);
		while (!Car::checkOwnerName(owner_name))
		{
			cout << "     * Invalid! Owner name: ";
			getline(cin, owner_name);
		}
		vector<Car*> v = btree.searchByName(owner_name);
		// Kết quả tìm kiếm
		if (v.size() > 0)
		{
			system("cls");
			cout << "--- All setting ---" << endl;
			for (int i = 0; i < v.size(); i++)
			{
				cout << "*" << i + 1 << "*" << endl;
				v.at(i)->info();
			}
		}
		else
		{
			cout << "   --> This car does not exist!" << endl;
		}
	}

}
