#include <cstddef>
#include <string>
#include <locale>
#include <iostream>
#include <boost/noncopyable.hpp>

std::string do_conversion( wchar_t const* /*text*/, size_t /*length*/ )
{
	return std::string();
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
//	return utf8_conv.to_bytes(str);
}

std::wstring do_conversion( char const* /*text*/, size_t /*length*/ )
{
	return std::wstring();
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
//	return utf8_conv.from_bytes(str);
}

template <class CharT>
struct convert 
	: public boost::noncopyable
{
public:
	typedef CharT char_type;
	typedef size_t size_type;

	typedef convert this_type;
	typedef std::basic_string<char_type> string_type;

	convert( string_type const& text )
		: m_text( text.c_str() )
		, m_length( text.size() )
	{
	}

	convert( string_type&& text )
		: m_buffer( std::move( text ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

	convert( this_type&& rhs )
		: m_buffer( std::move( rhs.m_buffer ) )
		, m_text( std::move( rhs.m_text ) )
		, m_length( std::move( rhs.m_length ) )
	{
	}

	template <class T>
	convert( std::basic_string<T> const& text )
		: m_buffer( do_conversion( text.c_str(), text.size() ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

	size_type length() const { return m_length; }

private:
	template <class T> 
	friend T const* c_str_ptr( convert<T> const& );
	template <class T> 
	friend T const* c_str_ptr( convert<T>&& );

	CharT const* c_str() const { return m_text; }

private:
	string_type m_buffer;
	char_type const* m_text;
	size_type m_length;
};

template <class CharT>
CharT const* c_str_ptr( convert<CharT> const& c )
{
	return c.c_str();
}

template <class CharT>
CharT const* c_str_ptr( convert<CharT>&& c )
{
	return c.c_str();
}
 
template <class SrcT>
void conversion_test( std::basic_string<SrcT> const& s1, std::basic_string<SrcT> const& s2 )
{
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 ) ) << std::endl;
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 + s2 ) ) << std::endl;
	convert<char> const t1( s1 );
	std::cout << "This is ok: " << c_str_ptr( t1 ) << std::endl;
	convert<char> const t12( s1 + s2 );
	std::cout << "Oooops!: " << c_str_ptr( t12 ) << std::endl;
}

int main()
{
	//conversion_test( std::wstring(L"Hello"), std::wstring(L" World") );
	conversion_test( std::string("Hello"), std::string(" World") );
}

