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

#ifdef __GXX_EXPERIMENTAL_CXX0X__

template <class CharT>
struct convert_lval
	: public boost::noncopyable
{
	typedef CharT char_type;
	typedef size_t size_type;
	
	typedef convert_lval this_type;
	typedef std::basic_string<char_type> string_type;
	
	convert_lval( this_type&& rhs )
	: m_buffer( std::move( rhs.m_buffer ) )
		, m_text( std::move( rhs.m_text ) )
		, m_length( std::move( rhs.m_length ) )
	{
	}

	convert_lval( string_type const& text )
	: m_text( text.c_str() )
		, m_length( text.size() )
	{
	}

	template <class T>
	convert_lval( std::basic_string<T> const& text )
		: m_buffer( do_conversion( text.c_str(), text.size() ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

	size_type length() const { return m_length; }

private:
	template <class T> 
	friend T const* c_str_ptr( convert_lval<T> const& );
	template <class T> 
	friend T const* c_str_ptr( convert_lval<T>&& );

	CharT const* c_str() const { return m_text; }

private:
	string_type m_buffer;
	char_type const* m_text;
	size_type m_length;
};

template <class CharT>
CharT const* c_str_ptr( convert_lval<CharT> const& c )
{
	return c.c_str();
}

template <class CharT>
CharT const* c_str_ptr( convert_lval<CharT>&& c )
{
	return c.c_str();
}


template <class CharT>
struct convert_rval
	: public boost::noncopyable
{
	typedef CharT char_type;
	typedef size_t size_type;
	
	typedef convert_rval this_type;
	typedef std::basic_string<char_type> string_type;
	
	convert_rval( this_type&& rhs )
	: m_buffer( std::move( rhs.m_buffer ) )
		, m_text( std::move( rhs.m_text ) )
		, m_length( std::move( rhs.m_length ) )
	{
	}

	convert_rval( string_type&& text )
	: m_buffer( std::move( text ) )
	, m_text( m_buffer.c_str() )
	, m_length( m_buffer.size() )
	{
	}

	template <class T>
	convert_rval( std::basic_string<T>&& text )
		: m_buffer( do_conversion( text.c_str(), text.size() ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

	size_type length() const { return m_length; }

private:
	//template <class T> 
	//friend T const* c_str_ptr( convert_rval<T> const& );
	template <class T> 
	friend T const* c_str_ptr( convert_rval<T>&& );

	CharT const* c_str() const { return m_text; }

private:
	string_type m_buffer;
	char_type const* m_text;
	size_type m_length;
};

template <class CharT>
CharT const* c_str_ptr( convert_rval<CharT> const& c )
{
	// This is not allowed before we have C++11 support on all target platforms
	// (r-value string conversion must be performed within the same expression)
	return c.c_str();
}

template <class CharT>
CharT const* c_str_ptr( convert_rval<CharT>&& c )
{
	return c.c_str();
}

template <class OutCharT, class InCharT>
convert_lval<OutCharT> convert( std::basic_string<InCharT> const& str )
{
	return convert_lval<OutCharT>( str );
}

template <class OutCharT, class InCharT>
convert_rval<OutCharT> convert( std::basic_string<InCharT>&& str )
{
	return convert_rval<OutCharT>( std::move( str ) );
}

#define DECL( TYPE, NAME ) auto const NAME = TYPE

#else 

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
 
#define DECL( TYPE, NAME ) TYPE const NAME

#endif

template <class SrcT>
void conversion_test( std::basic_string<SrcT> const& s1, std::basic_string<SrcT> const& s2 )
{
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 ) ) << std::endl;
	std::cout << "This is ok: " << c_str_ptr( convert<char>( s1 + s2 ) ) << std::endl;
	DECL( convert<char>, t1 )( s1 );
	std::cout << "This is ok: " << c_str_ptr( t1 ) << std::endl;
	DECL( convert<char>, t12 )( s1 + s2 );
	std::cout << "Oooops!: " << c_str_ptr( t12 ) << std::endl;
}

int main()
{
	conversion_test( std::wstring(L"Hello"), std::wstring(L" World") );
	conversion_test( std::string("Hello"), std::string(" World") );
}

