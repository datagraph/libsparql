/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_IMPL_H
#define SPARQLXX_WRITER_IMPL_H

#include "sparql++/writer.h"

#include <boost/noncopyable.hpp>

struct sparql::writer::implementation : private boost::noncopyable {
protected:
  implementation() noexcept {}

public:
  virtual ~implementation() noexcept {}

  virtual void begin() = 0;

  virtual void finish() = 0;

  virtual void begin_head() = 0;

  virtual void finish_head() = 0;

  virtual void begin_variables() = 0;

  virtual void finish_variables() = 0;

  virtual void write_variable(const char* name) = 0;

  virtual void write_link(const char* href) { (void)href; }

  virtual void write_boolean(bool value) = 0;

  virtual void begin_results() = 0;

  virtual void finish_results() = 0;

  virtual void begin_result() = 0;

  virtual void finish_result() = 0;

  virtual void write_binding(const char* name, ...) = 0; // TODO

  virtual void flush() = 0;
};

#endif /* SPARQLXX_WRITER_IMPL_H */
