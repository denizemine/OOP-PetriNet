#include <iostream>
#include "Place.h"

Place::Place(string _name, int _numberOfTokens)
{
	this->name = _name;
	this->numberOfTokens = _numberOfTokens;
}

string Place::getName()
{
	return name;//private olarak tanýmladýgýmýz için public metod tanýmladým
}

string Place::getType()
{
	return "Place";//
}

int Place::getNumberOfTokens() const
{
	return numberOfTokens;
}

void Place::incrementTokenNumber(int num)
{
	numberOfTokens += num;//kaç tane arttýtCAGINI GÖSTERÝYO
}

void Place::decrementTokenNumber(int num)
{
	numberOfTokens -= num;//KAÇ KULLANDIGINI
}
