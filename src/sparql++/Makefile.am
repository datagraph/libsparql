lib_LTLIBRARIES = libsparql++.la

libsparql___la_LIBADD = $(top_srcdir)/lib/librfcjson.la

libsparql___la_SOURCES =  \
  extern.cc               \
  feature.cc              \
  format.cc               \
  module.cc               \
  version.cc              \
  writer.cc

base_pkgincludedir = $(includedir)/sparql++

base_pkginclude_HEADERS = \
  extern.h                \
  feature.h               \
  format.h                \
  module.h                \
  version.h               \
  writer.h

if !DISABLE_BOOL
  libsparql___la_SOURCES += writer/bool.cc
endif

if !DISABLE_BRTR
  libsparql___la_SOURCES += writer/brtr.cc
endif

if !DISABLE_CSV
  libsparql___la_SOURCES += writer/csv.cc
endif

if !DISABLE_JSON
  libsparql___la_SOURCES += writer/json.cc
endif

if !DISABLE_SSE
  libsparql___la_SOURCES += writer/sse.cc
endif

if !DISABLE_TSV
  libsparql___la_SOURCES += writer/tsv.cc
endif

if !DISABLE_XML
  AM_CPPFLAGS += $(libxml2_CFLAGS)
  libsparql___la_LIBADD += $(libxml2_LIBS)
  libsparql___la_SOURCES += writer/xml.cc
endif

if !DISABLE_XSLT
  libsparql___la_SOURCES += writer/xslt.cc
endif
