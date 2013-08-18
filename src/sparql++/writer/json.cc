/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/json.h"

#include <cassert> /* for assert() */
#include <cstring> /* for std::strlen() */

#include "rfc/json/json_writer.h"

using namespace rfc4627;

namespace {
  struct implementation : public sparql::writer::implementation {
    implementation(FILE* stream);
    virtual ~implementation() noexcept override;
    virtual void begin() override;
    virtual void finish() override;
    virtual void begin_head() override;
    virtual void finish_head() override;
    virtual void begin_variables() override;
    virtual void finish_variables() override;
    virtual void write_variable(const char* name) override;
    virtual void write_link(const char* href) override;
    virtual void write_boolean(bool value) override;
    virtual void begin_results() override;
    virtual void finish_results() override;
    virtual void begin_result() override;
    virtual void finish_result() override;
    virtual void begin_binding(const char* name) override;
    virtual void finish_binding() override;
    virtual void write_uri_reference(const char* string) override;
    virtual void write_blank_node(const char* string) override;
    virtual void write_plain_literal(const char* string, const char* language) override;
    virtual void write_typed_literal(const char* string, const char* datatype) override;
    virtual void flush() override;
  private:
    json_writer _json;
  };
}

sparql::writer::implementation*
sparql_writer_for_json(FILE* const stream,
                       const char* const content_type,
                       const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream);
}

implementation::implementation(FILE* const stream)
  : _json(stream) {
  assert(stream != nullptr);
}

implementation::~implementation() noexcept {}

void
implementation::begin() {
  _json.begin_object();
}

void
implementation::finish() {
  _json.finish_object();
}

void
implementation::begin_head() {
  _json.write_string("head");
  _json.begin_object();
}

void
implementation::finish_head() {
  _json.finish_object();
}

void
implementation::begin_variables() {
  _json.write_string("vars");
  _json.begin_array();
}

void
implementation::finish_variables() {
  _json.finish_array();
}

void
implementation::write_variable(const char* const name) {
  _json.write_string(name);
}

void
implementation::write_link(const char* const href) {
  _json.write_string("link");
  _json.begin_array();
  _json.write_string(href);
  _json.finish_array();
}

void
implementation::write_boolean(const bool value) {
  _json.write_string("boolean");
  _json.write_boolean(value);
}

void
implementation::begin_results() {
  _json.write_string("results");
  _json.begin_object();
  _json.write_string("bindings");
  _json.begin_array();
}

void
implementation::finish_results() {
  _json.finish_array();
  _json.finish_object();
}

void
implementation::begin_result() {
  _json.begin_object();
}

void
implementation::finish_result() {
  _json.finish_object();
}

void
implementation::begin_binding(const char* const name) {
  _json.write_string(name);
  _json.begin_object();
}

void
implementation::finish_binding() {
  _json.finish_object();
}

void
implementation::write_uri_reference(const char* const string) {
  _json.begin_object();
  _json.write_strings("type", "uri");
  _json.write_strings("value", string);
  _json.finish_object();
}

void
implementation::write_blank_node(const char* const string) {
  _json.begin_object();
  _json.write_strings("type", "bnode");
  _json.write_strings("value", string);
  _json.finish_object();
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  _json.begin_object();
  _json.write_strings("type", "literal");
  _json.write_strings("value", string);
  if (language != nullptr) {
    _json.write_strings("xml:lang", language);
  }
  _json.finish_object();
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  _json.begin_object();
  _json.write_strings("type", "literal"); // TODO: support also for SPARQL 1.0's "typed-literal"
  _json.write_strings("value", string);
  _json.write_strings("datatype", datatype);
  _json.finish_object();
}

void
implementation::flush() {
  _json.flush();
}
