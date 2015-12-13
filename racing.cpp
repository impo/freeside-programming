#include <iostream>
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

	return 0;
}
