#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Created by:Dujon Brown-Deacon
//Created on: 9/22/17
//Program must take input from user to create a graph then return the order in which the maximum cover is the smallest of all permutations

template <class Object>
class Matrix

{
public:
	Matrix(int rows = 0, int cols = 0) : array(rows)
	{
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	void resize(int rows, int cols)
	{
		array.resize(rows);
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	const vector<Object> & operator[](int row) const
	{
		return array[row];
	}
	vector<Object> & operator[](int row)
	{
		return array[row];
	}
	int numrows() const
	{
		return array.size();
	}
	int numcols() const
	{
		return numrows() ? array[0].size() : 0;
	}
private:
	vector< vector<Object> > array;
};


class Graph
{
public:
	Graph(int size) 
	{ adj.resize(size, size); //Sets adjacency matrix to the size by size 
	numVertices = size;
	maxOrder.resize(size);
	} // creates an empty graph with size vertices
	void fillGraph()
	{
		
		char firstLetter;
		int edges;
		char letter;

		for (int i = 0; i < numVertices; i++) {

			for (int j = 0; j < numVertices; j++) {

				adj[i][j] = 0;//fills adjecency matrix with zeroes

												  }
		
											  }



		for (int i = 0; i < numVertices; i++) {
			cin >> firstLetter;
			idTable.push_back(firstLetter);     //puts lettesr that is stored a the first part of the line in  vectors
			cin >> edges;
			VEdges.push_back(edges);			//puts edges in their own vector
			for (int d = 0; d < edges; d++) {
				cin >> letter;
				Vverts.push_back(letter);		// puts vertices connected to the first letter vertice at the same index as the first letter vertice
			                                }
											 }
		
		
		int k = 0;

		for (int i = 0; i < numVertices; i++) {   // i iterates until i is one less than the number of vertices enter by the user

			for (int j = 0; j < VEdges[i]; j++) {  //j iterates until it is one less the then the number of the is stored in the edge vertex at i
				
				adj[finder(idTable[i],idTable)][finder(Vverts[k],idTable)] = 1;    //finder function searches for the char passed through it in the char vector passed through it
																				   // and returns that letters position in that vector this function is set up so it search so
																				   // the adj cency table is set to one showing that their is an edge connecting the idtable at i and vverts at k
																					// k is used so that the Vverts vector doesnt restart at zero when the loop is exited
				k++;                                                               
				                                                                   
			                                     }


											   }

		


		
		
		
	}; // fills in the graph from cin
	
	void printGraph() 
	{
		for (int i = 0; i < numVertices; i++) {

			for (int j = 0; j < numVertices; j++) {

				cout << adj[i][j];

			}
			cout << endl;

		}
		
	
	}; // prints the graph (for debugging only)
	int maxCover(vector<char>  & order) 
	{
		int bigCov = 0;
		int superCov=numVertices+1 ;
		int Ocov;
		
		sort(order.begin(), order.end());
		

		do {

			bigCov = 0;

			for (int i = 0; i < numVertices; i++) {
				Ocov = cover(order[i], order);
				if (bigCov <Ocov ) {
					
					bigCov=Ocov;
													 }
				

									   }
			if (superCov > bigCov) {
				superCov = bigCov;

				for (int i = 0; i < numVertices; i++) {

					maxOrder[i] = order[i];
				}
				
											      }
			
			}
		while (next_permutation(order.begin(), order.end()));


			return superCov;

	}; // returns the maxCover for the
									  // ordering order
	int cover(char vertex, vector<char> & order) //return largest cover of the order passed through
	{
		int Cover=0;
		int vPlace= finder(vertex, order);    //vPlace is the position in the passed through vector held by the passed through vertex
		

		
		for (int i = 0; i < numVertices; i++) {
			if(adj[finder(vertex,idTable)][finder(idTable[i],idTable)]==1){
				
					if (Cover < abs(vPlace - finder(idTable[i],order))) {
						Cover = abs(vPlace - finder(idTable[i], order));
																	  }
									}
				
								 }

											  

		return Cover;
		
	
	}; // returns the cover size for vertex

	int finder(char VT,vector<char>order)			//Finds where in the matrix that is passed through where the letter passed through is located;
	{                                               // pre condition: VT must be in the matrix and also must be a char, order must already be filled and must be a vector of type char; 
		

			for (int i = 0; i < numVertices; i++) {



				if (order[i] == VT) {


					return i;

				}
											    }
			
			return -1;
			
			
									  
		 
		
		
	};															// post-condition: the position in which the letter is stored in the vector that was passed through is returned

	void copyVec(vector<char> &userVec) {						//pre-condition: idTable must already be filled

		for (int i = 0; i < numVertices; i++) {

			userVec.push_back(idTable[i]);

										  	  }
		

									   };					//post condition: users char vector now contains the same vectors as idtable
	

	void printVec() {				// pre condition : maxCover ffunction must have already been succesfully called

		for (int i = 0; i < numVertices; i++) {
			cout << maxOrder[i] << ' ';

		}
	};									//post condition prints out the order with the best
private:
	Matrix<int> adj;// or Matrix<char> adj;
	
	int numVertices;
	vector<int> VEdges;
	vector<char> Vgraph;
	vector<char> Vverts;
	vector<char> idTable;
	vector<char> maxOrder;
	vector<int> bigVec;
	int tempCov;
};



int main() {

	int numGraphs;
	cin >> numGraphs;

	for (int i = 0; i < numGraphs; i++) {
		int numVertices;
		vector<char> userVec;
		int maxCov;

		cin >> numVertices;
		Graph graf(numVertices);
		graf.fillGraph();
		graf.copyVec(userVec);

		

		maxCov = graf.maxCover(userVec);
		graf.printVec();
		cout << maxCov<<endl;
	}
	

	return 0;
}


