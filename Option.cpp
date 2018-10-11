#include "stdafx.h"
#include "Option.h"

bool Option::operator==(const Stock& rhs) const
{
	if (!Stock::operator==(rhs)) return false;

	const auto ptr_rhs = dynamic_cast<const Option*>(&rhs);
	if (ptr_rhs == nullptr) return false;

	if (_right != ptr_rhs->_right)
		return false;

	if (_expdate != ptr_rhs->_expdate)
		return false;

	if (_strike != ptr_rhs->_strike)
		return false;

	return true;
}

bool Option::operator<(const Stock& rhs) const
{
	const auto ptr_rhs = dynamic_cast<const Option*>(&rhs);
	if (ptr_rhs == nullptr) return false;						// stock will go first

	string leftSym = rhs.GetSymbol();

	if (this->GetSymbol() != rhs.GetSymbol())
		return (this->GetSymbol() < rhs.GetSymbol());

	if (_right != ptr_rhs->GetRight())
		return (_right < ptr_rhs->GetRight());

	if (_expdate != ptr_rhs->GetExpDate())
		return (_strike < ptr_rhs->GetStrike());

	if (_strike != ptr_rhs->GetStrike())
		return (_expdate < ptr_rhs->GetExpDate());

	return false;		// are they same? is it error?
}


Option::~Option()
{
	// add cleanup here:

	std::cout << "option " << GetId() << " deleted" << std::endl;
}

