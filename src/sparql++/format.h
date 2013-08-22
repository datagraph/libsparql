/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_FORMAT_H
#define SPARQLXX_FORMAT_H

#include <string> /* for std::string */

namespace sparql {
  struct format {
    const char* const content_type;
    const char* const charset;
    const char* const file_extension;
    const char* const module_name;

    static inline bool supported(const std::string& content_type) {
      return supported(content_type.c_str());
    }

    static bool supported(const char* content_type);
  };
}

#endif /* SPARQLXX_FORMAT_H */
