/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_FORMAT_H
#define SPARQLXX_FORMAT_H

namespace sparql {
  struct format {
    const char* const content_type;
    const char* const charset;
    const char* const file_extension;
    const char* const module_name;
  };
}

#endif /* SPARQLXX_FORMAT_H */
