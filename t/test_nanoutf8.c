#include "../nanoutf8.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// tap utils
#define ok(b) printf("%s - %s line %d\n", (b) ? "ok" : "not ok", __FILE__, __LINE__);

inline void note(const char*s)
{
  printf("# %s\n", s);
}

void test_nanoutf8_encode(const char* src, uint64_t ch, size_t len)
{
  char buf[6];
  size_t got_len = nanoutf8_encode(ch, buf);
  ok(got_len == len);
  ok(memcmp(buf, src, len) == 0);
}

void test_nanoutf8_next_size(char src, size_t len)
{
  ok(nanoutf8_next_size(src) == len);
}

void test_nanoutf8_peek_char(const char* src, uint64_t ch, size_t len) {
  bool succeeded;
  size_t got_len;
  uint64_t got_ch = nanoutf8_peek_char(src, len, &got_len, &succeeded);
  ok(got_ch == ch);
  ok(got_len == len);
  ok(succeeded);
}

void test_nanoutf8(size_t len, const char* src, uint64_t ch)
{
  printf("# -------- %lX ------ %zu\n", ch, len);
  printf("#  next_size\n");
  test_nanoutf8_next_size(src[0], len);
  printf("#  peek_char\n");
  test_nanoutf8_peek_char(src, ch, len);
  printf("#  encode\n");
  test_nanoutf8_encode(src, ch, len);
}

void test_nanoutf8_run()
{
  // U+0000 00
  test_nanoutf8(1, "\x00",     0x00000000);
  // U+007F 7F
  test_nanoutf8(1, "\x7f",     0x0000007f);
  // U+0080 C2  80
  test_nanoutf8(2, "\xc2\x80", 0x00000080);
  // U+07FF DF  BF
  test_nanoutf8(2, "\xdf\xbf", 0x000007ff);
  // U+0800 E0  A0  80
  test_nanoutf8(3, "\xe0\xa0\x80", 0x0000800);
  // U+FFFF EF  BF  BF
  test_nanoutf8(3, "\xef\xbf\xbf", 0x000FFFF);
  // U+10000 F0  90  80  80
  test_nanoutf8(4, "\xf0\x90\x80\x80", 0x0010000);
  // U+1FFFFF F7  BF  BF  BF
  test_nanoutf8(4, "\xf7\xbf\xbf\xbf", 0x01FFFFF);
  // U+200000 F8  88  80  80  80
  test_nanoutf8(5, "\xf8\x88\x80\x80\x80", 0x0200000);
  // U+3FFFFFF FB BF  BF  BF  BF
  test_nanoutf8(5, "\xfb\xbf\xbf\xbf\xbf", 0x3FFFFFF);
  // U+4000000  FC  84  80  80  80  80
  test_nanoutf8(6, "\xfc\x84\x80\x80\x80\x80", 0x4000000);
  // U+7FFFFFFF FD  BF  BF  BF  BF  BF
  test_nanoutf8(6, "\xfd\xbf\xbf\xbf\xbf\xbf", 0x7FFFFFFF);
}

int main() {
  printf("1..78\n");

  test_nanoutf8_run();
  test_nanoutf8(3, "あ", 0x3042);
}
