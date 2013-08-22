/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/csv.h"

#include <cassert>   /* for assert() */
#include <cstdio>    /* for std::fflush(), std::fput*() */
#include <cstring>   /* for std::strlen(), std::strpbrk() */
#include <stdexcept> /* for std::logic_error */

namespace {
  struct implementation : public sparql::writer::implementation {
    implementation(FILE* stream);
    virtual ~implementation() noexcept override;
    //virtual void begin() override;
    //virtual void finish() override;
    //virtual void begin_head() override;
    //virtual void finish_head() override;
    //virtual void begin_variables() override;
    virtual void finish_variables() override;
    virtual void write_variable(const char* name) override;
    virtual void write_boolean(bool value) override;
    //virtual void begin_results() override;
    //virtual void finish_results() override;
    //virtual void begin_result() override;
    virtual void finish_result() override;
    virtual void omit_binding(const char* name) override;
    virtual void begin_binding(const char* name) override;
    virtual void finish_binding() override;
    virtual void write_uri_reference(const char* string) override;
    virtual void write_blank_node(const char* string) override;
    virtual void write_plain_literal(const char* string, const char* language) override;
    virtual void write_typed_literal(const char* string, const char* datatype) override;
    virtual void flush() override;
  protected:
    void write_field(const char* string);
    void finish_record();
  private:
    FILE* _stream = nullptr;
  };
}

sparql::writer::implementation*
sparql_writer_for_csv(FILE* const stream,
                      const char* const content_type,
                      const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream);
}

implementation::implementation(FILE* const stream)
  : _stream(stream) {
  assert(stream != nullptr);
}

implementation::~implementation() noexcept {}

void
implementation::finish_variables() {
  finish_record();
}

void
implementation::write_variable(const char* const name) {
  if (_variable_count) {
    std::fputc(',', _stream);
  }

  std::fputs(name, _stream);

  _variable_count++;
}

void
implementation::write_boolean(const bool value) {
  (void)value; /* ignored */

  throw std::logic_error("boolean output not supported");
}

void
implementation::finish_result() {
  finish_record();
}

void
implementation::omit_binding(const char* const name) {
  begin_binding(name);
}

void
implementation::begin_binding(const char* const name) {
  (void)name; /* ignored */

  if (_binding_count) {
    std::fputc(',', _stream);
  }

  _binding_count++;
}

void
implementation::finish_binding() {
  // TODO
}

void
implementation::write_uri_reference(const char* const string) {
  write_field(string);
}

void
implementation::write_blank_node(const char* const string) {
  std::fputs("_:", _stream);
  write_field(string);
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  (void)language; /* omitted */

  write_field(string);
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  (void)datatype; /* omitted */

  write_field(string);
}

void
implementation::flush() {
  std::fflush(_stream);
}

void
implementation::write_field(const char* string) {
  if (!std::strpbrk(string, ",\n\r\"")) {
    std::fputs(string, _stream); /* the simple case */
    return;
  }

  std::fputc('"', _stream);
  for (std::size_t index = 0; index < std::strlen(string); index++) {
    const char c = string[index];
    switch (c) {
      case '"':
        std::fputc('"', _stream);
        /* fall through */
      default:
        std::fputc(c, _stream);
        break;
    }
  }
  std::fputc('"', _stream);
}

void
implementation::finish_record() {
  std::fputs("\r\n", _stream); /* CRLF */
}
