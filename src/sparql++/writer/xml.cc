/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sparql++/writer/xml.h"

#include <cassert>   /* for assert() */
#include <stdexcept> /* for std::runtime_error */

#include <libxml/xmlwriter.h>

namespace {
  struct implementation : public sparql::writer::implementation {
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

    virtual void flush() override {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterFlush */
      xmlTextWriterFlush(_writer);
    }

  protected:
    inline void begin_document() {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterStartDocument */
      xmlTextWriterStartDocument(_writer, "1.0", "UTF-8", nullptr);
    }

    inline void finish_document() {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterEndDocument */
      xmlTextWriterEndDocument(_writer);
    }

    inline void write_element(const char* name, const char* text) {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterWriteElement */
      xmlTextWriterWriteElement(_writer,
        reinterpret_cast<const xmlChar*>(name),
        reinterpret_cast<const xmlChar*>(text));
    }

    inline void begin_element(const char* name) {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterStartElement */
      xmlTextWriterStartElement(_writer,
        reinterpret_cast<const xmlChar*>(name));
    }

    inline void begin_element_with_ns(const char* name, const char* ns) {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterStartElementNS */
      xmlTextWriterStartElementNS(_writer, nullptr,
        reinterpret_cast<const xmlChar*>(name),
        reinterpret_cast<const xmlChar*>(ns));
    }

    inline void finish_element(const bool full = false) {
      if (full) {
        /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterFullEndElement */
        xmlTextWriterFullEndElement(_writer);
      }
      else {
        /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterEndElement */
        xmlTextWriterEndElement(_writer);
      }
    }

    inline void write_attribute(const char* name, const char* value) {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterWriteAttribute */
      xmlTextWriterWriteAttribute(_writer,
        reinterpret_cast<const xmlChar*>(name),
        reinterpret_cast<const xmlChar*>(value));
    }

    void write_text(const char* text) {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterWriteString */
      xmlTextWriterWriteString(_writer,
        reinterpret_cast<const xmlChar*>(text));
    }

  private:
    xmlTextWriterPtr _writer = nullptr;
  };
}

sparql::writer::implementation*
sparql_writer_for_xml(FILE* const stream,
                      const char* const content_type,
                      const char* const charset) {
  (void)content_type, (void)charset;
  return new implementation(stream);
}

implementation::implementation(FILE* const stream) {
  assert(stream != nullptr);

  xmlOutputBufferPtr output = xmlOutputBufferCreateFile(stream, nullptr);
  if (output == nullptr) {
    throw std::runtime_error("xmlOutputBufferCreateFile() failed"); // TODO
  }

  _writer = xmlNewTextWriter(output);
  if (_writer == nullptr) {
    (void)xmlOutputBufferClose(output);
    throw std::runtime_error("xmlNewTextWriter() failed"); // TODO
  }
}

implementation::~implementation() noexcept {
  if (_writer != nullptr) {
    xmlFreeTextWriter(_writer);
    _writer = nullptr;
  }
}

void
implementation::begin() {
  xmlTextWriterSetIndent(_writer, 1);
  xmlTextWriterSetIndentString(_writer, reinterpret_cast<const xmlChar*>("  ")); /* two spaces */

  /* <?xml version="1.0" encoding="UTF-8"?> */
  begin_document();

  /* <sparql xmlns="http://www.w3.org/2005/sparql-results#"> */
  begin_element_with_ns("sparql", "http://www.w3.org/2005/sparql-results#");
}

void
implementation::finish() {
  finish_element(true); /* </sparql> */

  finish_document(); /* EOF */
}

void
implementation::begin_head() {
  begin_element("head");
}

void
implementation::finish_head() {
  finish_element(); /* </head> */
}

void
implementation::begin_variables() {
  /* nothing to do */
}

void
implementation::finish_variables() {
  /* nothing to do */
}

void
implementation::write_variable(const char* const name) {
  begin_element("variable");
  write_attribute("name", name);
  finish_element();
}

void
implementation::write_link(const char* const href) {
  begin_element("link");
  write_attribute("href", href);
  finish_element();
}

void
implementation::write_boolean(const bool value) {
  write_element("boolean", value ? "true" : "false");
}

void
implementation::begin_results() {
  begin_element("results");
}

void
implementation::finish_results() {
  finish_element(true); /* </results> */
}

void
implementation::begin_result() {
  begin_element("result");
}

void
implementation::finish_result() {
  finish_element(true); /* </result> */
}

void
implementation::begin_binding(const char* const name) {
  begin_element("binding");
  write_attribute("name", name);
}

void
implementation::finish_binding() {
  finish_element(true);
}

void
implementation::write_uri_reference(const char* const string) {
  (void)string; // TODO
}

void
implementation::write_blank_node(const char* const string) {
  (void)string; // TODO
}

void
implementation::write_plain_literal(const char* const string,
                                    const char* const language) {
  (void)string, (void)language; // TODO
}

void
implementation::write_typed_literal(const char* const string,
                                    const char* const datatype) {
  (void)string, (void)datatype; // TODO
}
