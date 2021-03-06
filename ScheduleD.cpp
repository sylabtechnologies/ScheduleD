// ScheduleD.cpp standard algorithm!
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <iterator>
#include <string>
#include <fstream>
using namespace std;

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

#include "Transaction.h"
#include "MsgReport.h"
#include "Stock.h"
#include "Option.h"

const string MyNameVersion = "Schedule D v1.0";
MsgReport MsgReport::report(MyNameVersion);
int MsgReport::count = 0;

int transactionCount = 0;
int positionCount = 0;

void readPort(set<Stock*>&);
void readSQLTrans(vector<Stock*>&);


int main()
{
	MsgReport& myMsg = MsgReport::getHandle();

	myMsg("using MySQL schema stock"); myMsg.title("##");

	set<Stock*> portfolio;
	readPort(portfolio);
	myMsg["read"]; myMsg[std::to_string(portfolio.size())];
	myMsg("positions");

	vector<Stock*> allTrans; allTrans.reserve(10000);
	readSQLTrans(allTrans);
	myMsg["read"]; myMsg[std::to_string(allTrans.size())];
	myMsg("transactions");

	for (auto iter = allTrans.begin(); iter != allTrans.end(); ++iter)
	{
		;
	}


    return 0;
}

string readVarChar(sql::ResultSet*, int);

void readPort(set<Stock*>& port)
{
	try {
		sql::Driver *driver;
		sql::Connection *con;

		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "RikkiTikki");
		con->setSchema("stock");

		sql::Statement *stmt;
		sql::ResultSet *res;

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM port");

		while (res->next())
		{
			Transaction trans;
			Stock* posPtr;

			trans.transId = res->getInt(1);
			trans.transDate = readVarChar(res, 2);
			date tDate = from_simple_string(trans.transDate);
			trans.symbol = readVarChar(res, 3);
			trans.expDate = readVarChar(res, 4);
			date eDate = from_simple_string(trans.expDate);
			trans.strike = res->getDouble(5);
			trans.right = readVarChar(res, 6);
			trans.quant = res->getInt(7);
			trans.price = res->getDouble(8);
			positionCount++;

			if (trans.right == "STK")
				posPtr = new Stock(trans.transId, tDate, trans.symbol, trans.quant, trans.price);
			else
				posPtr = new Option(trans.transId, tDate, trans.symbol, trans.quant, trans.price, trans.right.at(0), eDate, trans.strike);

			port.insert(posPtr);
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

}

void readSQLTrans(vector<Stock*>& tArray)
{

	try {
		sql::Driver *driver;
		sql::Connection *con;

		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "RikkiTikki");
		con->setSchema("stock");

		sql::Statement *stmt;
		sql::ResultSet *res;

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM trans");

		while (res->next())
		{
			Transaction trans;
			Stock* posPtr;

			trans.transId	= res->getInt(1);
			trans.transDate = readVarChar(res, 2);
			date tDate		= from_simple_string(trans.transDate);
			trans.action	= readVarChar(res, 3);
			trans.symbol	= readVarChar(res, 4);
			trans.expDate	= readVarChar(res, 5);
			date eDate = from_simple_string(trans.expDate);
			trans.strike	= res->getDouble(6);
			trans.right		= readVarChar(res, 7);
			trans.quant		= res->getInt(8);
			trans.price		= res->getDouble(9);
			transactionCount++;

			if (trans.right == "STK")
				posPtr = new Stock(trans.transId, tDate, trans.symbol, trans.quant, trans.price);
			else
				posPtr = new Option(trans.transId, tDate, trans.symbol, trans.quant, trans.price, trans.right.at(0), eDate, trans.strike);

			tArray.push_back(posPtr);
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}


string readVarChar(sql::ResultSet* set, int col)
{
	istream *ss;
	string	answer, temp;
	bool	notfirst = false;

	ss = set->getBlob(col);

	while (*ss >> temp)
	{
		if (notfirst) answer += " ";

		answer += temp; notfirst = true;
	}

	return answer;
}


