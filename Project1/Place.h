#ifndef Place_h
#define Place_h
#include "ClassInterface.h"

#include <string>
using namespace std;
//We have defined an interface called ClassInterface. Transition and Place inherit from it. The reason we define this Interface
//is either DFS or  we're navigating in a lot of places or Transition. 
//Using Inheritance, it was enough to use ClassInterface to replace these two.
class Place : public ClassInterface{
private:
	string name;
	int numberOfTokens;
public:
	Place(string, int);
	string getName();
	string getType();
	int getNumberOfTokens() const;
	void incrementTokenNumber(int);
	void decrementTokenNumber(int);

	/*These two operators overloaded to make them work in EnabledTransitions find and remove functions
	in PetriNet Class*/
	bool operator == (const Place& p) const { return name == p.name; }//operator overloading  p2 olaný silmek için gerek yok ama iþe yarar
	bool operator != (const Place& p) const { return !operator==(p); }

};


#endif /* Place_h */
