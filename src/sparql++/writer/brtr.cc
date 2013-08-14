/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/brtr.h"

#include <cassert> /* for assert() */

namespace {
  struct implementation : public sparql::writer::implementation {
  public:
    implementation(FILE* stream);
    virtual ~implementation() noexcept override;
    virtual void begin() override;
    virtual void finish() override;
    virtual void begin_head() override;
    virtual void finish_head() override;
    virtual void begin_variables() override;
    virtual void finish_variables() override;
    virtual void write_variable(const char* name) override;
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
  };
}

sparql::writer::implementation*
sparql_writer_for_brtr(FILE* const stream,
                       const char* const content_type,
                       const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream); // TODO
}

implementation::implementation(FILE* const stream) {
  assert(stream != nullptr);
  (void)stream; // TODO
}

implementation::~implementation() noexcept {
  // TODO
}

void
implementation::begin() {
  // TODO
}

void
implementation::finish() {
  // TODO
}

void
implementation::begin_head() {
  // TODO
}

void
implementation::finish_head() {
  // TODO
}

void
implementation::begin_variables() {
  // TODO
}

void
implementation::finish_variables() {
  // TODO
}

void
implementation::write_variable(const char* const name) {
  (void)name; // TODO
}

void
implementation::write_boolean(const bool value) {
  (void)value; // TODO
}

void
implementation::begin_results() {
  // TODO
}

void
implementation::finish_results() {
  // TODO
}

void
implementation::begin_result() {
  // TODO
}

void
implementation::finish_result() {
  // TODO
}

void
implementation::begin_binding(const char* const name) {
  (void)name; // TODO
}

void
implementation::finish_binding() {
  // TODO
}

void
implementation::write_uri_reference(const char* const string) {
  (void)string; // TODO
}

void
implementation::write_blank_node(const char* const string) {
  (void)string; // TODO
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  (void)string, (void)language; // TODO
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  (void)string, (void)datatype; // TODO
}

void
implementation::flush() {
  // TODO
}
