/* This is free and unencumbered software released into the public domain. */

#include "catch.hpp"

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

TEST_CASE("test_ctor") {
  REQUIRE_NOTHROW(sparql::writer(stdout, "text/boolean", "UTF-8"));
}
