/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer_csv
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

static sparql::writer
make_writer(FILE* stream = stdout) {
  return sparql::writer(stream, "text/csv", "UTF-8");
}

BOOST_AUTO_TEST_CASE(test_ctor) {
  BOOST_CHECK_NO_THROW(make_writer());
}

BOOST_AUTO_TEST_CASE(test_bindings) {
  const auto output = with_captured_output([](FILE* output) {
    auto writer = make_writer(output);
    write_bindings(writer);
  });
  BOOST_CHECK_EQUAL(output, read_file("fixtures/bindings.csv"));
}
