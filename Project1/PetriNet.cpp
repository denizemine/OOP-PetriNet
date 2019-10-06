#include <iostream>
#include "PetriNet.h"

PetriNet::PetriNet()
{
	//Initialize our state with 0.
	state = 0;
}

void PetriNet::TokenPlayer(ClassInterface* startPlace)
{
	int k = 0; //k holds our number of tries. Used to track state.

	while (true)
	{
		k++;
		prepareEnabledTransitionsWithDFS(startPlace);

		//If there's no enabled transition
		if (enabledTransitions.empty())
		{
			cout << endl << "There are no enabled Transitions left" << endl;
			return;
		}
		//If there is enabled transition, at least 1
		else
		{
			printEnabledTransitions();
			//Fire the transition at the front of our list.
			fireATransition(&enabledTransitions.front());
			printPlacesAndTheirTokens();
		}
	}
}

void PetriNet::fireATransition(Transition* transitionToBeFired)
{
	/*If a transition is sent here to be fired, it means that it has qualification to be
	fired, meaning its inputs hold necessary amount of tokens.
	*/

	/*
	Here we decrement the input places' token numbers by the value of Arc's weight.
	and increment output places' token number by the value of Arc's weight.
	*/

	//Print out Transition to be Fired
	cout << endl << "Transition to be Fired: " << transitionToBeFired->getName() << endl;

	//Traverse the list
	for (auto const&elem : adjList)
	{
		//To decrement tokens from inputs
		for (auto const& val : elem.second)
		{
			//Dynamic Casting
			Transition *tr1 = dynamic_cast<Transition*>(val.second);
			//If val.second's type is Transition above code will be type of Transition object. Otherwise the tr1 above will be NULL
			if (tr1) //If it's not NULL
			{
				//If we find our transition to be fired when traversing. Do the job here.
				if (tr1->getName() == transitionToBeFired->getName()) {
					//Dynamic Casting
					Place *pl = dynamic_cast<Place*>(elem.first);
					//If elem.first's type is Place above code will be type of Place object. Otherwise the pl above will be NULL
					if (pl) //If it's not NULL
					{
						//Decrement input's token number by the value of Arc's weight.
						pl->decrementTokenNumber(val.first.getWeight());
					}
				}

			}
		}


		//To increment tokens on outputs
		/*A transition only goes to 1 place. Therefore there's
		no need to inner for to traverse the list */

		Transition *tr2 = dynamic_cast<Transition*>(elem.first);

		//If elem.first's type is Transition above code will be type of Transition object. Otherwise the tr2 above will be NULL
		if (tr2) //If it's not NULL
		{
			/*We found the transition to be fired. Now find the place this transition goes and increment its token number. */
			if (tr2->getName() == transitionToBeFired->getName())
			{
				for (auto const& val : elem.second)
				{
					Place *pl2 = dynamic_cast<Place*>(val.second);

					//If val.second's type is Place pl2 will be type of Place object. Otherwise pl2 above will be NULL
					if (pl2) //If it's not NULL
					{
						//Increment input's token number by the value of Arc's weight.
						pl2->incrementTokenNumber(val.first.getWeight());
					}
				}

			}
		}
	}
	//Increment state after each Transition is fired.
	this->goNextState();
}

// Generate random number between min(included) and max range (included)
// This will be used to find the transition to be enabled when simultaneous transitions occurs.
int PetriNet::randomGenerator(int min, int max)
{
	random_device rd; // get a random number from hardware
	mt19937 eng(rd()); // seed the generator for truly random
	uniform_int_distribution<> distr(min, max); // define the range

	return distr(eng); //generate and return a random number between range.
}

