#include <string>
#include <iostream>

//#define CHECK_BACKWARD_COMPATIBILITY 
#include "./convert.hpp"

template <class SrcT>
void conversion_test( std::basic_string<SrcT> const& s1, std::basic_string<SrcT> const& s2 )
{
	// case 1: converting an lvalue in a single expression is OK
	std::cout << "This is ok: " << convert<char>( s1 ).c_str() << std::endl;
	// case 2: converting an rvalue (temporary) in a single expression is OK
	std::cout << "This is ok: " << convert<char>( s1 + s2 ).c_str() << std::endl;
	// case 3: converting an lvalue with a named converter<> is OK
	converter<char> const t1( s1 );
	std::cout << "This is ok: " << t1.c_str() << std::endl;
	// case 4: converting an rvalue (temporary) with a named converter<> is BAD
	converter<char> const t12( s1 + s2 );
	std::cout << "Oooops!: " << t12.c_str() << std::endl;
}

int main()
{
	conversion_test( std::wstring(L"Hello"), std::wstring(L" World") );
	conversion_test( std::string("Hello"), std::string(" World") );
}

