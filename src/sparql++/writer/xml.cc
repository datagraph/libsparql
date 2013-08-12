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
  public:
    implementation(FILE* stream);

    virtual ~implementation() override;

    virtual void begin() override;

    virtual void finish() override;

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

    inline void finish_element() {
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterEndElement */
      //xmlTextWriterEndElement(_writer);
      /* @see http://www.xmlsoft.org/html/libxml-xmlwriter.html#xmlTextWriterFullEndElement */
      xmlTextWriterFullEndElement(_writer);
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

implementation::~implementation() {
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
  finish_element(); /* </sparql> */

  finish_document(); /* EOF */
}