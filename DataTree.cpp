//Chiu Tze To     SID: 55726127     LID: LA2
#include <iostream>
#include <string>
#include "DataNode.h"
#include "DataTree.h"

using namespace std;

DataTree::DataTree()
{
	root = temp = NULL ;
	Total = 0;
	DeleteTotal = 0;
}

DataTree::~DataTree()
{
}

bool DataTree::IsEmpty()
{
	return root == NULL ? true : false;
}

int DataTree::height(DataNode* h)
{
	if (h == NULL)
		return -1;
	else
		return h->height;
}

int DataTree::max(int h1, int h2)
{
	if (h1 > h2)
		return h1;
	else
		return h2;
}

int DataTree::GetBalance(DataNode* B)
{
	if (B == NULL)
		return 0;
	return height(B->Left) - height(B->Right);
}

DataNode* DataTree::Getmin(DataNode* min)
{
	DataNode* curr = min;

	/* loop down to find the leftmost leaf */
	while (curr->Left != NULL)
	{
		curr = curr->Left;
	}
	return curr;
}

DataNode* DataTree::GetRoot()
{
	return root;
}

DataNode* DataTree::SingleRotateWithLeft(DataNode* k2)
{
	DataNode* k1;
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;
	k2->height = max(height(k2->Left), height(k2->Right)) + 1;
	k1->height = max(height(k1->Left), k2->height) + 1;
	return k1;
}

DataNode* DataTree::SingleRotateWithRight(DataNode* k1)
{
	DataNode* k2;
	k2 = k1->Right;
	k1->Right = k2->Left;
	k2->Left = k1;
	k1->height = max(height(k1->Left), height(k1->Right)) + 1;
	k2->height = max(height(k2->Right), k1->height) + 1;
	return k2;
}

DataNode* DataTree::DoubleRotateWithLeft(DataNode* k)
{
	k->Left = SingleRotateWithRight(k->Left);
	return SingleRotateWithLeft(k);
}

DataNode* DataTree::DoubleRotateWithRight(DataNode* k)
{
	k->Right = SingleRotateWithLeft(k->Right);
	return SingleRotateWithRight(k);
}

DataNode* DataTree::InsertNode(string str1,string str2, string str3, string str4, string str5, string str6, string str7, string str8,DataNode* T, int x)
{
	DataNode* newNode = new DataNode(str1, str2, str3, str4, str5, str6, str7, str8);
	if (T == NULL) 
	{
		T = newNode;
		if (T == NULL) {
			cout << "Out of memory, Insert unsucessful! \n" << endl; exit(1);
		}
		else 
		{ 
		T->height = 0; T->Left = T->Right = NULL; 
		Total++;
		if (x == 0)
		{
			root = newNode;
		}
		}
	}
	else
	{
		x = 1;
		if (newNode->Code < T->Code)
		{
			T->Left = InsertNode(str1, str2, str3, str4, str5, str6, str7, str8, T->Left, x);
			if (height(T->Left) - height(T->Right) == 2)
				if (newNode->Code < T->Left->Code)
					T = SingleRotateWithLeft(T);
				else
					T = DoubleRotateWithLeft(T);
		}
		else
			if (newNode->Code > T->Code) 
			{
				T->Right = InsertNode(str1, str2, str3, str4, str5, str6, str7, str8, T->Right, x);
				if (height(T->Right) - height(T->Left) == 2)
					if (newNode->Code > T->Right->Code)
						T = SingleRotateWithRight(T);
					else
						T = DoubleRotateWithRight(T);
			}
	}
	T->height = max(height(T->Left), height(T->Right)) + 1;
	return T;
}

