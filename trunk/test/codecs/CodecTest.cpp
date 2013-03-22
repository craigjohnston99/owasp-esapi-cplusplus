/*
 * OWASP Enterprise Security API (ESAPI)
 *
 * This file is part of the Open Web Application Security Project (OWASP)
 * Enterprise Security API (ESAPI) project. For details, please see
 * <a href="http://www.owasp.org/index.php/ESAPI">http://www.owasp.org/index.php/ESAPI</a>.
 *
 * Copyright (c) 2011 - The OWASP Foundation
 *
 * @author Dan Amodio, dan.amodio@aspectsecurity.com
 */

#include "EsapiCommon.h"

#if defined(ESAPI_OS_WINDOWS_STATIC)
// do not enable BOOST_TEST_DYN_LINK
#elif defined(ESAPI_OS_WINDOWS_DYNAMIC)
# define BOOST_TEST_DYN_LINK
#elif defined(ESAPI_OS_WINDOWS)
# error "For Windows, ESAPI_OS_WINDOWS_STATIC or ESAPI_OS_WINDOWS_DYNAMIC must be defined"
#else
# define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "EsapiCommon.h"
using esapi::Char;
using esapi::String;

#include "codecs/Codec.h"
using esapi::Codec;

#include <iostream>
#include <string>
#include <sstream>

BOOST_AUTO_TEST_CASE(CodecContainsCharacter)
{
  Codec codec;

  BOOST_CHECK(codec.containsCharacter('a',"asdf"));
  BOOST_CHECK(codec.containsCharacter('s',"asdf"));
  BOOST_CHECK(codec.containsCharacter('d',"asdf"));
  BOOST_CHECK(codec.containsCharacter('f',"asdf"));
  BOOST_CHECK(codec.containsCharacter('b',"asdf") == false);
  BOOST_CHECK(codec.containsCharacter(' ',"asdf") == false);
  BOOST_CHECK(codec.containsCharacter('\0',"asdf") == false);
  BOOST_CHECK(codec.containsCharacter(0,"") == false);

  BOOST_CHECK(codec.containsCharacter('a',(Char*)"asdf",4));
  BOOST_CHECK(codec.containsCharacter('f',(Char*)"asdf",4));
  BOOST_CHECK(codec.containsCharacter('b',(Char*)"asdf",4) == false);
  BOOST_CHECK(codec.containsCharacter(' ',(Char*)"asdf",4) == false);
  BOOST_CHECK(codec.containsCharacter('\0',(Char*)"asdf",4) == false);

  const Char charr[] = { 'a', 's', 'd', 'f' };
  BOOST_CHECK(codec.containsCharacter('a',charr,COUNTOF(charr)) == true); 
  BOOST_CHECK(codec.containsCharacter('s',charr,COUNTOF(charr)) == true); 
  BOOST_CHECK(codec.containsCharacter('d',charr,COUNTOF(charr)) == true); 
  BOOST_CHECK(codec.containsCharacter('f',charr,COUNTOF(charr)) == true);
  BOOST_CHECK(codec.containsCharacter('g',charr,COUNTOF(charr)) == false);
  BOOST_CHECK(codec.containsCharacter('a',NULL,COUNTOF(charr)) == false);
  BOOST_CHECK(codec.containsCharacter('a',charr,0) == false);
  BOOST_CHECK(codec.containsCharacter(0,0,0) == false);
}

BOOST_AUTO_TEST_CASE( CodecEncode )
{
  Codec codec;

  BOOST_CHECK(codec.encode("a",4,"asdf").compare("asdf")==0);
  BOOST_CHECK(codec.encode("",4,"asdf").compare("asdf")==0);
}

BOOST_AUTO_TEST_CASE( CodecToHex )
{
	Codec codec;

	BOOST_CHECK(codec.toHex('a')[0] == 0x61);
	BOOST_CHECK(codec.toHex('b')[0] == 0x62);
	BOOST_CHECK(codec.toHex('a')[0] != 0x62);
}

BOOST_AUTO_TEST_CASE( CodecToOctal )
{
	Codec codec;

	BOOST_CHECK(codec.toOctal('a')[0] == 0141);
	BOOST_CHECK(codec.toOctal('b')[0] == 0142);
	BOOST_CHECK(codec.toOctal('a')[0] != 0142);
}

BOOST_AUTO_TEST_CASE( CodecGetHexForNonAlphanumeric )
{
	Codec codec;

	//BOOST_CHECK(codec.getHexForNonAlphanumeric('!')[0] == 0x21);
	//BOOST_CHECK_MESSAGE(atoi(codec.getHexForNonAlphanumeric('!').c_str()) == 21, "getHexForNonAlphanumeric('!') == " << codec.getHexForNonAlphanumeric('!'));
	//BOOST_CHECK(atoi(codec.getHexForNonAlphanumeric('"').c_str()) == 22);
	BOOST_CHECK(codec.getHexForNonAlphanumeric('!')[0] != 22);

	//BOOST_CHECK(atoi(codec.getHexForNonAlphanumeric('a').c_str()) == 0);
}