//Here we create a test PetriNet, exactly the one given in the document.
void  PetriNet::createTestPetriNet()
{
	Place *P1 = new Place("P1", 1); //Name = 'P1', numberOfTokens = 1
	Place *P2 = new Place("P2", 2); //Name = 'P2', numberOfTokens = 2
	Place *P3 = new Place("P3", 0); //Name = 'P3', numberOfTokens = 0

									//Create Arcs
	Arc arc1(1), arc2(1), arc3(1), arc4(1), arc5(1), arc6(1), arc7(1);

	//Create Transitions
	Transition *T1 = new Transition("T1");
	Transition *T2 = new Transition("T2");
	Transition *T3 = new Transition("T3");

	//Create edges for Places and Transitions with help of pairing.
	//And add them to list<edge> with push_back method.

	list<edge> P1edges;
	P1edges.push_back(make_pair(arc1, T1));//liste sonuna ekle 
	P1edges.push_back(make_pair(arc4, T2));

	list<edge> P2edges;
	P2edges.push_back(make_pair(arc3, T3));

	list<edge> P3edges;
	P3edges.push_back(make_pair(arc6, T3));

	list<edge> T1edges;
	T1edges.push_back(make_pair(arc2, P2));

	list<edge> T2edges;
	T2edges.push_back(make_pair(arc5, P3));

	list<edge> T3edges;
	T3edges.push_back(make_pair(arc7, P1));

	//Add them to our map data structure as key-value
	adjList[P1] = P1edges;
	adjList[P2] = P2edges;
	adjList[P3] = P3edges;
	adjList[T1] = T1edges;
	adjList[T2] = T2edges;
	adjList[T3] = T3edges;
}

//Prints PetriNet as adjacency list, using adjList object.
void PetriNet::printPetriNetAsAdjacencyList()
{
	cout << "Created Marked Petri Net is: \n() shows Arc weight:" << endl;
	cout << "----------------------------" << endl;
	for (auto const&elem : adjList)//gezerken degiþiklik yapmýcam p1 p2 p3 t2 elem
	{
		cout << elem.first->getName() << " ->";//classinterface cagýrýyo

		for (auto const& val : elem.second) {//2 tane oldugu için 
			cout << val.second->getName() << "(" << val.first.getWeight() << "), ";
		}
		cout << endl;
	}
	printPlacesAndTheirTokens();
	cout << "----------------------------" << endl;
}

