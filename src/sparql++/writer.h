/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_H
#define SPARQLXX_WRITER_H

#include <cstdio>  /* for FILE */
#include <memory>  /* for std::unique_ptr */
#include <ostream> /* for std::ostream */
#include <string>  /* for std::string */
#include <vector>  /* for std::vector */

namespace sparql {
  class writer {
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
     */
    void begin();

    /**
     */
    void finish();

    /**
     */
    void write_head();

    /**
     */
    void begin_head();

    /**
     */
    void finish_head();

    /**
     */
    void write_variables(const std::vector<std::string>& names);

    /**
     */
    void begin_variables();

    /**
     */
    void finish_variables();

    /**
     */
    void write_variable(const std::string& name) {
      write_variable(name.c_str());
    }

    /**
     */
    void write_variable(const char* name);

    /**
     */
    void write_link(const std::string& href) {
      write_link(href.c_str());
    }

    /**
     */
    void write_link(const char* href);

    /**
     */
    void write_boolean(bool value);

    /**
     */
    void begin_results();

    /**
     */
    void finish_results();

    /**
     */
    void begin_result();

    /**
     */
    void finish_result();

    /**
     */
    void write_binding(const std::string& name, ...) { // FIXME
      write_binding(name.c_str()); // TODO
    }

    /**
     */
    void write_binding(const char* name, ...); // FIXME

    /**
     */
    void flush();

    /**
     * The opaque type for the actual implementation logic.
     */
    struct implementation;

  private:
    std::unique_ptr<implementation> _implementation = {nullptr};
  };
}

#endif /* SPARQLXX_WRITER_H */
