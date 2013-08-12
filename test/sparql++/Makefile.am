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

if !DISABLE_BOOL
  check_PROGRAMS += check_writer_bool
endif

if !DISABLE_BRTR
  check_PROGRAMS += check_writer_brtr
endif

if !DISABLE_CSV
  check_PROGRAMS += check_writer_csv
endif

if !DISABLE_JSON
  check_PROGRAMS += check_writer_json
endif

if !DISABLE_SSE
  check_PROGRAMS += check_writer_sse
endif

if !DISABLE_TSV
  check_PROGRAMS += check_writer_tsv
endif

if !DISABLE_XML
  check_PROGRAMS += check_writer_xml
endif

if !DISABLE_XSLT
  check_PROGRAMS += check_writer_xslt
endif

TESTS = $(check_PROGRAMS)

AM_DEFAULT_SOURCE_EXT = .cc
