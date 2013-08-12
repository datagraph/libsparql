/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer_tsv
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

BOOST_AUTO_TEST_CASE(test_ctor) {
  sparql::writer writer(stdout, "text/tab-separated-values", "UTF-8");
  BOOST_CHECK(true); // TODO
}
