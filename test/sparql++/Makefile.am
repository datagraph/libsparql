AM_CPPFLAGS += $(TEST_CPPFLAGS)
AM_CXXFLAGS += $(TEST_CXXFLAGS)
AM_LDFLAGS  += $(TEST_LDFLAGS)

LDADD = $(top_srcdir)/src/sparql++/libsparql++.la

check_PROGRAMS = \
  check_feature  \
  check_format   \
  check_module   \
  check_version  \
  check_writer

TESTS = $(check_PROGRAMS)

AM_DEFAULT_SOURCE_EXT = .cc
