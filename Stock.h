#pragma once
#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using namespace boost::gregorian;

class Stock
{
public:
	Stock(const int myid, const date& mydate, const string& s, const int p, const double c) :
		_transid(myid), _transdate(mydate), _symbol(s), _position(p), _cost(c) {}
	virtual ~Stock();

	virtual bool operator==(const Stock&) const;
	virtual bool operator<(const Stock&) const;

	int GetId() const { return _transid; }
	date GetDate() const { return _transdate; }
	string GetSymbol() const { return _symbol; }
	int GetPosition() const { return _position; }
	void SetPosition(const int p) { _position = p; };
	double GetCost() const { return _cost; }
	void SetCost(const double c) { _cost = c;  }

private:
	int _transid;
	date _transdate;
	string _symbol;
	int _position;
	double _cost;
};

