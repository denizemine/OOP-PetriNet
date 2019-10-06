#include <iostream>
#include "Place.h"

Place::Place(string _name, int _numberOfTokens)
{
	this->name = _name;
	this->numberOfTokens = _numberOfTokens;
}

string Place::getName()
{
	return name;//private olarak tan�mlad�g�m�z i�in public metod tan�mlad�m
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
	numberOfTokens += num;//ka� tane artt�tCAGINI G�STER�YO
}

void Place::decrementTokenNumber(int num)
{
	numberOfTokens -= num;//KA� KULLANDIGINI
}
