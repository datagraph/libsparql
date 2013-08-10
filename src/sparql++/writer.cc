/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer.h"
#include "sparql++/writer/impl.h"

#include <cassert> /* for assert() */

using namespace sparql;

writer::writer(const std::string& file_path,
               const std::string& content_type,
               const std::string& charset)
  : _implementation(writer::implementation::create(
      file_path, content_type, charset)) {}

writer::writer(std::ostream& stream,
               const std::string& content_type,
               const std::string& charset)
  : _implementation(writer::implementation::create(
      stream, content_type, charset)) {}

writer::writer(FILE* const stream,
               const std::string& content_type,
               const std::string& charset)
  : _implementation(writer::implementation::create(
      stream, content_type, charset)) {}

writer::~writer() = default;

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
writer::flush() {
  assert(_implementation != nullptr);
  _implementation->flush();
}
