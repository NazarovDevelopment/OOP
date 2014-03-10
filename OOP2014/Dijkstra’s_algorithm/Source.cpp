#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class graph
{
public:
	graph(int n = 0) :N(n){}
	~graph();
	void add();

private:
	const int N;
	vector<vector<bool>> adj_matrix;
	vector<vector<int>> cost;
};


class Dijkstra
{
public:
	Dijkstra(int n = 0) :N(n){}
	~Dijkstra();

	void AlgDijkstra(string start);

private:
	const int N;
	vector<int> dist;
	vector<string> parent;
};





/*********************************************/

// start -- вершина, от которой считаем расстояния
void Dijkstra::AlgDijkstra(string start)
{
	   // in_tree[i] == true, если для вершины i
		   // уже посчитано минимальное расстояние
	bool in_tree = new ;

	   for (int i = 0; i < N; i++)
		      dist[i] = INT_MAX; // машинная бесконечность,
	      // т. е. любое расстояние будет меньше данного

		   dist[start] = 0; // понятно почему, не так ли? ;)

		   string cur = start; // вершина, с которой работаем

	   // пока есть необработанная вершина
		   while (!in_tree[cur])
		   {
		      in_tree[cur] = true;

		      for (int i = 0; i < N; i++)
			      {
			         // если между cur и i есть ребро
				         if (adj_matrix[cur][i])
				         {
				            // считаем расстояние до вершины i:
					            // расстояние до cur + вес ребра
					            int d = dist[cur] + cost[cur][i];
				            // если оно меньше, чем уже записанное
					            if (d < dist[i])
					            {
					               dist[i] = d;   // обновляем его
					               parent[i] = cur; // и "родителя"
					            }
				         }
			      }

		      // ищем нерассмотренную вершину
			      // с минимальным расстоянием
			      int min_dist = INT_MAX;
		      for (int i = 0; i < N; i++)
			      {
			         if (!in_tree[i] && dist[i] < min_dist)
				         {
				            cur = i;
				            min_dist = dist[i];
				         }
			      }
		   }

	   // Теперь:
		   // в dist[i] минимальное расстояние от start до i
		   // в parent[i] вершина, из которой лежит оптимальный путь в i
		}

void main()
{

	system("pause");
}