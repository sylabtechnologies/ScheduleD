#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using std::string;
using namespace boost::gregorian;

struct Transaction
{
	int transId;
	string transDate;
	string action;
	string symbol;
	string expDate;
	double strike;
	string right;
	int quant;
	double price;

	Transaction();
	~Transaction();
};

