#pragma once
#include "Stock.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using namespace boost::gregorian;

// of course we derive it
class Option final : public Stock
{
public:
	Option(const int myid, const date& mydate, const string& s, const int p, const double c, const char right, const date& expire, const double strk) :
		Stock(myid, mydate, s, p, c), _right(right), _expdate(expire), _strike(strk) {}
	~Option();

	bool operator==(const Stock&) const override;
	bool operator<(const Stock& rhs) const override;

	int GetRight() const { return _right; }
	date GetExpDate() const { return _expdate; }
	double GetStrike() const { return _strike; }

private:
	char _right;
	date _expdate;
	double _strike;
};


