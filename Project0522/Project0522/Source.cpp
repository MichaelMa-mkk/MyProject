#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>

struct point {
	int x, y;
	point() {};
	point(int x, int y)
		:x(x), y(y)
	{}
};

using namespace std;
vector<vector<int>>map;
int a, b;
int dx[] = { 0,1,-1,0 };
int dy[] = { 1,0,0,-1 };
int ans = 1000000009;

void dfs(int x0, int y0, int xt, int yt, int d = 0) {
	if (x0 == xt && y0 == yt) {
		ans = min(ans, d);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int x = x0 + dx[i];
		int y = y0 + dy[i];
		if (x >= a || x < 0 || y >= b || y < 0) continue;
		if (!map[x][y]) {
			map[x][y] = 2;
			dfs(x, y, xt, yt, d + 1);
			map[x][y] = 0;
		}
	}
}
void dfs(int x0, int y0, point xy, int tot) {
	if (x0 == xy.x && y0 == xy.y && tot == ans) {
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
		throw runtime_error("end");
	}
	for (int i = 0; i < 4; i++) {
		int x = x0 + dx[i];
		int y = y0 + dy[i];
		if (x >= a || x < 0 || y >= b || y < 0) continue;
		if (!map[x][y]) {
			map[x][y] = 2;
			dfs(x, y, xy, tot + 1);
			map[x][y] = 0;
		}
	}
}

int main() {
	ifstream fin("mg4.txt");
	fin >> a >> b;
	for (int i = 0; i < a; i++) {
		map.push_back(vector<int>(b));
		for (int j = 0; j < b; j++) {
			char ch;
			fin >> ch;
			if (ch == '0') map[i][j] = 0;
			if (ch == '1') map[i][j] = 1;
		}
	}
	map[0][0] = 2;
	dfs(0, 0, a - 1, b - 1);
	try {
		dfs(0, 0, point(a - 1, b - 1), 0);
	}
	catch (exception& e) {}
	cout << ans << endl;
	system("pause");
}