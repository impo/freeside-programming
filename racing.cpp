#include <iostream>
#include <stack>
#include <list>
#include <string>
#include <utility>
#include <limits>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
#include <algorithm>

#define INT_MAX std::numeric_limits<int>::max()
#define INT_MIN std::numeric_limits<int>::min()

using namespace std;

typedef unsigned long long ull;
typedef long double ld;
typedef pair<ld, ld> gem;

struct edge {
	int length = 1;
	int to;
};

ld dist(gem A, gem B)
{
	auto delta_x = B.first - A.first;
	auto delta_y = B.second - A.second;
	return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

void topo_sort(int v, vector<bool> visited, stack<int> &Stack,
		vector< vector<edge> > &Graph)
{
	visited[v] = true;

	for (auto i = Graph[v].begin(); i != Graph[v].end(); ++i) {
		if (!visited[i->to])
			topo_sort(i->to, visited, Stack, Graph);
	}

	Stack.push(v);
}

int main()
{
	ld N, R, W, H; /* gems, ratio, width, height */
	cin >> N >> R >> W >> H;

	vector<gem> gems(N + 1);

	gems[0] = make_pair(0.0, 0.0);

	for (int i = 1; i <= N; i++) {
		gem a;
		cin >> a.first >> a.second;
		gems[i] = a;
	}

	vector< vector<edge> > graph(N, vector<edge>());

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			// there exists an edge from gems[i] to gems[j]
			if ((gems[j].second > gems[i].second) &&
			    (dist(gems[j], gems[i]) >= -R) &&
			    (dist(gems[j], gems[i]) <= R)) {
				edge z;
				z.to = j;
				graph[i].push_back(z);
			}
		}
	}

	// start longest path algo here
	stack<int> Stack;
	vector<int> dist(N + 1, INT_MIN);
	vector<bool> visited(N + 1, false);

	dist[0] = 0; /* dist to source vertex is 0 */

	for (int i = 0; i <= N; i++) {
		if (visited[i] == false)
			topo_sort(i, visited, Stack, graph);
	}

	while (Stack.empty() == false) {
		int u = Stack.top();
		Stack.pop();

		if (dist[u] != INT_MIN) {
			for (auto i = graph[u].begin(); i != graph[u].end();
			     ++i) {
				dist[i->to] = max(dist[i->to],
						  (dist[u] + i->length));
			}
		}
	}

	auto ans = *max_element(dist.begin(), dist.end());

	cout << ans << endl;

	return 0;
}
