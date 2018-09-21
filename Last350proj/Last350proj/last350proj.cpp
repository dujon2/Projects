//Created by DuJon Brown-Deacon
//Description:Finds shortest distance need to travel to collect 
//each pokemon once and return home


#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<functional>

using namespace std;

struct pokeStop {
	string name;
	int x;
	int y;
	int pIndex;
	int distSF;
	bool visited;
	pokeStop() {}
	pokeStop(int xcoor, int ycoor, int index, string PName)
	{
		name = PName;
		x = xcoor;
		y = ycoor;
		pIndex = index;
		distSF = 0;
		visited = false;
	}
	bool operator<(const pokeStop& other) const
	{
		(this->distSF < other.distSF);
	}
	bool operator>(const pokeStop & other) const
	{
		return (this->distSF > other.distSF);
	}
};
class goPlayer {

public:
	int x;
	int y;
	int Distance=0;
	vector<pokeStop> stops;
	priority_queue<pokeStop, vector<pokeStop>, greater<pokeStop>> minHeap;

	goPlayer() 
	{
		x = 0;
		y = 0;
		int Distance = 0;
	}
	//pre: none
	//post: contents of pokeStop passed through are push into vector of pokestops
	void addPokeStop(pokeStop stopp)
	{
		

		stops.push_back(stopp);
	}

	//pre: index has to be positive
	//post: returns stops at index 
	pokeStop getPokeIndex(int index) 
	{
		

		return stops[index];
	}

	//pre: N/A
	//post: Shows if all stops have been visited yet
	bool allVisited() 
	{

		int count = 0;

		for (int i = 0; i < stops.size(); i++) 
		{
			if (stops[i].visited == true)
			{
				count++;
			}
		}
		if (count == stops.size()) 
		{
			return true;
		}
		return false;
	}
	//pre: N/A
	//post: Sets stopp passed through to visited
	void setVisted(pokeStop stopp) 
	{
		

		for (int i = 0; i < stops.size(); i++) 
		{
			if (stops[i].name == stopp.name) 
			{
				stops[i].visited = true;
			}
		}
	}
	//pre:N/A
	//post:if all stops are visted this returns distance so far 
	//if not calls returns distance after heaper is called
	int bounder(pokeStop stopp) 
	{
		setVisted(stopp);
	
		if (!allVisited()) 
		{
			bounder(heaper());
		}

		return Distance;
	}
	//pre: N/A
	//post: returns stop with shorest dist from player
	pokeStop heaper() {
		

		priority_queue<pokeStop, vector<pokeStop>, greater<pokeStop>> tempHeap;

		for (int i = 0; i < stops.size(); i++) 
		{
			if (stops[i].visited != true)
			{
				fDistance(stops[i], i);
				tempHeap.push(stops[i]);
			}
		}
		minHeap.push(tempHeap.top());
		x = tempHeap.top().x;
		y = tempHeap.top().y;
		Distance =Distance + tempHeap.top().distSF;

		return tempHeap.top();
	}
	//pre: index must be positive
	//post: Adds to stops distaneS(o)F(ar)
	void fDistance(pokeStop stopp, int index) 
	{
		

		stops[index].distSF = abs(stopp.x - x) + abs(stopp.y - y);
	}
	//pre: N/A
	//post: Adds to stops total distal=nce
	void dAdder(pokeStop stopp) 
	{
		x = stopp.x;
		y = stopp.y;
		Distance =Distance + abs(stopp.x) + abs(stopp.y);
	}
	//pre: N/A
	//post: Adds to totalDistance distance it takes to get back to starting point
	void lastDAdder() {
		

		Distance =Distance + abs(x) + abs(y);
		x = 0;
		y = 0;
	}
	//pre: N/A
	//post: clears heap, distance and stops;
	void pClear() 
	{
		

		Distance = 0;
		while (!minHeap.empty())
		{
			minHeap.pop();
		}
		for (int i = 0; i < stops.size(); i++)
		{
			stops[i].visited = false;
			stops[i].distSF = 0;
		}
		
	}
};

int main() 
{

	int stops;
	int x;
	int y;
	string name;
	goPlayer player;
	priority_queue<int, vector<int>, greater<int>> variants;

	cin >> stops;

	for (int i = 0; i < stops; i++)
	{
		cin >> x;
		cin >> y;
		cin >> name;
		pokeStop localStop( x, y, i, name);
		player.addPokeStop(localStop);
	}

	
	for (int i = 0; i < stops; i++) 
	{
		player.dAdder(player.getPokeIndex(i));
		player.bounder(player.getPokeIndex(i));
		player.lastDAdder();
		variants.push(player.Distance);
		player.pClear();
	}

	cout << variants.top();

	return 0;
}