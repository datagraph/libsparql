/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_BRTR_H
#define SPARQLXX_WRITER_BRTR_H

#include "sparql++/writer/impl.h"

sparql::writer::implementation* sparql_writer_for_brtr(
  FILE* stream,
  const char* content_type,
  const char* charset);

#endif /* SPARQLXX_WRITER_BRTR_H */