//A utility for DFS to traverse Places and Transitions in PetriNet.
//To fulfill DFS it will call itself recursively.
void PetriNet::DFSUtil(ClassInterface* toBeVisited, list<ClassInterface*> visited)//recursive func hangisi enabled 
{
	visited.push_back(toBeVisited);
	cout << "Now visiting: " << toBeVisited->getName() << endl;

	//Traverse all adjList
	for (auto elem : adjList)
	{
		//If the node we're on while traversing is the one we want to visit in DFS
		if (elem.first->getName() == toBeVisited->getName())
		{
			/* If size of a place's edges is one it means that it doesn't have transitions that are simultaneous*/
			if (elem.second.size() == 1)
			{
				for (auto const& val : elem.second) {//tokenle edge ýn weightýný karþýlaþtýr

					/* Dynamic casting
					Will be used when start node is of type Place and end node is of type Transition
					Used in if clause below
					*/
					Place *pl = dynamic_cast<Place*>(elem.first);
					Transition *tr2 = dynamic_cast<Transition*>(val.second);

					/* Dynamic casting
					Will be used when start node is of type Transition and end node is of type Place
					Used in else if clause below
					*/
					Transition *tr = dynamic_cast<Transition*>(elem.first);
					Place *pl2 = dynamic_cast<Place*>(val.second);

					/*
					pl = elem.first and tr2 = val.second
					This means that its start is Place and its end is a Transition
					*/
					if (pl && tr2)//true ise
					{
						//if weight of the arc is smaller or equal to the place's number of token.
						if (val.first.getWeight() <= pl->getNumberOfTokens())
						{
							//It means that this transition can be enabled.
							//Add it to enabled list if it's not already in it.
							addToListIfNotExistsAlready(tr2);//listeyi baþtan sona gezip varsa eklemiyo
						}
						//if weight of the arc is greater than place's number of token.
						else
						{
							//Do nothing prepareDisabledTransitions() function handles this case.
						}
						/*tr2 is its end node, so if it's not visited in DFS mode, visit it then its neighbor.... */
						if (!isVisitedInDFS(tr2, visited))
						{
							//Go recuriseve, because we're doing DFS
							DFSUtil(tr2, visited);
						}
					}

					/*
					pl2 = val.second and tr = elem.first
					This means that its start is Transition and its end is a Place
					*/
					else if (pl2 && tr)//tokenýmý azaltmýyom
					{
						/*pl2 is its end node, so if it's not visited in DFS mode, visit it then its neighbor.... */
						if (!isVisitedInDFS(pl2, visited))
						{
							//Go recuriseve, because we're doing DFS
							DFSUtil(pl2, visited);
						}

					}
				}
			}
			/* If size of a place's edges is greater one it means that it has transitions that are simultaneous*/
			else if (elem.second.size()>1)
			{
				//Prepare an iterator on end notes.
				list<edge>::iterator it = elem.second.begin();//iterator random number sec.gezici demek 

				/*
				As requested by the document:

				"If there are more than one simultaneous enabled transitions at a time, only one transition will be fired."

				Here we get a random number between 0 and size of that place's we are on-1. So that
				only one transition line will be followed.

				In our test graph that means After P1 we'll go either T1 or T2 but not both.
				*/
				int randomNum = randomGenerator(0, elem.second.size() - 1);
				if (elem.second.size()>randomNum)
				{
					std::advance(it, randomNum);  // "it" now points to the element at index randomNum //listede ileri gitmek
				}

				/* Dynamic casting
				Will be used when start node is of type Place and end node is of type Transition
				Used in if clause below
				*/
				Place *pl = dynamic_cast<Place*>(elem.first);
				Transition *tr2 = dynamic_cast<Transition*>(it->second);

				/* Dynamic casting
				Will be used when start node is of type Transition and end node is of type Place
				Used in else if clause below
				*/
				Transition *tr = dynamic_cast<Transition*>(elem.first);
				Place *pl2 = dynamic_cast<Place*>(it->second);

				/*
				pl = elem.first and tr2 = val.second
				This means that its start is Place and its end is a Transition
				*/
				if (pl && tr2)
				{
					//if weight of the arc is smaller or equal to the place's number of token.
					if (it->first.getWeight() <= pl->getNumberOfTokens())
					{
						//It means that this transition can be enabled.
						//Add it to enabled list if it's not already in it.
						addToListIfNotExistsAlready(tr2);
					}
					//if weight of the arc is greater than place's number of token.
					else
					{
						//Do nothing prepareDisabledTransitions() function handles this case.
					}
					/*tr2 is its end node, so if it's not visited in DFS mode, visit it then its neighbor.... */
					if (!isVisitedInDFS(tr2, visited))
					{
						//Go recuriseve, because we're doing DFS
						DFSUtil(tr2, visited);
					}

				}
				/*
				pl2 = val.second and tr = elem.first
				This means that its start is Transition and its end is a Place
				*/
				else if (pl2 && tr)
				{
					/*pl2 is its end node, so if it's not visited in DFS mode, visit it then its neighbor.... */
					if (!isVisitedInDFS(pl2, visited))
					{
						//Go recuriseve, because we're doing DFS
						DFSUtil(pl2, visited);
					}
				}
			}
		}
	}
}

/*
Here we traverse our petrinet and find Transitions who doesn't fullfil the criteria
i.e. one of their input places don't have enough tokens we add them to a list.
Then subtract them from Enabled Transitions.*/
void PetriNet::prepareDisabledTransitions()
{
	//Traverse the list
	for (auto const&elem : adjList)
	{
		//Traverse the edges part
		for (auto const& val : elem.second) {


			Place *pl = dynamic_cast<Place*>(elem.first);
			//If elem.first's type is Place above code will be type of Place object. Otherwise the pl above will be NULL

			Transition *tr2 = dynamic_cast<Transition*>(val.second);
			//If val.second's type is Transition above code will be type of Transition object. Otherwise the tr2 above will be NULL


			/* Dynamic casting
			Will be used when start node is of type Place and end node is of type Transition
			*/
			if (pl && tr2)
			{
				//if weight of the arc is greater than the place's number of token.
				//Add them to a list. Then subtract them from Enabled Transitions.
				if (val.first.getWeight() > pl->getNumberOfTokens())
				{
					//This transition shouldn't be enabled
					disabledTransitions.push_back(*tr2);
				}
			}
		}
	}
}


