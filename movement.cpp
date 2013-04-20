#include <string>
#include <iostream>

#define CHECK_BACKWARD_COMPATIBILITY 
#include "./convert.hpp"

template <class SrcT>
void conversion_test( std::basic_string<SrcT> const& s1, std::basic_string<SrcT> const& s2 )
{
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 ) ) << std::endl;
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 + s2 ) ) << std::endl;
	CONVERT_DECL( convert<char>, t1 )( s1 );
	std::cout << "This is ok: " << c_str_ptr( t1 ) << std::endl;
	CONVERT_DECL( convert<char>, t12 )( s1 + s2 );
	std::cout << "Oooops!: " << c_str_ptr( t12 ) << std::endl;
}

int main()
{
	conversion_test( std::wstring(L"Hello"), std::wstring(L" World") );
	conversion_test( std::string("Hello"), std::string(" World") );
}

