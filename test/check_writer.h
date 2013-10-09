/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_CHECK_WRITER_H
#define SPARQLXX_CHECK_WRITER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>    /* for assert() */
#include <cstddef>    /* for std::size_t */
#include <cstdio>     /* for FILE, open_memstream(), std::f*(), std::tmpfile() */
#include <cstdlib>    /* for std::free() */
#include <functional> /* for std::function */
#include <string>     /* for std::string */

static inline void
write_boolean(sparql::writer& writer) {
  writer.begin();
  {
    writer.write_head();
    writer.write_boolean(true);
  }
  writer.finish();
}

static inline void
write_bindings(sparql::writer& writer) {
  writer.begin();
  {
    writer.begin_head();
    {
      writer.write_variables({"s", "p", "o"});
    }
    writer.finish_head();

    writer.begin_results();
    {
      writer.begin_result();
      {
        writer.begin_binding("s");
        writer.write_blank_node("jhacker");
        writer.finish_binding();

        writer.begin_binding("p");
        writer.write_uri_reference("http://xmlns.com/foaf/0.1/name");
        writer.finish_binding();

        writer.begin_binding("o");
        writer.write_plain_literal("J. Random Hacker", "en");
        writer.finish_binding();
      }
      writer.finish_result();
    }
    writer.finish_results();
  }
  writer.finish();
}

static inline std::string
read_file(FILE* const input) {
  std::string result;

  char buffer[4096];
  std::size_t buffer_size = 0;

  while (!std::feof(input) && !std::ferror(input)) {
    if ((buffer_size = std::fread(buffer, 1, sizeof(buffer), input))) {
      result.append(buffer, buffer_size);
    }
  }

  return result;
}

static inline std::string
read_file(const char* const path) {
  FILE* const input = std::fopen(path, "r");
  assert(input != nullptr);

  std::string result = read_file(input);

  std::fclose(input);

  return result;
}

static inline std::string
with_captured_output(std::function<void (FILE*)> callback) {
#ifdef HAVE_OPEN_MEMSTREAM
  char* buffer = nullptr;
  std::size_t buffer_size = 0;

  FILE* const output = open_memstream(&buffer, &buffer_size);
  assert(output != nullptr);

  callback(output);

  std::fclose(output);
  assert(buffer != nullptr);

  std::string result(buffer);
  std::free(buffer);
#else /* !HAVE_OPEN_MEMSTREAM */
  FILE* const output = std::tmpfile();
  assert(output != nullptr);

  callback(output);

  std::rewind(output);
  std::string result = read_file(output);

  std::fclose(output);
#endif /* HAVE_OPEN_MEMSTREAM */

  return result;
}

#endif /* SPARQLXX_CHECK_WRITER_H */
