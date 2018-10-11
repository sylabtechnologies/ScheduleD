#include "stdafx.h"
#include "MsgReport.h"

void MsgReport::operator[] (const string &s)
{
	if (_msg.length() != 0)
		_msg += " ";
	else
		if (_title.length() > 0)
		{
			if (_title == "##")
			{
				count++;
				_msg = std::to_string(count) + ". ";
			}
			else
				_msg = _title + ": ";
		}

	_msg += s;
}

void MsgReport::operator() (const string &s)
{
	this->operator[] (s);
	cout << _msg << std::endl;
	_msg.clear();
}

void MsgReport::title(const string &s)
{
	_title = s;
}

