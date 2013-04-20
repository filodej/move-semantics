#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#  define HAS_MOVE_SEMANTICS
#endif
 
#ifdef CHECK_BACKWARD_COMPATIBILITY 
#  ifdef HAS_MOVE_SEMANTICS
#    include "./convert_check.hpp"
#  else
#    error "We need C++11 move semantics for checking backward compatibility of convert<> calls"
#  endif 
#else
#  include "./convert_impl.hpp"
#endif 

#endif // __CONVERT_HPP__