DataNode* DataTree::PhoneDeleteNode(DataNode* n, long long PhoneNum)
{

	// Standard Deletion
	if (n == NULL)
		return n;

	if ( PhoneNum < n->Code )
		n->Left = PhoneDeleteNode(n->Left, PhoneNum);
	else if( PhoneNum > n->Code )
		n->Right = PhoneDeleteNode(n->Right, PhoneNum);
	// if same PhoneNumber, this is the target node to be deleted
	else
	{
		// node with only one child or no child
		if((n->Left == NULL) || (n->Right == NULL))
		{
			DataNode *Temp = n->Left ? n->Left : n->Right;

			// No child case
			if (Temp == NULL)
			{
				Temp = n;
				n = NULL;
			}
			// One child case
			else
			*n = *Temp; // Copy the contents of the non-empty child
			delete Temp;
		}
		else
		{
			// Node with two children:
			//Get the inorder successor (smallest in the right subtree)
			DataNode* Temp = Getmin(n->Right);

			// Copy the inorder successor's data to this node
			n->ID = Temp->ID;
			n->JobTitle = Temp->JobTitle;
			n->EmailAddress = Temp->EmailAddress;
			n->LastName = Temp->LastName;
			n->FirstName = Temp->FirstName;
			n->PhoneNumber = Temp->PhoneNumber;
			n->Skills = Temp->Skills;
			n->Country = Temp->Country;
			n->Code = Temp->Code;

			// Delete the inorder successor
			n->Right = PhoneDeleteNode(n->Right, Temp->Code);
		}
	}

	// If the DataTree had only one node
	// then return
	if (n == NULL)
	return n;

	// Update height of the new Datanode
	n->height = 1 + max(height(n->Left), height(n->Right));

	// Check whether this DataNode is balance or not
	int Balance = GetBalance(n);

	// Left Left Case
	if (Balance > 1 &&
		GetBalance(n->Left) >= 0)
		return SingleRotateWithRight(n);

	// Left Right Case
	if (Balance > 1 &&
		GetBalance(n->Left) < 0)
	{
		n->Left = SingleRotateWithLeft(n->Left);
		return SingleRotateWithRight(n);
	}

	// Right Right Case
	if (Balance < -1 &&
		GetBalance(n->Right) <= 0)
		return SingleRotateWithLeft(n);

	// Right Left Case
	if (Balance < -1 &&
		GetBalance(n->Right) > 0)
	{
		n->Right = SingleRotateWithRight(n->Right);
		return SingleRotateWithLeft(n);
	}

	return n;
}

/*DataNode* DataTree::CountryDeleteNode(DataNode* n, string country)
{

	// Standard Deletion
	if (n == NULL)
		return n;

	// Delete target node when the target country found
	if (n->Country == country)
	{
		// node with only one child or no child
		if ((n->Left == NULL) || (n->Right == NULL))
		{
			DataNode* Temp = n->Left ? n->Left : n->Right;

			// No child case
			if (Temp == NULL)
			{
				Temp = n;
				n = NULL;
			}
			// One child case
			else
				*n = *Temp; // Copy the contents of the non-empty child
			delete Temp;
		}
		else
		{
			// Node with two children:
			//Get the inorder successor (smallest in the right subtree)
			DataNode* Temp = Getmin(n->Right);

			// Copy the inorder successor's data to this node
			n->ID = Temp->ID;
			n->JobTitle = Temp->JobTitle;
			n->EmailAddress = Temp->EmailAddress;
			n->LastName = Temp->LastName;
			n->FirstName = Temp->FirstName;
			n->PhoneNumber = Temp->PhoneNumber;
			n->Skills = Temp->Skills;
			n->Country = Temp->Country;
			n->Code = Temp->Code;

			// Delete the inorder successor
			n->Right = CountryDeleteNode(n->Right, Temp->Country);
		}
	}

	// If the DataTree had only one node
	// then return
	if (n == NULL)
		return n;

	// Update height of the new Datanode
	n->height = 1 + max(height(n->Left), height(n->Right));

	// Check whether this DataNode is balance or not
	int Balance = GetBalance(n);

	// Left Left Case
	if (Balance > 1 &&
		GetBalance(n->Left) >= 0)
		return SingleRotateWithRight(n);

	// Left Right Case
	if (Balance > 1 &&
		GetBalance(n->Left) < 0)
	{
		n->Left = SingleRotateWithLeft(n->Left);
		return SingleRotateWithRight(n);
	}

	// Right Right Case
	if (Balance < -1 &&
		GetBalance(n->Right) <= 0)
		return SingleRotateWithLeft(n);

	// Right Left Case
	if (Balance < -1 &&
		GetBalance(n->Right) > 0)
	{
		n->Right = SingleRotateWithRight(n->Right);
		return SingleRotateWithLeft(n);
	}

	return n;
}

DataNode* DataTree::PostOrderCountrySearch(DataNode* Target, string country)
{
	if (Target != NULL)
	{
		PostOrderTreeDeletion(Target->Left);
		PostOrderTreeDeletion(Target->Right);

		if (Target->Country == country)
		{
			CountryDeleteNode(Target, country);
			DeleteTotal++;
		}

	}
	return Target;
}*/

