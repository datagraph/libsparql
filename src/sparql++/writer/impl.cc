/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/impl.h"

using namespace sparql;

writer::implementation*
writer::implementation::create(const std::string& file_path,
                               const std::string& content_type,
                               const std::string& charset) {
  return (void)file_path, (void)content_type, (void)charset, nullptr; // TODO
}

writer::implementation*
writer::implementation::create(std::ostream& stream,
                               const std::string& content_type,
                               const std::string& charset) {
  return (void)stream, (void)content_type, (void)charset, nullptr; // TODO
}

writer::implementation*
writer::implementation::create(FILE* const stream,
                               const std::string& content_type,
                               const std::string& charset) {
  return (void)stream, (void)content_type, (void)charset, nullptr; // TODO
}
