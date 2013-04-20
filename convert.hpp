#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#  define HAS_MOVE_SEMANTICS
#  define HAS_TEMPLATE_TYPEDEF
#endif
 
#if defined( CHECK_BACKWARD_COMPATIBILITY ) and !defined( HAS_MOVE_SEMANTICS )
#  error "We need C++11 move semantics for checking backward compatibility of convert<> calls"
#endif 

#include "./convert_impl.hpp"

#endif // __CONVERT_HPP__
