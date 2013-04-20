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

	convert()
		: m_text(0)
		, m_length(0)
	{
	}

	this_type const& operator()( string_type const& text ) const
	{
		m_text = text.c_str();
		m_length = text.size();
		return *this;
	}

	template <class T>
	this_type const& operator()( std::basic_string<T> const& text ) const
	{
		m_buffer = do_conversion( text.c_str(), text.size() );
	 	m_text = m_buffer.c_str();
	 	m_length = m_buffer.size();
		return *this;
	}

#ifdef HAS_MOVE_SEMANTICS

	this_type const& operator()( string_type&& text ) &&
	{
		m_buffer = std::move( text );
		m_text = m_buffer.c_str();
		m_length = text.size();
		return *this;
	}

	this_type const& operator()( string_type&& ) const&
	{
	 	// This is not allowed before we have C++11 support on all target platforms
	 	// (r-value string conversion must be performed within the same expression)
		//return *this;
	}

	template <class T>
	this_type const& operator()( std::basic_string<T>&& text ) &&
	{
		m_buffer = do_conversion( text.c_str(), text.size() );
	 	m_text = m_buffer.c_str();
	 	m_length = m_buffer.size();
		return *this;
	}

	template <class T>
	this_type const& operator()( std::basic_string<T>&& ) const&
	{
	 	// This is not allowed before we have C++11 support on all target platforms
	 	// (r-value string conversion must be performed within the same expression)
		//return *this;
	}

#endif

	size_type length() const { return m_length; }

	CharT const* c_str() const
	{ 
		return m_text; 
	}

private:
	mutable string_type m_buffer;
	mutable char_type const* m_text;
	mutable size_type m_length;
};
 
#endif // __CONVERT_IMPL_HPP__
