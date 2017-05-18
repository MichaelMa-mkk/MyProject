#include "Fix.h"
#include <string>
#include <sstream>
using namespace std;

namespace Fix4 {
	string String(int x) {// transfer a int to a string
		stringstream ss;
		ss << x;
		string ans;
		ss >> ans;
		return ans;
	}

	Fix::Fix()
	{
	}

	Fix::Fix(const string & s)
		:content(s)
	{
		stringstream ss;
		ss << s;
		while (ss) {
			int tag_first;
			char equal, tag_second, semicolon;
			ss >> tag_first >> equal;
			if (tag_first == Price) {// get price
				double price;
				ss >> price >> semicolon;
				order_price = price;
				continue;
			}
			if (tag_first == Qty || tag_first == LeavesQty) {// get quantity
				int quantity;
				ss >> quantity >> semicolon;
				order_quantity = quantity;
				continue;
			}
			if (tag_first == OrdID || tag_first == cancelID) {
				int id;
				ss >> id >> semicolon;
				order_id = String(id);
				continue;
			}
			ss >> tag_second >> semicolon;
			tag[tag_first] = tag_second;
		}
	}


	Fix::~Fix()
	{
	}

	string Fix::str()// get the fix string
		const
	{
		return content;
	}

	char Fix::getTag(int tag_first) const// get tag pair
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) {
			return it->second;
		}
		else return none;
	}

	double Fix::getPrice()// get fix price tag (if has)
		const
	{
		return order_price;
	}

	int Fix::getQuantity() const // get fix OrdQty tag
	{
		return order_quantity;
	}

	string Fix::getID() const
	{
		return order_id;
	}

	bool Fix::addTag(int tag_first, char tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		// transfer tag_first and tag_second to a string
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// update
		content += pair;
		tag[tag_first] = tag_second;
		return true;
	}

	bool Fix::addTag(int tag_first, string tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		// transfer tag_first and tag_second to a string
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// update
		content += pair;
		if (tag_first == OrdID || tag_first == cancelID) order_id = tag_second;
		return true;
	}

	bool Fix::addTag(int tag_first, double tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		// transfer tag_first and tag_second to a string
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// update
		content += pair;
		if (tag_first == OrdID) order_price = tag_second;
		return true;
	}

	bool Fix::addTag(int tag_first, int tag_second)
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		// transfer tag_first and tag_second to a string
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// update
		content += pair;
		if (tag_first == Qty || tag_first == LeavesQty) order_quantity = tag_second;
		return true;
	}

}
