#include "stdafx.h"
#include "Stock.h"

bool Stock::operator==(const Stock& rhs) const
{
	if (_symbol != rhs._symbol)
		return false;

	return true;
}

bool Stock::operator<(const Stock& rhs) const
{
	return (_symbol < rhs._symbol);
}

Stock::~Stock()
{
	// add cleanup here:

	std::cout << "stock " << GetId() << " deleted" << std::endl;
}
