#ifndef Transition_h
#define Transition_h
#include "ClassInterface.h"
using namespace std;

class Transition : public ClassInterface {
private:
	string name;
public:
	Transition(string _name);
	string getName();//purevirtua tanýmlandýgýn için
	string getType();

	/*These two operators overloaded to make them work in EnabledTransitions find and remove functions
	in PetriNet Class*/
	bool operator == (const Transition& t) const { return name == t.name; }//find için 
	bool operator != (const Transition& t) const { return !operator==(t); }

};

#endif /* Transition_h */
