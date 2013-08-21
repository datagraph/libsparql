/* This is free and unencumbered software released into the public domain. */

static void
write_boolean(sparql::writer& writer) {
  writer.begin();
  {
    writer.write_head();
    writer.write_boolean(true);
  }
  writer.finish();
}

static void
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
