#ifndef __CONVERT_IMPL_HPP__
#define __CONVERT_IMPL_HPP__

#include <cstddef>
#include <string>
#include <boost/noncopyable.hpp>
#include "./conversions.hpp"

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

#ifdef HAS_MOVE_SEMANTICS

	convert( string_type&& text )
	: m_buffer( std::move( text ) )
	, m_text( text.c_str() )
		, m_length( text.size() )
	{
	}

#endif
 
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
 
#define CONVERT_DECL( TYPE, NAME ) TYPE const NAME

#endif // __CONVERT_IMPL_HPP__
