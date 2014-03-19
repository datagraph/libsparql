/* This is free and unencumbered software released into the public domain. */

#include "catch.hpp"

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

static sparql::writer
make_writer(FILE* stream = stdout) {
  return sparql::writer(stream, "application/xml", "UTF-8");
}

TEST_CASE("test_ctor") {
  REQUIRE_NOTHROW(make_writer());
}
