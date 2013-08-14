/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/json.h"

#include <cassert> /* for assert() */
#include <cstring> /* for std::strlen() */

#include <yajl/yajl_gen.h>

namespace {
  struct implementation : public sparql::writer::implementation {
  public:
    implementation(FILE* stream);
    virtual ~implementation() noexcept override;
    virtual void begin() override;
    virtual void finish() override;
    virtual void begin_head() override;
    virtual void finish_head() override;
    virtual void begin_variables() override;
    virtual void finish_variables() override;
    virtual void write_variable(const char* name) override;
    virtual void write_link(const char* href) override;
    virtual void write_boolean(bool value) override;
    virtual void begin_results() override;
    virtual void finish_results() override;
    virtual void begin_result() override;
    virtual void finish_result() override;
    virtual void begin_binding(const char* name) override;
    virtual void finish_binding() override;
    virtual void write_uri_reference(const char* string) override;
    virtual void write_blank_node(const char* string) override;
    virtual void write_plain_literal(const char* string, const char* language) override;
    virtual void write_typed_literal(const char* string, const char* datatype) override;
    virtual void flush() override;

    void write(const char* data, std::size_t size) {
      fwrite(data, 1, size, _stream); // TODO: error handling
    }

  protected:
    void begin_map() {
      const int rc = yajl_gen_map_open(_state);
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

    void finish_map() {
      const int rc = yajl_gen_map_close(_state);
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

    void begin_array() {
      const int rc = yajl_gen_array_open(_state);
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

    void finish_array() {
      const int rc = yajl_gen_array_close(_state);
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

    void write_pair(const char* key, const char* value) {
      assert(key != nullptr);
      write_string(key);
      write_string(value);
    }

    void write_string(const char* string) {
      const int rc = (string == nullptr) ? yajl_gen_null(_state) :
        yajl_gen_string(_state, reinterpret_cast<const unsigned char*>(string), std::strlen(string));
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

    void write_bool(const bool value) {
      const int rc = yajl_gen_bool(_state, value);
      if (rc != yajl_gen_status_ok) {
        // TODO: error handling
      }
    }

  private:
    FILE* _stream = nullptr;
    yajl_gen _state = nullptr;
  };
}

sparql::writer::implementation*
sparql_writer_for_json(FILE* const stream,
                       const char* const content_type,
                       const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream);
}

static void
_yajl_write_callback(void* const ctx, const char* const str, const std::size_t len) {
  assert(ctx != nullptr);
  assert(str != nullptr);

  implementation* const writer = reinterpret_cast<implementation*>(ctx);
  assert(writer != nullptr);

  writer->write(str, len);
}

implementation::implementation(FILE* const stream)
  : _stream(stream) {
  assert(stream != nullptr);

  _state = yajl_gen_alloc(nullptr);
  assert(_state != nullptr);

  {
    const int rc = yajl_gen_config(_state, yajl_gen_print_callback, _yajl_write_callback, this);
    (void)rc;
  }
  {
    const int rc = yajl_gen_config(_state, yajl_gen_beautify, true);
    (void)rc;
  }
  {
    const int rc = yajl_gen_config(_state, yajl_gen_indent_string, "  "); /* two spaces */
    (void)rc;
  }
}

implementation::~implementation() noexcept {
  if (_state != nullptr) {
    yajl_gen_free(_state);
    _state = nullptr;
  }
}

void
implementation::begin() {
  begin_map();
}

void
implementation::finish() {
  finish_map();
}

void
implementation::begin_head() {
  write_string("head");
  begin_map();
}

void
implementation::finish_head() {
  finish_map();
}

void
implementation::begin_variables() {
  write_string("vars");
  begin_array();
}

void
implementation::finish_variables() {
  finish_array();
}

void
implementation::write_variable(const char* const name) {
  write_string(name);
}

void
implementation::write_link(const char* const href) {
  write_string("link");
  begin_array();
  write_string(href);
  finish_array();
}

void
implementation::write_boolean(const bool value) {
  write_string("boolean");
  write_bool(value);
}

void
implementation::begin_results() {
  write_string("results");
  begin_map();
  write_string("bindings");
  begin_array();
}

void
implementation::finish_results() {
  finish_array();
  finish_map();
}

void
implementation::begin_result() {
  begin_map();
}

void
implementation::finish_result() {
  finish_map();
}

void
implementation::begin_binding(const char* const name) {
  write_string(name);
  begin_map();
}

void
implementation::finish_binding() {
  finish_map();
}

void
implementation::write_uri_reference(const char* const string) {
  begin_map();
  write_pair("type", "uri");
  write_pair("value", string);
  finish_map();
}

void
implementation::write_blank_node(const char* const string) {
  begin_map();
  write_pair("type", "bnode");
  write_pair("value", string);
  finish_map();
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  begin_map();
  write_pair("type", "literal");
  write_pair("value", string);
  if (language != nullptr) {
    write_pair("xml:lang", language);
  }
  finish_map();
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  begin_map();
  write_pair("type", "literal"); // TODO: support also for SPARQL 1.0's "typed-literal"
  write_pair("value", string);
  write_pair("datatype", datatype);
  finish_map();
}

void
implementation::flush() {
  fflush(_stream);
}
