/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <sparql++/writer.h> /* for sparql::writer */

#include "check_writer.h"

TEST_CASE("test_ctor") {
  REQUIRE_NOTHROW(sparql::writer(stdout, "text/boolean", "UTF-8"));
}
