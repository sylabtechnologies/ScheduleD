#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

// singleton EK2p431
class MsgReport
{
	static MsgReport report;
	static int count;
	string	_title;
	string	_msg;
	bool	print_title = true;

	MsgReport(const string &t) : _title(t) {}
	~MsgReport() { cout << "OK" << std::endl; }

public:
	static MsgReport& getHandle() {	return report; }
	void title(const string &s);
	void operator() (const string &s);		// print
	void operator[] (const string &s);		// add
};

