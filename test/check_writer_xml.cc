/* This is free and unencumbered software released into the public domain. */

#include "catch.hpp"

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

static sparql::writer
make_writer(FILE* stream = stdout) {
  return sparql::writer(stream, "application/sparql-results+xml", "UTF-8");
}

TEST_CASE("test_ctor") {
  REQUIRE_NOTHROW(make_writer());
}

TEST_CASE("test_boolean") {
  const auto output = with_captured_output([](FILE* output) {
    auto writer = make_writer(output);
    write_boolean(writer);
  });
  REQUIRE(output == read_file("fixtures/boolean.srx"));
}

TEST_CASE("test_bindings") {
  const auto output = with_captured_output([](FILE* output) {
    auto writer = make_writer(output);
    write_bindings(writer);
  });
  REQUIRE(output == read_file("fixtures/bindings.srx"));
}
