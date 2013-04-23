#ifndef __CONVERSIONS_HPP__
#define __CONVERSIONS_HPP__

#include <string>

std::string do_conversion( std::wstring const& /*text*/ )
{
	return std::string();
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
//	return utf8_conv.to_bytes(str);
}

std::wstring do_conversion( std::string const& /*text*/ )
{
	return std::wstring();
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
//	return utf8_conv.from_bytes(str);
}

#endif // __CONVERSIONS_HPP__
