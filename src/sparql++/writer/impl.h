/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_IMPL_H
#define SPARQLXX_WRITER_IMPL_H

#include "sparql++/writer.h"

struct sparql::writer::implementation : private boost::noncopyable {
public:
  virtual ~implementation() {}

  virtual void begin() = 0;

  virtual void finish() = 0;

  virtual void flush() = 0;

protected:
  implementation() {}
};

#endif /* SPARQLXX_WRITER_IMPL_H */
