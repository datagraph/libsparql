/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer.h"
#include "sparql++/writer/impl.h"

#ifndef DISABLE_BOOL
#include "sparql++/writer/bool.h"
#endif

#ifndef DISABLE_BRTR
#include "sparql++/writer/brtr.h"
#endif

#ifndef DISABLE_CSV
#include "sparql++/writer/csv.h"
#endif

#ifndef DISABLE_JSON
#include "sparql++/writer/json.h"
#endif

#ifndef DISABLE_SSE
#include "sparql++/writer/sse.h"
#endif

#ifndef DISABLE_TSV
#include "sparql++/writer/tsv.h"
#endif

#ifndef DISABLE_XML
#include "sparql++/writer/xml.h"
#endif

#ifndef DISABLE_XSLT
#include "sparql++/writer/xslt.h"
#endif

#include <cassert>   /* for assert() */
#include <stdexcept> /* for std::invalid_argument */

using namespace sparql;

static writer::implementation*
sparql_writer_for(FILE* stream,
                  const std::string& content_type,
                  const std::string& charset) {
  (void)stream, (void)content_type, (void)charset;

#ifndef DISABLE_BOOL
  if (content_type.compare("text/boolean") == 0) {
    return sparql_writer_for_bool(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_BRTR
  if (content_type.compare("application/x-binary-rdf-results-table") == 0) {
    return sparql_writer_for_brtr(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_CSV
  if (content_type.compare("text/csv") == 0) {
    return sparql_writer_for_csv(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_JSON
  if (content_type.compare("application/sparql-results+json") == 0) {
    return sparql_writer_for_json(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_SSE
  if (content_type.compare("application/sparql-results+sse") == 0) {
    return sparql_writer_for_sse(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_TSV
  if (content_type.compare("text/tab-separated-values") == 0) {
    return sparql_writer_for_tsv(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_XML
  if (content_type.compare("application/sparql-results+xml") == 0) {
    return sparql_writer_for_xml(stream, content_type.c_str(), charset.c_str());
  }
#endif

#ifndef DISABLE_XSLT
  if (content_type.compare("application/xslt+xml") == 0) {
    return sparql_writer_for_xslt(stream, content_type.c_str(), charset.c_str());
  }
#endif

  return nullptr;
}

writer::writer(const std::string& file_path,
               const std::string& content_type,
               const std::string& charset) {
  (void)file_path, (void)content_type, (void)charset; // TODO
}

writer::writer(std::ostream& stream,
               const std::string& content_type,
               const std::string& charset) {
  (void)stream, (void)content_type, (void)charset; // TODO
}

writer::writer(FILE* const stream,
               const std::string& content_type,
               const std::string& charset)
  : _implementation(sparql_writer_for(stream, content_type, charset)) {
  if (!_implementation) {
    throw std::invalid_argument("unknown content type: " + content_type);
  }
}

writer::~writer() = default;

void
writer::begin() {
  assert(_implementation != nullptr);
  _implementation->begin();
}

void
writer::finish() {
  assert(_implementation != nullptr);
  _implementation->finish();
}

void
writer::flush() {
  assert(_implementation != nullptr);
  _implementation->flush();
}
