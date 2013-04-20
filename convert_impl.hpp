#ifndef __CONVERT_IMPL_HPP__
#define __CONVERT_IMPL_HPP__

#include <cstddef>
#include <string>
#include <boost/noncopyable.hpp>
#include "./conversions.hpp"

template <class CharT>
class converter
	: public boost::noncopyable
{
public:
	typedef CharT char_type;
	typedef size_t size_type;

	typedef converter this_type;
	typedef std::basic_string<char_type> string_type;

	converter( string_type const& text )
	: m_buffer()
	, m_text( text.c_str() )
	, m_length( text.size() )
	{
	}

	template <class T>
	converter( std::basic_string<T> const& text )
		: m_buffer( do_conversion( text.c_str(), text.size() ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

#ifdef HAS_MOVE_SEMANTICS

	converter( this_type&& rhs )
	: m_buffer( std::move( rhs.m_buffer ) )
	, m_text( std::move( rhs.m_text ) )
	, m_length( std::move( rhs.m_length ) )
	{
	}

	 	// This is not allowed before we have C++11 support on all target platforms
	 	// (r-value string conversion must be performed within the same expression)
		//return m_text; 
#endif

	CharT const* c_str() const
	{ 
		return m_text; 
	}
 
	size_type length() const { return m_length; }

private:
	converter( string_type&& text )
	: m_buffer( std::move( text ) )
	, m_text( m_buffer.c_str() )
	, m_length( text.size() )
	{
	}

	template <class T>
	converter( std::basic_string<T>&& text )
		: converter( text )
	{
	}

	template <class CT, class T>
	friend converter<CT> convert( T&& text );

private:
	string_type m_buffer;
	char_type const* m_text;
	size_type m_length;
};

template <class CharT, class T>
converter<CharT> convert( T&& text )
{
	return converter<CharT>( std::forward<T>( text ) ); 
} 

#endif // __CONVERT_IMPL_HPP__
