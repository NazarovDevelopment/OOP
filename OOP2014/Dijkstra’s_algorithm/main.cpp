#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <queue>

using namespace std;


class Graph
{
public:
	/*Graph();
	~Graph();
*/
	void AddEdge(string first_city_name, string second_city_name, int weight_of_the_edge)
	{
			graph[first_city_name][second_city_name] = weight_of_the_edge;
	}

public:
	map<string, map<string, int>> graph;
};

class Distance
{
public:
	int len;
	string second;
	Distance() :len(0){};
	Distance(int a,const string &b) :len(a), second(b){};
	bool operator<(Distance &right){
		return len < right.len;
	}
};

class AlgorithmD
{
public:
	AlgorithmD();
	AlgorithmD(Graph gr) :graph(gr){}

	map<string, int> shortestDistance(string start)
	{
		priority_queue<Distance, vector<Distance>, greater<Distance>> que;
		map<string, int> distances;
		que.push(Distance(0, start));
		while (!que.empty())
		{
			// выбрать ближайший город из очереди
			int distance = que.top().len;
			string city = que.top().second;
			que.pop();

			// если мы еще не встречали такой город, обработать его
			if (0 == distances.count(city))
			{
				// затем добавить его к карте
				// кратчайших расстояний
				distances[city] = distance;

				// и занести в очередь новые значения
				map<string, int>::iterator start, stop;
				start = graph.graph[city].begin();
				stop = graph.graph[city].end();
				
				for (; start != stop; ++start)
				{
					que.push(Distance(distance + start->second, start->first));
				}
			}//if
		}//while
		return distances;
	}
private: 
	Graph graph;
};


void main()
{
	Graph mygr;
	mygr.AddEdge(string("Moscow"), string("Novosibirsk"),7);
	mygr.AddEdge(string("Moscow"), string("Toronto"), 9);
	mygr.AddEdge(string("Moscow"), string("Krasnoyzrsk"), 14);
	mygr.AddEdge(string("Novosibirsk"), string("Toronto"), 7);
	mygr.AddEdge(string("Novosibirsk"), string("Omsk"), 7);
	mygr.AddEdge(string("Omsk"), string("Toronto"), 7);
	mygr.AddEdge(string("Krasnoyzrsk"), string("Kiev"), 7);
	mygr.AddEdge(string("Kiev"), string("Omsk"), 7);

	AlgorithmD alg(mygr);
	alg.shortestDistance(string("Moscow"));

	map<string, int> dist = alg.shortestDistance(string("Moscow"));

	system("pause");
}