void PetriNet::prepareEnabledTransitionsWithDFS(ClassInterface* startPlace)//hangisiyle baþlým enabled places bul
{
	//Clear the contents of these 2 lists. Then we can have a clean start on them.
	disabledTransitions.clear();//tokenler yer degiþtirince yeni enabled olabilir.
	enabledTransitions.clear();

	/*Create a visited list to hold what nodes we visited in DFS.
	If a node is visited it shouldn't be visited second time*/
	list<ClassInterface*> visited;//dfs ile gecerken gezdigimizi ekleriz

	//This finds enabed transitions
	DFSUtil(startPlace, visited);//bir iþi yapan .graphi gezer

	//This finds transitions that shouldn't be enabled
	prepareDisabledTransitions();
	//Then subtract disabled Transitions from Enabled Transitions.*/
	deleteDisabledsFromEnabledList();
}

/*This function traverse the visited list and tries to find if a node is visited in DFS
Returns true if it's visited before, false otherwise
*/
bool PetriNet::isVisitedInDFS(ClassInterface* toBeSearched, list<ClassInterface*> visited)
{
	//Traverse the visited list
	for (auto v : visited)
	{
		//Dynamic casting
		Place *pl = dynamic_cast<Place*>(v);
		Transition *tr = dynamic_cast<Transition*>(v);

		if (pl)
		{
			if (pl->getName() == toBeSearched->getName())
				return true;
		}
		if (tr)
		{
			if (tr->getName() == toBeSearched->getName())
				return true;
		}
	}
	return false;
}


/*This function adds a transition to EnabledTransitions List, if it's not already added.
As we traverse through in our AdjList we may encounter a Transition many times
And we need to be sure this transition is added only once.*/
void PetriNet::addToListIfNotExistsAlready(Transition* transitionToBeAdded)
{
	//Find out if it's already added.
	bool found = (std::find(enabledTransitions.begin(), enabledTransitions.end(), *transitionToBeAdded) != enabledTransitions.end());

	//Not exist in the list, then add it
	if (!found)
	{
		enabledTransitions.push_back(*transitionToBeAdded);//yoksa ekliyo
	}
}


/*This function deletes a transition from EnabledTransitions List, if it exists.
As we traverse through in our AdjList we may encounter a Transition that is enabled
But then its other input place doesn't have enough tokens, so it shouldn't be enabled.
And we need to be sure this transition is deleted from list.*/
void PetriNet::deleteDisabledsFromEnabledList()
{
	for (auto v : disabledTransitions)
	{
		enabledTransitions.remove(v);
	}
}

//Print out enabled transitions
void PetriNet::printEnabledTransitions()
{
	cout << endl << "Enabled Transitions:" << endl;
	for (auto v : enabledTransitions)
	{
		cout << v.getName() << endl;
	}
}

//Print out disabled transitions. Used for debugging.
void PetriNet::printDisabledTransitions()
{
	for (auto v : disabledTransitions)
	{
		cout << v.getName() << endl;
	}
}

//Print out Places and their tokens
void PetriNet::printPlacesAndTheirTokens()
{
	cout << "----------------------------" << endl;
	cout << "Places and their tokens: " << endl;
	for (auto const&elem : adjList)
	{
		//Dynamic Casting
		//We find Place objects and then call its functions.
		Place *pl = dynamic_cast<Place*>(elem.first);
		if (pl)
		{
			cout << pl->getName() << " Number of Tokens: " << pl->getNumberOfTokens() << endl;
		}
	}
	//Also print out the systems state.
	cout << "State of the system is: " << this->getState() << endl;
	cout << "----------------------------" << endl;
}

//Increments our state
void PetriNet::goNextState()
{
	state++;
}

