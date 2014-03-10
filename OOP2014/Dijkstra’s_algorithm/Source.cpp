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

// start -- �������, �� ������� ������� ����������
void Dijkstra::AlgDijkstra(string start)
{
	   // in_tree[i] == true, ���� ��� ������� i
		   // ��� ��������� ����������� ����������
	bool in_tree = new ;

	   for (int i = 0; i < N; i++)
		      dist[i] = INT_MAX; // �������� �������������,
	      // �. �. ����� ���������� ����� ������ �������

		   dist[start] = 0; // ������� ������, �� ��� ��? ;)

		   string cur = start; // �������, � ������� ��������

	   // ���� ���� �������������� �������
		   while (!in_tree[cur])
		   {
		      in_tree[cur] = true;

		      for (int i = 0; i < N; i++)
			      {
			         // ���� ����� cur � i ���� �����
				         if (adj_matrix[cur][i])
				         {
				            // ������� ���������� �� ������� i:
					            // ���������� �� cur + ��� �����
					            int d = dist[cur] + cost[cur][i];
				            // ���� ��� ������, ��� ��� ����������
					            if (d < dist[i])
					            {
					               dist[i] = d;   // ��������� ���
					               parent[i] = cur; // � "��������"
					            }
				         }
			      }

		      // ���� ��������������� �������
			      // � ����������� �����������
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

	   // ������:
		   // � dist[i] ����������� ���������� �� start �� i
		   // � parent[i] �������, �� ������� ����� ����������� ���� � i
		}

void main()
{

	system("pause");
}