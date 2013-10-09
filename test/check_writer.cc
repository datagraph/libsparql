/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

BOOST_AUTO_TEST_CASE(test_ctor) {
  BOOST_CHECK_NO_THROW(sparql::writer(stdout, "text/boolean", "UTF-8"));
}
