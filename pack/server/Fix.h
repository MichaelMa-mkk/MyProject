#pragma once
#include <string>
#include <unordered_map>
using namespace std;

namespace Fix4 {

	const int Price = 44;// tag Price
	const int OrdID = 11;// tag ClOrdID
	const int Side = 54;// tag Side
	const int Type = 35;// tag type

	class Fix
	{
	public:
		const char none = 'Z';

		Fix();
		Fix(const string &);
		~Fix();
		string str() const;
		char getTag(int tag_first);
		double getPrice() const;
		bool addTag(int tag_first, char tag_second);
		bool addTag(int tag_first, string tag_second);
		bool addTag(int tag_first, double tag_second);

	private:
		string content;
		unordered_map<int, char> tag;
		double order_price;
		string order_id;

	};
}
