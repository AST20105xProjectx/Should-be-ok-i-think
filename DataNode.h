//Chiu Tze To     SID: 55726127     LID: LA2
#ifndef DataNode_h
#define DataNode_h
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class DataNode
{
public:
	DataNode* Left;
	DataNode* Right;
	int height;
	string ID;
	string JobTitle;
	string EmailAddress;
	string LastName;
	string FirstName;
	string PhoneNumber;
	string Skills;
	string Country;
	long long Code;

public:
	long long CodeConvertor(string PhoneNumber)
	{
		string T;
		T += PhoneNumber[0];
		T += PhoneNumber[2];
		T += PhoneNumber[3];
		T += PhoneNumber[4];
		T += PhoneNumber[6];
		T += PhoneNumber[7];
		T += +PhoneNumber[8];
		T += PhoneNumber[10];
		T += PhoneNumber[11];
		T += PhoneNumber[12];
		T += PhoneNumber[13];
		long long Result = stoll(T);
		return Result;
	}

	DataNode(string ID, string JobTitle, string EmailAddress, string LastName, string FirstName, string PhoneNumber, string Skills, string Country)
	{
	Left = Right = NULL;
	this->ID = ID;
	this->JobTitle = JobTitle;
	this->EmailAddress = EmailAddress;
	this->LastName = LastName;
	this->FirstName = FirstName;
	this->PhoneNumber = PhoneNumber;
	this->Skills = Skills;
	this->Country = Country;
	Code = CodeConvertor(PhoneNumber);
	}
};
#endif