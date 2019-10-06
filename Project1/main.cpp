#include <iostream>
#include "PetriNet.h"
using namespace std;

int main() {

	//Create a petriNet Object
	PetriNet pn;
	//Call PetriNet objects' createTestPetriNet() function to fill it with values in the document.
	pn.createTestPetriNet();
	//Print PetriNet as Adjacancy List. We can because Petrinets are a bipartite oriented graph.
	pn.printPetriNetAsAdjacencyList();

	//Call TokenPlayer and pass it which object will be used to start our PetriNet operations.
	pn.TokenPlayer(new Place("P1", 1));
	//pn.TokenPlayer(new Transition("T1"));
	system("pause");
	return 0;
}