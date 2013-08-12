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
    writer(
      const std::string& file_path,
      const std::string& content_type,
      const std::string& charset);

    writer(
      std::ostream& stream,
      const std::string& content_type,
      const std::string& charset);

    writer(
      FILE* stream,
      const std::string& content_type,
      const std::string& charset);

    ~writer();

    void begin();

    void finish();

    void flush();

    struct implementation;

  private:
    std::unique_ptr<implementation> _implementation = {nullptr};
  };
}

#endif /* SPARQLXX_WRITER_H */
