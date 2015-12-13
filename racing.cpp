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

void print_graph(vector< vector<edge> > &graph, int nodes)
{
	for (int i = 0; i < nodes; i++) {
		for (auto j = graph[i].begin(); j != graph[i].end(); ++j) {
			cout << "EDGE: (" << i << ", " << j->to << ")" << endl;
		}
	}
}

ld slope(gem A, gem B)
{
	auto delta_x = B.first - A.first;
	auto delta_y = B.second - A.second;
	return delta_y / delta_x;
}

void topo_sort(int v, vector<bool> &visited, stack<int> &Stack,
		vector< vector<edge> > &Graph)
{
	visited[v] = true;

	for (auto i = Graph[v].begin(); i != Graph[v].end(); ++i) {
		if (!visited[i->to])
			topo_sort(i->to, visited, Stack, Graph);
	}

	Stack.push(v);
}

vector<gem> construct_gems(int N, ld h_start)
{
	vector<gem> gems(N + 1);
	gems[0] = make_pair(h_start, 0.0);

	for (int i = 1; i <= N; i++) {
		gem a;
		cin >> a.first >> a.second;
		gems[i] = a;
	}
	return gems;
}

vector< vector<edge> > construct_graph(int N, int R, vector<gem> &gems)
{
	vector< vector<edge> > graph(N + 1, vector<edge>());

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (gems[j].second > gems[i].second &&
			    abs(slope(gems[j], gems[i])) >= R) {
				edge z;
				z.to = j;
				graph[i].push_back(z);
			}
		}
	}
	return graph;
}

int longest_path(int N, vector< vector<edge> > &graph)
{
	stack<int> Stack;
	vector<int> dist(N + 1, INT_MIN);
	vector<bool> visited(N + 1, false);

	dist[0] = 0;

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
	return ans;
}

int solve(ld N, ld R, ld W, ld H, ld h_start, vector<gem> &gems)
{
	gems[0].first = h_start;
	auto graph = construct_graph(N, R, gems);
	auto ans = longest_path(N, graph);
	return ans;
}

int main()
{
	ld N, R, W, H; /* gems, ratio, width, height */
	cin >> N >> R >> W >> H;

	auto gems = construct_gems(N, 0.0);

	int max_ans = 0;

	for (ld i = 0; i <= W; ++i) {
		max_ans = max(max_ans, solve(N, R, W, H, i, gems));
	}

	cout << max_ans << endl;

	return 0;
}
