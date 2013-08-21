/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/bool.h"

#include <cassert> /* for assert() */
#include <cstdio>  /* for std::fflush(), std::fputs() */

namespace {
  struct implementation : public sparql::writer::implementation {
    implementation(FILE* stream);
    virtual ~implementation() noexcept override;
    virtual void write_boolean(bool value) override;
    virtual void flush() override;
  private:
    FILE* _stream = nullptr;
  };
}

sparql::writer::implementation*
sparql_writer_for_bool(FILE* const stream,
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
implementation::write_boolean(const bool value) {
  std::fputs(value ? "true\n" : "false\n", _stream);
}

void
implementation::flush() {
  std::fflush(_stream);
}
