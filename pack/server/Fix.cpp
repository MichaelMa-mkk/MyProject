#include "Fix.h"
#include <string>
#include <sstream>
using namespace std;

namespace Fix4 {

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

	char Fix::getTag(int tag_first) // get tag pair
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) {
			return tag[tag_first];
		}
		else return none;
	}

	double Fix::getPrice()// get fix price tag (if has)
		const
	{
		return order_price;
	}

	bool Fix::addTag(int tag_first, char tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// transfer tag_first and tag_second to a string
		content += pair;
		tag[tag_first] = tag_second;
		// update
		return true;
	}

	bool Fix::addTag(int tag_first, string tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// transfer tag_first and tag_second to a string
		content += pair;
		if (tag_first == OrdID) order_id = tag_second;
		// update
		return true;
	}

	bool Fix::addTag(int tag_first, double tag_second)// add a tag to fix
	{
		auto it = tag.find(tag_first);
		if (it != tag.end()) return false;
		stringstream ss;
		ss << tag_first << "=" << tag_second << ";";
		string pair;
		ss >> pair;
		// transfer tag_first and tag_second to a string
		content += pair;
		if (tag_first == OrdID) order_price = tag_second;
		// update
		return true;
	}

}