void DataTree::PhoneSearch(DataNode* Target,long long PhoneNum)
{
	if (Target != NULL)
	{
		if (Target->Code == PhoneNum)
		{
			cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
				 << Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
		}
		PhoneSearch(Target->Left,PhoneNum);
		PhoneSearch(Target->Right,PhoneNum);
	}
}

void DataTree::SkillsSearch(DataNode* Target, string skills)
{
	if (Target != NULL)
	{
		if (Target->Skills == skills)
		{
			cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
				<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
		}
		SkillsSearch(Target->Left, skills);
		SkillsSearch(Target->Right, skills);
	}
}

void DataTree::JobSearch(DataNode* Target, string Job)
{
	if (Target != NULL)
	{
		if (Target->JobTitle == Job)
		{
			cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
				<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
		}
		JobSearch(Target->Left, Job);
		JobSearch(Target->Right, Job);
	}
}

void DataTree::CountrySearch(DataNode* Target, string country)
{
	if (Target != NULL)
	{
		if (Target->Country == country)
		{
			cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
				<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
		}
		CountrySearch(Target->Left, country);
		CountrySearch(Target->Right, country);
	}
}

void DataTree::DoubleSearchPhone(DataNode* Target, long long PhoneNum, string str, int choice)
{
	int control = 0;
	if (Target != NULL)
	{
		switch(choice)
		{
		case 5:
			if (Target->Code == PhoneNum && Target->Skills == str)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		case 6:
			if (Target->Code == PhoneNum && Target->JobTitle == str)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		case 7:
			if (Target->Code == PhoneNum && Target->Country == str)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		default:
			cout << "You choose the invalid choice!\n";
			control = 1;
		}
		if (control == 0)
		{
			DoubleSearchPhone(Target->Left, PhoneNum, str, choice);
			DoubleSearchPhone(Target->Right, PhoneNum, str, choice);
		}
	}
}

void DataTree::DoubleSearchXPhone(DataNode* Target, string str1, string str2, int choice)
{
	int control = 0;
	if (Target != NULL)
	{
		switch (choice)
		{
		case 8:
			if (Target->Skills == str1 && Target->JobTitle == str2)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		case 9:
			if (Target->Skills == str1 && Target->Country == str2)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		case 10:
			if (Target->JobTitle == str1 && Target->Country == str2)
			{
				cout << Target->ID << "\t" << Target->JobTitle << "\t" << Target->EmailAddress << "\t" << Target->LastName << "\t"
					<< Target->FirstName << "\t" << Target->PhoneNumber << "\t" << Target->Skills << "\t" << Target->Country << "\n";
			}
			break;
		default:
			cout << "You choose the invalid choice!\n";
			control = 1;
		}
		if (control == 0)
		{
			DoubleSearchXPhone(Target->Left, str1, str2, choice);
			DoubleSearchXPhone(Target->Right, str1, str2, choice);
		}
	}
}

void DataTree::PostOrderTreeDeletion(DataNode* Target)
{
	if (Target != NULL)
	{
		PostOrderTreeDeletion(Target->Left);
		PostOrderTreeDeletion(Target->Right);
		delete Target;
		DeleteTotal++;
	}
}