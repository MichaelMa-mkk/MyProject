#include<string>
#include<set>
#include<fstream>
#include<map>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<cmath>
using namespace std;
struct node {
	node() {}
	node(const vector<string> & v, string s)
		:contain(v), sub(s)
	{}
	vector<string> contain;
	string sub;
	bool operator <(const node & x)const {
		return sub < x.sub;
	}
};

struct node2 {
	node2() {}
	node2(const vector<string> & v, int x)
		:contain(v), num(x)
	{}
	vector<string> contain;
	int num = 0;
};

map <int, vector<node>> map_num;
map <string, node2> map_suff;
vector<int> num_l;

ostream& operator<<(ostream& os, const vector<string>& _strv) {// output vector(use in debug)
	for (auto x = _strv.end() - 1; x != _strv.begin(); x--) {
		os << x->data() << " ";
	}
	return os << _strv[0];
	/*for (auto x : _strv) {
		os << x << " ";
	}
	return os;*/
}

int main() {
	int n;
	cin >> n;
	ifstream fin;
	fin.open("dictionary.txt");
	string word;
	while (fin >> word) {
		int l = word.size();
		if (l < n) continue;
		string sub = word.substr(l - n, n);
		map_suff[sub].num++;
		map_suff[sub].contain.push_back(word);
	}
	for (auto i = map_suff.begin(); i != map_suff.end(); i++) {
		sort(i->second.contain.begin(), i->second.contain.end());
		map_num[i->second.num].push_back(node(i->second.contain, i->first));
		num_l.push_back(i->second.num);
	}
	sort(num_l.begin(), num_l.end());
	int l = num_l.size();
	for (int i = 1; i <= min(10, l); i++) {
		auto pos = map_num[num_l[l - i]];
		sort(pos.begin(), pos.end());
		for (auto x = pos.end() - 1; x != pos.begin(); x--)
			cout << x->sub << " " << num_l[l - i] << endl;
		cout << pos.begin()->sub << " " << num_l[l - i] << endl;
	}

	while (1) {
		cout << "query: (enter 0 to quit)";
		string suff;
		int num = 0;
		cin >> suff;
		if (suff[0] >= '0' && suff[0] <= '9') {
			stringstream ss;
			ss << suff;
			ss >> num;
		}
		if (num) {
			auto pos = map_num.find(num);
			if (pos != map_num.end()) {
				for (auto x : pos->second)
					cout << x.sub << " " << x.contain << endl;
			}
			else cout << "not found." << endl;
		}
		else {
			if (suff == "0") break;
			else {
				auto pos = map_suff.find(suff);
				if (pos != map_suff.end()) {
					cout << pos->second.num << " " << pos->second.contain << endl;
				}
				else cout << "not found." << endl;
			}
		}
	}
	system("pause");
	return 0;
}