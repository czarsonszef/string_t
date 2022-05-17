#ifndef STRING_T_INCLUDED
#define STRING_T_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

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

typedef struct string_t {
    char* ptr;
    size_t size; /* always equal to strlen(ptr) */
    size_t cap;
} string_t;

#define STRING_EMPTY (string_t){ NULL, 0, 0 };

_STRING_NODISCARD string_t str_make(const char* str);
_STRING_NODISCARD string_t str_make_n(const char* str, size_t size);
_STRING_NODISCARD string_t str_copy(const string_t* string);
void str_exchg(string_t* first, string_t* second);
void str_free(string_t* string);
char* str_at(const string_t* string, size_t idx);
char str_pop(string_t* string);
size_t str_find(const string_t* string, char c);
size_t str_rfind(const string_t* string, char c);
size_t str_find_nth(const string_t* string, char c, size_t n);
size_t str_rfind_nth(const string_t* string, char c, size_t n);
void str_set_cap(string_t* string, size_t new_cap);
void str_add_cap(string_t* string, size_t n);
_STRING_NODISCARD string_t str_substr(const string_t* src, size_t idx_first, size_t idx_last);
char* str_write(const string_t* src, char* buf);
char* str_write_nt(const string_t* src, char* buf);
char* str_write_n(const string_t* src, char* buf, size_t max);
char* str_write_n_nt(const string_t* src, char* buf, size_t max);
char* str_substr_write(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* str_substr_write_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* str_substr_write_n(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
char* str_substr_write_n_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
void str_clear(string_t* string);
void str_reset(string_t* string);
const char* str_end(const string_t* string);
int str_is_empty(const string_t* string);
_STRING_NODISCARD string_t str_move(string_t* string);
int str_fgetln(string_t* dest, FILE* fp);
int str_fgetln_n(string_t* dest, FILE* fp, size_t max);
int str_fwrite(const string_t* src, FILE* fp);

void _string_detail_set_cchp(string_t* string, const char* str);
void _string_detail_set_cstp(string_t* dest, const string_t* src);
int _string_detail_same_cchp(const string_t* string, const char* str);
int _string_detail_same_cstp(const string_t* first, const string_t* second);
void _string_detail_app_cchp(string_t* dest, const char* src);
void _string_detail_app_cstp(string_t* dest, const string_t* src);
int _string_detail_pre_cchp(const string_t* string, const char* pre);
int _string_detail_pre_cstp(const string_t* string, const string_t* pre);
int _string_detail_suf_cchp(const string_t* string, const char* suf);
int _string_detail_suf_cstp(const string_t* string, const string_t* suf);

#define str_set(dest, src) _Generic((src),      \
    char*: _string_detail_set_cchp,             \
    string_t*: _string_detail_set_cstp          \
)((dest), (src))

#define str_same(string, str) _Generic((str),   \
    char*: _string_detail_same_cchp,            \
    string_t*: _string_detail_same_cstp         \
)((string), (str))

#define str_app(dest, src) _Generic((src),      \
    char*: _string_detail_app_cchp,             \
    string_t*: _string_detail_app_cstp          \
)((dest), (src))

#endif
