/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer_xml
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

BOOST_AUTO_TEST_CASE(test_ctor) {
  sparql::writer writer(stdout, "application/sparql-results+xml", "UTF-8");
  writer.begin();
  writer.finish();
  BOOST_CHECK(true); // TODO
}
