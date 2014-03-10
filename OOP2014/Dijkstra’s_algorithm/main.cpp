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
			graph[second_city_name][first_city_name] = weight_of_the_edge;
		}

public:
	map<string, map<string, int>> graph;
};

class Distance
{
public:
	int first;
	string second;
	Distance() :first(0){};
	Distance(int a, const string &b) :first(a), second(b){};

	/*bool operator>(Distance &right){
		return first > right.first;
	}
	bool operator>(Distance &right){
		return first > right.first;
	}*/
};
bool operator<(const Distance &left, const Distance &right){
	return left.first < right.first;
}
bool operator>(const Distance &left,const  Distance &right){
	return left.first > right.first;
}


class AlgorithmD
{
public:
	AlgorithmD();
AlgorithmD(Graph gr) :graph(gr){}

	void shortestDistance(string start, map<string,int> &distances)
	{
		//priority_queue<Distance, vector<Distance>, greater<Distance>> que;
		////map<string, int> distances;
		//que.push(Distance(0, start));
		//while (!que.empty())
		//{
		//	// выбрать ближайший город из очереди
		//	int distance = que.top().len;
		//	string city = que.top().second;
		//	que.pop();

		//	// если мы еще не встречали такой город, обработать его
		//	if (0 == distances.count(city))
		//	{
		//		// затем добавить его к карте
		//		// кратчайших расстояний
		//		distances[city] = distance;

		//		// и занести в очередь новые значения
		//		map<string, int>::iterator start, stop;
		//		start = graph.graph[city].begin();
		//		stop = graph.graph[city].end();
		//		
		//		for (; start != stop; ++start)
		//		{
		//			que.push(Distance(distance + start->second, start->first));
		//		}
		//	}//if
		//}//while

			// обработать приоритетную очередь расстояний до городов
			priority_queue< Distance, vector<Distance>, greater<Distance> > que;

			que.push(Distance(0, start));
			while (!que.empty())
			{
				// выбрать ближайший город из очереди
				int distance = que.top().first;
				string city = que.top().second;
				que.pop();

				// если мы еще не встречали такой город, обработать его
				if (0 == distances.count(city))
				{
					// затем добавить его к карте
					// кратчайших расстояний
					distances[city] = distance;

					// и занести в очередь новые значения
					map<string,int>::iterator start, stop;
					start = graph.graph[city].begin();
					stop = graph.graph[city].end();

					for (; start != stop; ++start)
					{
						que.push(Distance(distance + (*start).second,
							(*start).first));
					}
				}//if
			}//while
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
	mygr.AddEdge(string("Novosibirsk"), string("Toronto"), 10);
	mygr.AddEdge(string("Novosibirsk"), string("Omsk"), 15);
	mygr.AddEdge(string("Omsk"), string("Toronto"), 11);
	mygr.AddEdge(string("Toronto"), string("Krasnoyzrsk"), 11);
	mygr.AddEdge(string("Krasnoyzrsk"), string("Kiev"), 9);
	mygr.AddEdge(string("Kiev"), string("Omsk"), 6);

	AlgorithmD alg(mygr);
//	alg.shortestDistance(string("Moscow"));

	map<string, int> distances;
	 alg.shortestDistance(string("Moscow"), distances);

	 map<string, int>::iterator start = distances.begin();
	 map<string, int>::iterator stop = distances.end();

	 for (; start != stop; ++start)
	 {
		 cout << "Moscow ---- " << (*start).first << " = " << (*start).second << endl;
	 }

	system("pause");
}

