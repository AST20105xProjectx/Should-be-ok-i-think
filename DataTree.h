//Chiu Tze To     SID: 55726127     LID: LA2
#ifndef DataTree_h
#define DataTree_h
#include <iostream>
#include <string>
#include "DataNode.h"

using namespace std;
class DataTree
{
public:
	DataNode* root;
	DataNode* temp;
	int Total;
	int DeleteTotal;

public:
	DataTree();
	~DataTree();
	bool IsEmpty();
	int height(DataNode* h);
	int max(int h1, int h2);
	int GetBalance(DataNode* B);
	DataNode* Getmin(DataNode* min);
	DataNode* GetRoot();
	DataNode* SingleRotateWithLeft(DataNode* k2);
	DataNode* SingleRotateWithRight(DataNode* k1);
	DataNode* DoubleRotateWithLeft(DataNode* k);
	DataNode* DoubleRotateWithRight(DataNode* k);
	DataNode* InsertNode(string str1, string str2, string str3, string str4, string str5, string str6, string str7, string str8, DataNode* T);
	DataNode* PhoneDeleteNode(DataNode* n, long long PhoneNum);
	DataNode* CountryDeleteNode(DataNode* n, string country);
	DataNode* PostOrderCountrySearch(DataNode* Target, string country);
	void PhoneSearch(DataNode* Target, long long PhoneNum);
	void SkillsSearch(DataNode* Target, string skills);
	void JobSearch(DataNode* Target, string Job);
	void CountrySearch(DataNode* Target, string country);
	void DoubleSearchPhone(DataNode* Target, long long PhoneNum, string str, int choice);
	void DoubleSearchXPhone(DataNode* Target, string str1, string str2, int choice);
	void PostOrderTreeDeletion(DataNode* Target);
	DataNode* leftRotate(DataNode* x);
	DataNode* rightRotate(DataNode* x);
};
#endif