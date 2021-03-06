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

#include "sparql++/format.h"

#include <cassert>   /* for assert() */
#include <cstdlib>   /* for std::abort() */
#include <cstring>   /* for std::strcmp() */
#include <stdexcept> /* for std::invalid_argument */

using namespace sparql;

static writer::implementation*
sparql_writer_for(FILE* const stream,
                  const char* const content_type,
                  const char* const charset) {
  const format* const format = format::find_by_content_type(content_type);
  if (format == nullptr) {
    return nullptr; /* unknown content type */
  }
  assert(format->module_name != nullptr);

#ifndef DISABLE_BOOL
  if (std::strcmp("bool", format->module_name) == 0) {
    return sparql_writer_for_bool(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_BRTR
  if (std::strcmp("brtr", format->module_name) == 0) {
    return sparql_writer_for_brtr(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_CSV
  if (std::strcmp("csv", format->module_name) == 0) {
    return sparql_writer_for_csv(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_JSON
  if (std::strcmp("json", format->module_name) == 0) {
    return sparql_writer_for_json(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_SSE
  if (std::strcmp("sse", format->module_name) == 0) {
    return sparql_writer_for_sse(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_TSV
  if (std::strcmp("tsv", format->module_name) == 0) {
    return sparql_writer_for_tsv(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_XML
  if (std::strcmp("xml", format->module_name) == 0) {
    return sparql_writer_for_xml(stream, content_type, charset);
  }
#endif

#ifndef DISABLE_XSLT
  if (std::strcmp("xslt", format->module_name) == 0) {
    return sparql_writer_for_xslt(stream, content_type, charset);
  }
#endif

  (void)stream, (void)charset;
  return std::abort(), nullptr; /* never reached */
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
  : _implementation(sparql_writer_for(stream, content_type.c_str(), charset.c_str())) {
  if (!_implementation) {
    throw std::invalid_argument("unknown content type: " + content_type);
  }
}

writer::writer(writer&& other) noexcept {
  std::swap(_implementation, other._implementation);
}

writer::~writer() noexcept = default;

writer&
writer::operator=(writer&& other) noexcept {
  std::swap(_implementation, other._implementation);
  return *this;
}

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
writer::write_head() {
  begin_head();
  finish_head();
}

void
writer::begin_head() {
  assert(_implementation != nullptr);
  _implementation->begin_head();
}

void
writer::finish_head() {
  assert(_implementation != nullptr);
  _implementation->finish_head();
}

void
writer::write_variables(const std::vector<std::string>& names) {
  begin_variables();
  for (const auto& name : names) {
    write_variable(name);
  }
  finish_variables();
}

void
writer::begin_variables() {
  assert(_implementation != nullptr);
  _implementation->begin_variables();
}

void
writer::finish_variables() {
  assert(_implementation != nullptr);
  _implementation->finish_variables();
}

void
writer::write_variable(const char* const name) {
  assert(_implementation != nullptr);
  _implementation->write_variable(name);
}

void
writer::write_link(const char* const href) {
  assert(_implementation != nullptr);
  _implementation->write_link(href);
}

void
writer::write_boolean(const bool value) {
  assert(_implementation != nullptr);
  _implementation->write_boolean(value);
}

void
writer::begin_results() {
  assert(_implementation != nullptr);
  _implementation->begin_results();
}

void
writer::finish_results() {
  assert(_implementation != nullptr);
  _implementation->finish_results();
}

void
writer::begin_result() {
  assert(_implementation != nullptr);
  _implementation->begin_result();
}

void
writer::finish_result() {
  assert(_implementation != nullptr);
  _implementation->finish_result();
}

void
writer::omit_binding(const char* const name) {
  assert(_implementation != nullptr);
  _implementation->omit_binding(name);
}

void
writer::begin_binding(const char* const name) {
  assert(_implementation != nullptr);
  _implementation->begin_binding(name);
}

void
writer::finish_binding() {
  assert(_implementation != nullptr);
  _implementation->finish_binding();
}

void
writer::write_uri_reference(const char* const string) {
  assert(_implementation != nullptr);
  _implementation->write_uri_reference(string);
}

void
writer::write_blank_node(const char* const string) {
  assert(_implementation != nullptr);
  _implementation->write_blank_node(string);
}

void
writer::write_plain_literal(const char* const string,
                            const char* const language) {
  assert(_implementation != nullptr);
  _implementation->write_plain_literal(string, language);
}

void
writer::write_typed_literal(const char* const string,
                            const char* const datatype) {
  assert(_implementation != nullptr);
  _implementation->write_typed_literal(string, datatype);
}

void
writer::write_comment(const char* const comment) {
  assert(_implementation != nullptr);
  _implementation->write_comment(comment);
}

void
writer::flush() {
  assert(_implementation != nullptr);
  _implementation->flush();
}
