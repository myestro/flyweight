/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_DEFAULT_VALUE_POLICY_HPP
#define BOOST_FLYWEIGHT_DETAIL_DEFAULT_VALUE_POLICY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/flyweight/detail/perfect_fwd.hpp>
#include <boost/flyweight/detail/value_tag.hpp>

/* Default value policy: the key is the same as the value.
 */

namespace boost{

namespace flyweights{

namespace detail{

template<typename Value>
struct default_value_policy:value_marker
{
  typedef Value key_type;
  typedef Value value_type;

  struct rep_type
  {
  /* template ctors */

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)&&\
    BOOST_WORKAROUND(__GNUC__,<=3)&&(__GNUC_MINOR__<=4)

/* GCC 4.4.2 and prior seems to have a bug with the default ctor resulting
 * from the variadic template ctor below, as it fails to value-initialize x.
 */

   rep_type():x(){}
#endif

#define BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY(args) \
  :x(BOOST_FLYWEIGHT_FORWARD(args)){}

  BOOST_FLYWEIGHT_PERFECT_FWD(
    explicit rep_type,
    BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY)

#undef BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY

    rep_type(const rep_type& r):x(r.x){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    rep_type(rep_type&& r):x(std::move(r.x)){}
#endif

    operator const value_type&()const{return x;}

    value_type x;
  };

  static void construct_value(const rep_type&){}
  static void copy_value(const rep_type&){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  static void move_value(const rep_type&){}
#endif
};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif
