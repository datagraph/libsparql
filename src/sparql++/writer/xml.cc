/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/xml.h"

#include "xml_writer.h"

#include <cassert>   /* for assert() */
#include <stdexcept> /* for std::runtime_error */

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
    virtual void flush() override { _xml.flush(); }

  private:
    xml_writer _xml;
  };
}

sparql::writer::implementation*
sparql_writer_for_xml(FILE* const stream,
                      const char* const content_type,
                      const char* const charset) {
  (void)content_type, (void)charset; /* unused */
  return new implementation(stream);
}

implementation::implementation(FILE* const stream)
  : _xml(stream) {
  assert(stream != nullptr);
}

implementation::~implementation() noexcept {}

void
implementation::begin() {
  _xml.set_indent(2);

  /* <?xml version="1.0" encoding="UTF-8"?> */
  _xml.begin_document();

  /* <sparql xmlns="http://www.w3.org/2005/sparql-results#"> */
  _xml.begin_element_with_ns("sparql", "http://www.w3.org/2005/sparql-results#");
}

void
implementation::finish() {
  _xml.finish_element(true); /* </sparql> */

  _xml.finish_document(); /* EOF */
}

void
implementation::begin_head() {
  _xml.begin_element("head");
}

void
implementation::finish_head() {
  _xml.finish_element(); /* </head> */
}

void
implementation::begin_variables() {
  /* nothing to do */
}

void
implementation::finish_variables() {
  /* nothing to do */
}

void
implementation::write_variable(const char* const name) {
  _xml.begin_element("variable");
  _xml.write_attribute("name", name);
  _xml.finish_element();
}

void
implementation::write_link(const char* const href) {
  _xml.begin_element("link");
  _xml.write_attribute("href", href);
  _xml.finish_element();
}

void
implementation::write_boolean(const bool value) {
  _xml.write_element("boolean", value ? "true" : "false");
}

void
implementation::begin_results() {
  _xml.begin_element("results");
}

void
implementation::finish_results() {
  _xml.finish_element(true); /* </results> */
}

void
implementation::begin_result() {
  _xml.begin_element("result");
}

void
implementation::finish_result() {
  _xml.finish_element(true); /* </result> */
}

void
implementation::begin_binding(const char* const name) {
  _xml.begin_element("binding");
  _xml.write_attribute("name", name);
}

void
implementation::finish_binding() {
  _xml.finish_element(true);
}

void
implementation::write_uri_reference(const char* const string) {
  _xml.begin_element("uri");
  _xml.write_text(string);
  _xml.finish_element(true);
}

void
implementation::write_blank_node(const char* const string) {
  _xml.begin_element("bnode");
  _xml.write_text(string);
  _xml.finish_element(true);
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  _xml.begin_element("literal");
  if (language) {
    _xml.write_attribute("xml:lang", language);
  }
  _xml.write_text(string);
  _xml.finish_element(true);
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  _xml.begin_element("literal");
  _xml.write_attribute("datatype", datatype);
  _xml.write_text(string);
  _xml.finish_element(true);
}
