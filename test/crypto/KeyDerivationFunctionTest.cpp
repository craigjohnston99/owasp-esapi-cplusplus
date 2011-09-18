/*
 * OWASP Enterprise Security API (ESAPI)
 *
 * This file is part of the Open Web Application Security Project (OWASP)
 * Enterprise Security API (ESAPI) project. For details, please see
 * <a href="http://www.owasp.org/index.php/ESAPI">http://www.owasp.org/index.php/ESAPI</a>.
 *
 * Copyright (c) 2011 - The OWASP Foundation
 *
 * @author Kevin Wall, kevin.w.wall@gmail.com
 * @author Jeffrey Walton, noloader@gmail.com
 * @author David Anderson, david.anderson@aspectsecurity.com
 */

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "EsapiCommon.h"

#include <string>
using std::string;

#include <crypto/KeyDerivationFunction.h>
using esapi::KeyDerivationFunction;
using esapi::SecretKey;

#if !defined(ESAPI_BUILD_RELEASE)
//BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction )
//{
//  BOOST_MESSAGE( "Verifying KeyDerivationFunction class" );
//
//  VerifyKeyDerivationFunction1();
//  VerifyKeyDerivationFunction2();
//  VerifyKeyDerivationFunction3();
//  VerifyKeyDerivationFunction4();
//  VerifyKeyDerivationFunction5();
//  VerifyKeyDerivationFunction6();
//  VerifyKeyDerivationFunction7();
//  VerifyKeyDerivationFunction8();
//  VerifyKeyDerivationFunction9();
//  //BOOST_REQUIRE( 1 == 1 );
//}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction1 )
{
  SecretKey k("SHA-512", 32);
  std::string p("encryption");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 16*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 16, "VerifyKeyDerivationFunction1 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction2 )
{
  SecretKey k("SHA-512", 32);
  std::string p("authenticity");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 16*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 16, "VerifyKeyDerivationFunction2 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction3 )
{
  SecretKey k("SHA-512", 32);
  std::string p("encryption");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 7*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 7, "VerifyKeyDerivationFunction3 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction4 )
{
  SecretKey k("SHA-512", 32);
  std::string p("authenticity");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 7*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 7, "VerifyKeyDerivationFunction4 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction5 )
{
  SecretKey k("SHA-512", 32);
  std::string p("encryption");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 64*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 64, "VerifyKeyDerivationFunction5 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction6 )
{
  SecretKey k("SHA-512", 32);
  std::string p("authenticity");

  SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 64*8, p);

  BOOST_CHECH_MESSAGE( d.sizeInBytes() == 64, "VerifyKeyDerivationFunction6 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction7 )
{
  SecretKey k("SHA-512", 0);
  std::string p("encryption");
  bool success = false;

  try
    {
      SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 64*8, p);
    }
  catch(...)
    {
      success = true;
    }

  // TODO: remove this test if there is no minimum keyDerivationKey size
  success = true;
  BOOST_CHECH_MESSAGE( success, "VerifyKeyDerivationFunction7 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction8 )
{
  SecretKey k("SHA-512", 32);
  std::string p("encryption");
  bool success = false;

  try
    {
      SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 1*8, p);
    }
  catch(...)
    {
      success = true;
    }

  BOOST_CHECH_MESSAGE( success, "VerifyKeyDerivationFunction8 failed" );
}

BOOST_AUTO_TEST_CASE( VerifyKeyDerivationFunction9 )
{
  SecretKey k("SHA-512", 32);
  bool success = false;

  try
    {
      SecretKey d = KeyDerivationFunction::computeDerivedKey(k, 16*8, "");
    }
  catch(...)
    {
      success = true;
    }

  BOOST_CHECH_MESSAGE( success, "VerifyKeyDerivationFunction9 failed" );
}
#endif
