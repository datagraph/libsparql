/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE writer_tsv
#include <boost/test/unit_test.hpp>

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

static sparql::writer
make_writer() {
  return sparql::writer(stdout, "text/tab-separated-values", "UTF-8");
}

BOOST_AUTO_TEST_CASE(test_ctor) {
  make_writer();
}

#if 0
BOOST_AUTO_TEST_CASE(test_boolean) {
  auto writer = make_writer();
  write_boolean(writer);
  // TODO
}
#endif

BOOST_AUTO_TEST_CASE(test_bindings) {
  auto writer = make_writer();
  write_bindings(writer);
  // TODO
}
