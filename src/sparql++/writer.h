/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_H
#define SPARQLXX_WRITER_H

#include <cstdio>  /* for FILE */
#include <memory>  /* for std::unique_ptr */
#include <ostream> /* for std::ostream */
#include <string>  /* for std::string */
#include <vector>  /* for std::vector */

namespace sparql {
  class writer;
}

class sparql::writer {
public:
  /**
   * Default constructor.
   */
  writer() = delete;

  /**
   * Constructor.
   */
  writer(
    const std::string& file_path,
    const std::string& content_type,
    const std::string& charset);

  /**
   * Constructor.
   */
  writer(
    std::ostream& stream,
    const std::string& content_type,
    const std::string& charset);

  /**
   * Constructor.
   */
  writer(
    FILE* stream,
    const std::string& content_type,
    const std::string& charset);

  /**
   * Copy constructor.
   */
  writer(const writer& other) = delete;

  /**
   * Move constructor.
   */
  writer(writer&& other) noexcept;

  /**
   * Destructor.
   */
  ~writer() noexcept;

  /**
   * Copy assignment operator.
   */
  writer& operator=(const writer& other) = delete;

  /**
   * Move assignment operator.
   */
  writer& operator=(writer&& other) noexcept;

  /**
   * ...
   */
  void begin();

  /**
   * ...
   */
  void finish();

  /**
   * ...
   */
  void write_head();

  /**
   * ...
   */
  void begin_head();

  /**
   * ...
   */
  void finish_head();

  /**
   * ...
   */
  void write_variables(const std::vector<std::string>& names);

  /**
   * ...
   */
  void begin_variables();

  /**
   * ...
   */
  void finish_variables();

  /**
   * ...
   */
  void write_variable(const std::string& name) {
    write_variable(name.c_str());
  }

  /**
   * ...
   */
  void write_variable(const char* name);

  /**
   * ...
   */
  void write_link(const std::string& href) {
    write_link(href.c_str());
  }

  /**
   * ...
   */
  void write_link(const char* href);

  /**
   * ...
   */
  void write_boolean(bool value);

  /**
   * ...
   */
  void begin_results();

  /**
   * ...
   */
  void finish_results();

  /**
   * ...
   */
  void begin_result();

  /**
   * ...
   */
  void finish_result();

  /**
   * ...
   */
  void begin_binding(const std::string& name) {
    begin_binding(name.c_str());
  }

  /**
   * ...
   */
  void begin_binding(const char* name);

  /**
   * ...
   */
  void finish_binding();

  /**
   * ...
   */
  void write_uri_reference(const std::string& string) {
    write_uri_reference(string.c_str());
  }

  /**
   * ...
   */
  void write_uri_reference(const char* string);

  /**
   * ...
   */
  void write_blank_node(const std::string& string) {
    write_blank_node(string.c_str());
  }

  /**
   * ...
   */
  void write_blank_node(const char* string);

  /**
   * ...
   */
  void write_plain_literal(const std::string& string) {
    write_plain_literal(string.c_str(), nullptr);
  }

  /**
   * ...
   */
  void write_plain_literal(const std::string& string, const std::string& language) {
    write_plain_literal(string.c_str(), !language.empty() ? language.c_str() : nullptr);
  }

  /**
   * ...
   */
  void write_plain_literal(const char* string, const char* language = nullptr);

  /**
   * ...
   */
  void write_typed_literal(const std::string& string, const std::string& datatype) {
    write_typed_literal(string.c_str(), datatype.c_str());
  }

  /**
   * ...
   */
  void write_typed_literal(const char* string, const char* datatype);

#if 0
  /**
   * ...
   */
  void write_binding(const std::string& name, ...) { // FIXME
    write_binding(name.c_str()); // TODO
  }

  /**
   * ...
   */
  void write_binding(const char* name, ...); // FIXME
#endif

  /**
   * ...
   */
  void write_comment(const std::string& comment) {
    write_comment(comment.c_str());
  }

  /**
   * ...
   */
  void write_comment(const char* comment);

  /**
   * ...
   */
  void flush();

  /**
   * The opaque type for the actual implementation logic.
   */
  struct implementation;

private:
  std::unique_ptr<implementation> _implementation = {nullptr};
};

#endif /* SPARQLXX_WRITER_H */
