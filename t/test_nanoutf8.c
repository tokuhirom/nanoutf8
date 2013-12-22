#include "../nanoutf8.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// tap utils
static inline void ok(bool b)
{
  printf("%s - %s line %d\n", b ? "ok" : "not ok", __FILE__, __LINE__);
}
static inline void note(const char*s)
{
  printf("# %s\n", s);
}
static inline void header(const char*s)
{
  printf("# ---- %20s ----\n", s);
}

// test cases
void test_nanoutf8_encode() {
  header("nanoutf8_encode");
  {
    char buf[4];
    size_t len = nanoutf8_encode(0x0061, buf);
    ok(len == 1);
    ok(buf[0] == '\x61');
  }
  // copyright sign U+00A9 \xc2\xa9
  {
    char buf[4];
    size_t len = nanoutf8_encode(0x00A9, buf);
    ok(len == 2);
    ok(buf[0] == '\xc2');
    ok(buf[1] == '\xa9');
    buf[2] = '\0';
    printf("# copyright sign : %s\n", buf);
  }
  // Japanese hiragana U+3042 \xe3\x81\x82
  {
    char buf[4];
    size_t len = nanoutf8_encode(0x3042, buf);
    ok(len == 3);
    ok(buf[0] == '\xe3');
    ok(buf[1] == '\x81');
    ok(buf[2] == '\x82');
    buf[3] = '\0';
    printf("# Japanese Hiragana : %s\n", buf);
  }
  // U+20016 \xf0\xa0\x80\x96
  {
    char buf[4];
    size_t len = nanoutf8_encode(0x20016, buf);
    ok(len == 4);
    ok(buf[0] == '\xf0');
    ok(buf[1] == '\xa0');
    ok(buf[2] == '\x80');
    ok(buf[3] == '\x96');
  }
}

int main() {
  printf("1..22\n");

  header("nanoutf8_next_size");

  // basic latin \x61
  ok(nanoutf8_next_size("a"[0]));
  // copyright sign U+00A9 \xc2\xa9
  ok(nanoutf8_next_size("\xc2\xa9"[0]) == 2);
  // Japanese hiragana U+3042 
  ok(nanoutf8_next_size("\xE3\x81\x82"[0]) == 3);
  // LYCIAN LETTER A U+10280
  ok(nanoutf8_next_size("\xf0\x90\x8a\x80"[0]) == 4);
  // U+20016
  ok(nanoutf8_next_size("\xf0\xa0\x80\x96"[0]) == 4);

  header("nanoutf8_peek_char");
  {
    bool succeeded;
    size_t len;
    int32_t ch = nanoutf8_peek_char("あ", strlen("あ"), &len, &succeeded);
    ok(ch == 0x3042);
    ok(len == 3);
    ok(succeeded);
  }
  test_nanoutf8_encode();
}
