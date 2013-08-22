/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer_brtr
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

static sparql::writer
make_writer(FILE* stream = stdout) {
  return sparql::writer(stream, "application/x-binary-rdf-results-table", "UTF-8");
}

BOOST_AUTO_TEST_CASE(test_ctor) {
  BOOST_CHECK_NO_THROW(make_writer());
}
