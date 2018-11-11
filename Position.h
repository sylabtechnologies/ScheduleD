#pragma once
#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using namespace boost::gregorian;

#define ASSIGNMENT_2CLOSE	2
#define ASSIGNMENT_2OPEN	1

#define EXERCISE_CLOSE		4
#define EXERCISE_OPEN		3

class Position
{
public:
	Position(const int myid, const date& mydate, const string& s, const int p, const double c, const int act) :
		_transid(myid), _transdate(mydate), _symbol(s), _position(p), _cost(c), _action(act) {}
	virtual ~Position() {}

	virtual const Position& operator=(const Position&) = 0;
	virtual bool operator==(const Position&) const = 0;
	virtual bool operator<(const Position&) const = 0;
	virtual std::string print() const = 0;

	int GetId() const { return _transid; }
	date GetDate() const { return _transdate; }
	string GetSymbol() const { return _symbol; }
	int GetPosition() const { return _position; }
	void SetPosition(const int p) { _position = p; };
	double GetCost() const {
		return _cost;
	}
	void SetCost(const double c) { _cost = c;  }
	int GetAction() const { return _action; }

protected:
	int _transid;
	date _transdate;
	string _symbol;
	int _position;
	double _cost;
	int _action;
};

