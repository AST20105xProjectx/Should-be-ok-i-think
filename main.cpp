//Chiu Tze To     SID: 55726127     LID: LA2
#include <iostream>
#include <fstream>
#include <string>
#include "DataNode.h"
#include "DataTree.h"
#include "Menu.h"
#include "ctime"
#include <chrono> 

using namespace std;
using namespace std::chrono;

// Reading User file data
string readFile()
{
	string tempString = "";
	string filename;

	cout << "Input file name: ";
	cin >> filename;
	ifstream inputFile(filename);

	// Prompt user again if wrong filename received
	while (!inputFile.good())
	{
		cout << "Wrong file name, input again please: ";
		cin >> filename;
		inputFile.open(filename);
	}

	// Append all lines from the file into a long string
	while ((!inputFile.eof()))
	{
		string str;
		getline(inputFile, str);
		tempString += str;
	}
	inputFile.close();
	return tempString;
}

// Seperate the long string into different attribute and store it in the Data Tree
void SeperateFile(string fileString, DataTree* Tree)
{
	DataNode* T;
	char* Ustr;
	char* Unstr;
	int Control = 0;
	string str1, str2, str3, str4, str5, str6, str7, str8;

		char* word = new char[fileString.size() + 1];
		fileString.copy(word, fileString.size() + 1);
		word[fileString.size()] = '\0';
		Ustr = strtok_s(word, "	", &Unstr);
	while (Ustr != NULL)
	{
		switch (Control % 8)
		{
		case 0:
			str1 = Ustr;
			break;
		case 1:
			str2 = Ustr;
			break;
		case 2:
			str3 = Ustr;
			break;
		case 3:
			str4 = Ustr;
			break;
		case 4:
			str5 = Ustr;
		case 5:
			str6 = Ustr;
			break;
		case 6:
			str7 = Ustr;
			break;
		case 7:
			str8 = Ustr;
			T = Tree->root;
			int x = 0;
			Tree->InsertNode(str1, str2, str3, str4, str5, str6, str7, str8,T,x);
			break;
		}
		Ustr = strtok_s(NULL, "	", &Unstr);
		Control++;
	}
	cout << "There are total of " << Tree->Total << " data inserted!\n\n";
}

int main()
{
	Meun m;
	long long Phone;
	string str1, str2;
	DataNode* T;
	cout << "Welcome to our program! \n";
	cout << "======================= \n";

	string fileString = "";
	DataTree *Tree = new DataTree;
	fileString = readFile();
	auto start = high_resolution_clock::now();
	SeperateFile(fileString,Tree);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;

	int choice = 0;
	// Exit the Program by inputting -1
	while (choice != -1)
	{
		m.MainMeun();
		cin >> choice;
		// Insertion of dataset
		if (choice == 1)
		{
			//Deletion of old data
			T = Tree->root;
			Tree->DeleteTotal = 0;
			auto start = high_resolution_clock::now();
			Tree->PostOrderTreeDeletion(T);
			cout << "There are total of " << Tree->DeleteTotal << " data deleted!\n\n";
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;

			// Insertion of new dataset
			string fileString = "";
			DataTree* Tree = new DataTree;
			fileString = readFile();
			auto start = high_resolution_clock::now();
			SeperateFile(fileString, Tree);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
		}
		// Deletion of record(s)
		else if (choice == 2)
		{
			m.Deletion();
			cin >> choice;
			if (choice == 1)
			{
				cout << "Please type in the Phone Number in numbers ONLY (eg. 12345678900: ";
				cin >> Phone;	
				T = Tree->root;
				auto start = high_resolution_clock::now();
				Tree->PhoneDeleteNode(T,Phone);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
			}
			else if (choice == 2)
			{
				cout << "Please type in the Country: ";
				cin >> str1;
				T = Tree->root;
				Tree->DeleteTotal = 0;
				auto start = high_resolution_clock::now();
				Tree->PostOrderCountrySearch(T, str1);
				cout << "There are total of " << Tree->DeleteTotal << " data deleted!\n\n";
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
			}
			else
				cout << "Invalid input! \n";
		}
		// Searching for record(s)
		else if (choice == 3)
		{
			m.Search();
			cin >> choice;
			m.Search2(choice);
			// Searching Phone Number /+ 1 attribute
			if (choice == 1 || (choice >= 5 && choice <= 7))
			{
				cin >> Phone;
				if (choice == 1)
				{
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->PhoneSearch(T, Phone);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
				if (choice == 5)
				{
					cout << "Please type in the Skills: ";
					cin >> str1;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchPhone(T, Phone, str1, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
				else if (choice == 6)
				{
					cout << "Please type in the Job Title: ";
					cin >> str1;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchPhone(T, Phone, str1, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
				else if (choice == 7)
				{
					cout << "Please type in the Country: ";
					cin >> str1;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchPhone(T, Phone, str1, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
			}
			// Searching Skills /+ 1 attribute
			else if (choice == 2 || choice == 8 || choice == 9)
			{
				cin >> str1;
				if (choice == 2)
				{
					T = Tree->root;
					Tree->SkillsSearch(T, str1);
				}
				else if (choice == 8)
				{
					cout << "Please type in the Job Title: ";
					cin >> str2;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchXPhone(T, str1, str2, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
				else if (choice == 9)
				{
					cout << "Please type in the Country: ";
					cin >> str2;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchXPhone(T, str1, str2, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
			}
			// Searching Job Title /+ Country
			else if (choice == 3 || choice == 10)
			{
				cin >> str1;
				if (choice == 3)
				{
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->JobSearch(T, str1);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
				else if (choice == 10)
				{
					cout << "Please type in the Country: ";
					cin >> str2;
					T = Tree->root;
					auto start = high_resolution_clock::now();
					Tree->DoubleSearchXPhone(T, str1, str2, choice);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
				}
			}
			//Searching Country
			else if (choice == 4)
			{
				cin >> str1;
				T = Tree->root;
				auto start = high_resolution_clock::now();
				Tree->CountrySearch(T, str1);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "The time used for excution is: " << duration.count() << " microseconds" << endl;
			}
			else
				cout << "Invalid Input! \n";
		}
		else
		{
			if (choice != -1)
				cout << "Invalid Input! \n\n";
		}
	}
	cout << "Thanks for using my program!! \n";
	system("pause");
	return 0;
}