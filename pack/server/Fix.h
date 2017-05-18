#pragma once
#include <string>
#include <unordered_map>
using namespace std;

namespace Fix4 {

	const int Price = 44;// tag Price
	const int OrdID = 11;// tag ClOrdID
	const int Side = 54;// tag Side
	const int Type = 35;// tag MsgType
	const int Status = 39;// tag OrdStatus
	const int ExecType = 150;// tag ExecType
	const int Qty = 38;// tag OrdQty
	const int Symbol = 55;// tag Symbol 
	const int clientID = 109;// tag clientID
	const int LeavesQty = 151;// tag LeavesQty
	const int cancelID = 41;// tag OrigClOrdID

	class Fix
	{
	public:
		const char none = 'Z';

		Fix();
		Fix(const string &);
		~Fix();
		string str() const;
		char getTag(int tag_first) const;
		double getPrice() const;
		int getQuantity() const;
		string getID() const;
		bool addTag(int tag_first, char tag_second);
		bool addTag(int tag_first, string tag_second);
		bool addTag(int tag_first, double tag_second);
		bool addTag(int tag_first, int tag_second);

	private:
		string content;
		unordered_map<int, char> tag;
		double order_price;
		string order_id;
		int order_quantity;

	};
}
