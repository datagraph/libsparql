/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_IMPL_H
#define SPARQLXX_WRITER_IMPL_H

#include "sparql++/writer.h"

#include <boost/noncopyable.hpp>

struct sparql::writer::implementation : private boost::noncopyable {
  std::size_t _variable_count = 0;
  std::size_t _binding_count = 0;

protected:
  implementation() noexcept {}

public:
  virtual ~implementation() noexcept {}

  virtual void begin() {}

  virtual void finish() {}

  virtual void begin_head() {}

  virtual void finish_head() {}

  virtual void begin_variables() {}

  virtual void finish_variables() {}

  virtual void write_variable(const char* name) { (void)name; }

  virtual void write_link(const char* href) { (void)href; }

  virtual void write_boolean(bool value) { (void)value; }

  virtual void begin_results() {}

  virtual void finish_results() {}

  virtual void begin_result() {}

  virtual void finish_result() {}

  virtual void omit_binding(const char* name) { (void)name; }

  virtual void begin_binding(const char* name) { (void)name; }

  virtual void finish_binding() {}

  virtual void write_uri_reference(const char* string) { (void)string; }

  virtual void write_blank_node(const char* string) { (void)string; }

  virtual void write_plain_literal(const char* string, const char* language) {
    (void)string, (void)language;
  }

  virtual void write_typed_literal(const char* string, const char* datatype) {
    (void)string, (void)datatype;
  }

  virtual void write_comment(const char* comment) { (void)comment; }

  virtual void flush() {}
};

#endif /* SPARQLXX_WRITER_IMPL_H */
