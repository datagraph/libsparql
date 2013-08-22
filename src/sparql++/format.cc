/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/format.h"

#include <cassert> /* for assert() */
#include <cstring> /* for std::strcmp() */

using namespace sparql;

static const format sparql_format_info[] = {
#ifndef DISABLE_BOOL
  {"text/boolean",                           nullptr, "txt", "bool"},
#endif
#ifndef DISABLE_BRTR
  {"application/x-binary-rdf-results-table", nullptr, "brt", "brtr"},
#endif
#ifndef DISABLE_CSV
  {"text/csv",                               nullptr, "csv", "csv"},
#endif
#ifndef DISABLE_JSON
  {"application/sparql-results+json",        nullptr, "srj", "json"},
#endif
#ifndef DISABLE_SSE
  {"application/sparql-results+sse",         nullptr, "sse", "sse"},
#endif
#ifndef DISABLE_TSV
  {"text/tab-separated-values",              nullptr, "tsv", "tsv"},
#endif
#ifndef DISABLE_XML
  {"application/sparql-results+xml",         nullptr, "srx", "xml"},
#endif
#ifndef DISABLE_XSLT
  {"application/xml",                        nullptr, "xml", "xslt"},
#endif
  {nullptr, nullptr, nullptr, nullptr},
};

static const unsigned int sparql_format_count =
  (sizeof(sparql_format_info) / sizeof(sparql_format_info[0])) - 1;

bool
format::supported(const char* const content_type) {
  if (content_type != nullptr) {
    for (unsigned int i = 0; i < sparql_format_count; i++) {
      const format* const format_info = &sparql_format_info[i];
      assert(format_info->content_type != nullptr);

      if (std::strcmp(content_type, format_info->content_type) == 0) {
        return true; /* found */
      }
    }
  }

  return false; /* not found */
}
