/* This is free and unencumbered software released into the public domain. */

#ifndef SPARQLXX_WRITER_H
#define SPARQLXX_WRITER_H

#include <cstdio>  /* for FILE */
#include <memory>  /* for std::unique_ptr */
#include <ostream> /* for std::ostream */
#include <string>  /* for std::string */

#include <boost/noncopyable.hpp>

namespace sparql {
  class writer : private boost::noncopyable {
  public:
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
     * Destructor.
     */
    ~writer();

    /**
     */
    void begin();

    /**
     */
    void finish();

    /**
     */
    void begin_head();

    /**
     */
    void finish_head();

    /**
     */
    void begin_variables();

    /**
     */
    void finish_variables();

    /**
     */
    void write_variable(const char* name);

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
