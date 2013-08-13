/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/csv.h"

#include <cassert> /* for assert() */

namespace {
  struct implementation : public sparql::writer::implementation {
  public:
    implementation(FILE* stream);
    virtual ~implementation() override;
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
    virtual void write_binding(const char* name, ...) override; // TODO
    virtual void flush() override;
  };
}

sparql::writer::implementation*
sparql_writer_for_csv(FILE* const stream,
                      const char* const content_type,
                      const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream); // TODO
}

implementation::implementation(FILE* const stream) {
  assert(stream != nullptr);
  (void)stream; // TODO
}

implementation::~implementation() {
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
implementation::write_binding(const char* const name, ...) {
  (void)name; // TODO
}

void
implementation::flush() {
  // TODO
}
