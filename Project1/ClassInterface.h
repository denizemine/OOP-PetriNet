#ifndef ClassInterface_h
#define ClassInterface_h

using namespace std;

/*We created an interface called ClassInterface and made Place and Transition classes inherit
from it to hold values that are either Place or Transition.
*/
class ClassInterface
{
public:
	virtual string getName() = 0; //Pure virtual all derived classes have to implement it.
	virtual string getType() = 0; //Pure virtual all derived classes have to implement it.
	~ClassInterface() = default;//DESTRUCTOR
private:
};

#endif /* ClassInterface_h */
