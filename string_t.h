#ifndef STRING_T_INCLUDED
#define STRING_T_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

typedef struct string_t {
    char* ptr;
    size_t size; /* always equal to strlen(ptr) */
    size_t cap;
} string_t;

#define STRING_EMPTY (string_t){ NULL, 0ull, 0ull }
#define STRING_NPOS (size_t)-1

#ifndef STRING_MULTIPLIER /* see _string_detail_increase_cap() */
#   define STRING_MULTIPLIER 2ull
#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#   define _STRING_NODISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER) && (_MSC_VER >= 1700)
#   define _STRING_NODISCARD _Check_return_
#else
#   define _STRING_NODISCARD
#endif

#if defined(__GNUC__) && (__GNUC__ >= 3)
#   define _STRING_EXPECT(expr, c) __builtin_expect(!!(expr), c)
#else
#   define _STRING_EXPECT(expr, c) (expr)
#endif

#define _STRING_LIKELY(expr) _STRING_EXPECT(expr, 1)
#define _STRING_UNLIKELY(expr) _STRING_EXPECT(expr, 0)

void _string_detail_destructor(string_t*);
#if defined(__GNUC__) && defined(__has_attribute)
#   if __has_attribute(__cleanup__)
#       define STR_AUTO __attribute__((__cleanup__(_string_detail_destructor)))
#   endif
#   if __has_attribute(returns_nonnull)
#       define _STRING_RETURNS_NONNULL __attribute__((returns_nonnull))
#   endif
#endif

#if !defined(_STRING_RETURNS_NONNULL)
#   define _STRING_RETURNS_NONNULL
#endif

string_t str_make(const char* str) _STRING_NODISCARD;
string_t str_make_c(const char* str, size_t cap) _STRING_NODISCARD;
string_t str_make_n(const char* str, size_t size) _STRING_NODISCARD;
string_t str_make_n_c(const char* str, size_t size, size_t cap) _STRING_NODISCARD;
string_t str_make_empty(size_t cap) _STRING_NODISCARD;
string_t str_copy(const string_t* string) _STRING_NODISCARD;
void str_exchg(string_t* first, string_t* second);
string_t str_move(string_t* string) _STRING_NODISCARD;
char* str_at(const string_t* string, size_t idx) _STRING_RETURNS_NONNULL;
void str_push(string_t* string, char c);
char str_pop(string_t* string);
void str_set_cap(string_t* string, size_t new_cap);
void str_reset(string_t* string);
const char* str_end(const string_t* string);
string_t str_substr(const string_t* src, size_t idx_first, size_t idx_last) _STRING_NODISCARD;
char* str_write(const string_t* src, char* buf);
char* str_write_nt(const string_t* src, char* buf);
char* str_write_n(const string_t* src, char* buf, size_t max);
char* str_write_n_nt(const string_t* src, char* buf, size_t max);
char* str_substr_write(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* str_substr_write_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* str_substr_write_n(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
char* str_substr_write_n_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
size_t str_find(const string_t* string, char c);
size_t str_rfind(const string_t* string, char c);
size_t str_find_nth(const string_t* string, char c, size_t n);
size_t str_rfind_nth(const string_t* string, char c, size_t n);

void _string_detail_set_cchp(string_t*, const char*);
void _string_detail_set_cstp(string_t*, const string_t*);
int _string_detail_same_cchp(const string_t*, const char*);
int _string_detail_same_cstp(const string_t*, const string_t*);
int _string_detail_same_n_cchp(const string_t* string, const char* str, size_t max);
int _string_detail_same_n_cstp(const string_t* first, const string_t* second, size_t max);
void _string_detail_app_cchp(string_t*, const char*);
void _string_detail_app_cstp(string_t*, const string_t*);
int _string_detail_pre_cchp(const string_t*, const char*);
int _string_detail_pre_cstp(const string_t*, const string_t*);
int _string_detail_suf_cchp(const string_t*, const char*);
int _string_detail_suf_cstp(const string_t*, const string_t*);

#define str_free(string) free(string.ptr)
#define str_add_cap(string, n) str_set_cap(&string, n + string.cap)
#define str_clear(string) memset(string.ptr, '\0', string.size)
#define str_is_empty(string) (string.size == 0)
#define str_fwrite(string, file) fputs(string.ptr, file)

#define str_set(pdest, src) _Generic((src),                     \
    char*: _string_detail_set_cchp,                             \
    string_t*: _string_detail_set_cstp                          \
)((pdest), (src))

#define str_same(pstring, second) _Generic((second),            \
    char*: _string_detail_same_cchp ,                           \
    string_t*: _string_detail_same_cstp                         \
)((pstring), (second))

#define str_same_n(pstring, second, max) _Generic((second),     \
    char*: _string_detail_same_n_cchp,                          \
    string_t*: _string_detail_same_n_cstp                       \
)((pstring), (second), (max))

#define str_app(pdest, src) _Generic((src),                     \
    char*: _string_detail_app_cchp,                             \
    string_t*: _string_detail_app_cstp                          \
)((pdest), (src))

#define str_pre(pstring, pre) _Generic((pre),                   \
    char*: _string_detail_pre_cchp,                             \
    string_t*: _string_detail_pre_cstp                          \
)((pstring), (pre))

#define str_suf(pstring, suf) _Generic((suf),                   \
    char*: _string_detail_suf_cchp,                             \
    string_t*: _string_detail_suf_cstp                          \
)((pstring), (suf))

#endif
