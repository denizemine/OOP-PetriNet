#ifndef PetriNet_h
#define PetriNet_h

#include <list>
#include <random>
#include <map>
#include <algorithm>

#include "Transition.h"
#include "Place.h"
#include "Arc.h"
#include "ClassInterface.h"

using namespace std;

class PetriNet {
private:
	//Used to hold enabled Transitions
	list<Transition> enabledTransitions;
	/*When we traverse our petri net and find Transitions who doesn't fullfil the criteria
	i.e. one of their input places don't have enough tokens we add them to a list.
	Then they'll be subtracted from Enabled Transitions.*/
	list<Transition> disabledTransitions;

	int state;//token taþýrsak

	/*We created an interface called ClassInterface and made Place and Transition classes intherit
	from it to hold values that are either Place or Transition.
	*/

	/*That's how we store our Petri Net. We created a pair and called it edge.
	It pairs an Arc object with A ClassInterface object. Using typedef let us to
	call this pair<Arc,ClassInterface*> simply as edge
	*/
	typedef pair<Arc, ClassInterface*> edge;

	/*We hold our PetriNet in a standard library map data structure.
	ClassInterface* here is the starting node, can be Place or Transition
	list<edge> is the edges coming out from this node.
	*/
	map<ClassInterface*, list <edge> > adjList;//plaka kaydediyorsun key 26 variable eses.

	//A utility func. to add a transition to enabled list if not exists there.
	void addToListIfNotExistsAlready(Transition*);//enable olup tutmasý 

	//A utility func. to deletes disabled transitions from enabled list if exists there.
	void deleteDisabledsFromEnabledList();//t3 bir yolda enabled diyip ekliyo sonra 2.defa gittiginde enabled olmadýgý için siliyo

	//Prepares Enabled Transitions with visiting the Pertinet with DFS.
	void prepareEnabledTransitionsWithDFS(ClassInterface*);//hangi nodedan baþlým .

	//A utility function to apply DFS, it calls itself recursively for its purposes.
	void DFSUtil(ClassInterface*, list<ClassInterface*>);

	//In order not to visit a node second time in DFS we hold a visited list.
	//This function tells us whether a node is visited before or not.
	bool isVisitedInDFS(ClassInterface*, list<ClassInterface*>);//daha önce geldik mi

	//We need a random way to follow and fire a transition if there are simultaneous ones.
	//We get a random number from this function.
	int randomGenerator(int, int);//random t1 emi t2 ye gecimmi 

	//Fires a transition that is passed to it as parameter. Increments and Decrements tokens accordingly.
	void fireATransition(Transition*);//transitionadaki inputu token alýr digerine koyar

	//Increments our state
	void goNextState();//state artýrrýr
public:
	PetriNet();//constructor

	//Returns state with an M preceding it.
	string getState() {
		return "M" + to_string(state);
	}

	//That given in document
	void TokenPlayer(ClassInterface*);//dökümana yazdý .do forever tüm fonksiyonlarý bu çagýrýyo.transition  buluyo cagýrýyo 

	//Creates a marked Test Petri Net
	void createTestPetriNet();//þekil otomatik oluþacak
	//Print Petri Net as Adjacancy List. As it's actually a Bipartite oriented Graph.
	void printPetriNetAsAdjacencyList();//

	//Print out Enabled Transitions
	void printEnabledTransitions();
	//Print out Places and Their Tokens
	void printPlacesAndTheirTokens();

	//Finds disabled Transitions and adds them to disabledTransitions list.
	void prepareDisabledTransitions();
	//Print out Disabled Transitions. Used for debugging.
	void printDisabledTransitions();//debug yaparken kullandým
};
#endif /* PetriNet_h */
