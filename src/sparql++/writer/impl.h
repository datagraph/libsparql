/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_IMPL_H
#define SPARQLXX_WRITER_IMPL_H

#include "sparql++/writer.h"

class sparql::writer::implementation : private boost::noncopyable {
public:
  static writer::implementation* create(
    const std::string& file_path,
    const std::string& content_type,
    const std::string& charset);

  static writer::implementation* create(
    std::ostream& stream,
    const std::string& content_type,
    const std::string& charset);

  static writer::implementation* create(
    FILE* stream,
    const std::string& content_type,
    const std::string& charset);

  virtual ~implementation() {}

  virtual void begin() = 0;

  virtual void finish() = 0;

  virtual void flush() = 0;

protected:
  implementation() {}
};

#endif /* SPARQLXX_WRITER_IMPL_H */
