#pragma once
#include<string>
#include<sstream>
using namespace std;

void Error(const string & s) {
	throw runtime_error(s);
}

string String(int x) {// transfer a int to a string
	stringstream ss;
	ss << x;
	string ans;
	ss >> ans;
	return ans;
}

int checkInt(const string & my_message, int low, int high) { // check if input is avaliable
	stringstream ss;
	ss << my_message;
	int n;
	ss >> n;
	string temp;// save redundant words
	ss >> temp;
	if (my_message[0] < '0' || my_message[0] > '9') Error("Illegal integer format. Try again.");
	if (temp.size()) Error("Illegal integer format. Try again.");
	if (n < low || n > high) Error("N must be " + String(low) + " to " + String(high) + ".");
	return n;
}

double Double(const string & s) {// transfer a string to a double
	stringstream ss;
	ss << s;
	double ans;
	ss >> ans;
	string temp;// save redundant words
	ss >> temp;
	if (s[0] < '0' || s[0] > '9') Error("Illegal float format. Try again.");
	if (temp.size()) Error("Illegal float format. Try again.");
	if (ans - 0 <= 1e-3) Error("price must greater than 0.");
	return ans;
}
