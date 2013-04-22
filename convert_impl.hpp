#ifndef __CONVERT_IMPL_HPP__
#define __CONVERT_IMPL_HPP__

#include <cstddef>
#include <string>
#include "./conversions.hpp"

template <typename CharT>
class converter
{
public:
	typedef CharT char_type;
	typedef size_t size_type;

	typedef converter this_type;
	typedef std::basic_string<char_type> string_type;

	converter( string_type const& text )
	: m_text( text.c_str() )
	, m_length( text.size() )
	{
	}

	template <typename T>
	converter( std::basic_string<T> const& text )
		: m_buffer( do_conversion( text.c_str(), text.size() ) )
		, m_text( m_buffer.c_str() )
		, m_length( m_buffer.size() )
	{
	}

	CharT const* c_str() const
	{ 
		return m_text; 
	}
 
	size_type length() const { return m_length; }

#ifdef HAS_MOVE_SEMANTICS

#ifdef CHECK_BACKWARD_COMPATIBILITY
private:
	// Following constructors are not allowed before we have C++11 support on all target platforms
	// (r-value string conversion must be performed within the same expression)
	template <typename CT, typename T>
	friend converter<CT> convert( T&& text );
#endif
	converter( this_type&& rhs )
	: m_buffer( std::move( rhs.m_buffer ) )
	, m_text( std::move( rhs.m_text ) )
	, m_length( std::move( rhs.m_length ) )
	{
	}
 
	converter( string_type&& text )
	: m_buffer( std::move( text ) )
	, m_text( m_buffer.c_str() )
	, m_length( text.size() )
	{
	}

 	template <class T>
	converter( std::basic_string<T>&& text )
		// here we are intentionally not moving as we need the conversion anyway
		: converter( text ) 
	{
	}

#endif // HAS_MOVE_SEMANTICS

private:  // make this class noncopyable
	converter( const converter& );
	const converter& operator=( converter const& );

private:
	string_type const m_buffer;
	char_type const* const m_text;
	size_type const m_length;
};

#ifdef CHECK_BACKWARD_COMPATIBILITY

template <typename CharT, typename T>
inline converter<CharT> convert( T&& text )
{
	return converter<CharT>( std::forward<T>( text ) ); 
} 

#else // CHECK_BACKWARD_COMPATIBILITY

#ifdef HAS_TEMPLATE_TYPEDEF

template <typename CharT>
using convert = converter<CharT>;

#else // HAS_TEMPLATE_TYPEDEF

// we can either use ugly preprocessor hack
//# define convert converter

// ... or do the constructor forwarding by hand
 
template <typename CharT>
class convert 
	: public converter<CharT>
{
	typedef converter<CharT> base_type;
public:
	using typename base_type::char_type;
	using typename base_type::size_type;
	using typename base_type::this_type;
	using typename base_type::string_type;

	convert( string_type const& text )
	: base_type( text )
	{
	}

	template <typename T>
	convert( std::basic_string<T> const& text )
		: base_type( text )
	{
	}

};

#  endif // HAS_TEMPLATE_TYPEDEF
#endif // CHECK_BACKWARD_COMPATIBILITY
 
#endif // __CONVERT_IMPL_HPP__
