/* This is free and unencumbered software released into the public domain. */

static void
write_boolean(sparql::writer& writer) {
  writer.begin();
  {
    writer.begin_head();
    writer.finish_head();
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
      writer.begin_variables();
      {
        writer.write_variable("s");
        writer.write_variable("p");
        writer.write_variable("o");
      }
      writer.finish_variables();
    }
    writer.finish_head();

    writer.begin_results();
    {
      writer.begin_result();
      {
        writer.write_binding("s"); // TODO
        writer.write_binding("p"); // TODO
        writer.write_binding("o"); // TODO
      }
      writer.finish_result();
    }
    writer.finish_results();
  }
  writer.finish();
}
