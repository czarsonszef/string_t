#ifndef STRING_T_INCLUDED
#define STRING_T_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define STRING_NPOS (size_t)-1

#ifndef STRING_MULTIPLIER /* see _string_detail_increase_cap() */
    #define STRING_MULTIPLIER 2ull
#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define _STRING_NODISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER) && (_MSC_VER >= 1700)
    #define _STRING_NODISCARD _Check_return_
#else
    #define _STRING_NODISCARD
#endif

typedef struct string_t {
    char* ptr;
    size_t size;
    size_t cap;
} string_t;

_STRING_NODISCARD string_t string_make(const char* str);
_STRING_NODISCARD string_t string_make_n(const char* str, size_t size);
void string_exchg(string_t* first, string_t* second);
void string_free(string_t* string);
char string_at(const string_t* string, size_t idx);
int string_equal(const string_t* first, const string_t* second);
char string_pop(string_t* string);
size_t string_find(const string_t* string, char c);
size_t string_rfind(const string_t* string, char c);
size_t string_find_nth(const string_t* string, char c, size_t n);
size_t string_rfind_nth(const string_t* string, char c, size_t n);
void string_set_cap(string_t* string, size_t new_cap);
void string_add_cap(string_t* string, size_t n);
_STRING_NODISCARD string_t string_substr(const string_t* src, size_t idx_first, size_t idx_last);
char* string_write(const string_t* src, char* buf);
char* string_write_nt(const string_t* src, char* buf);
char* string_write_n(const string_t* src, char* buf, size_t max);
char* string_write_n_nt(const string_t* src, char* buf, size_t max);
char* string_substr_write(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* string_substr_write_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last);
char* string_substr_write_n(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
char* string_substr_write_n_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max);
void string_app(string_t* dest, const string_t* src);
void string_app_chars(string_t* dest, const char* src);
void string_clear(string_t* string);
void string_reset(string_t* string);

#endif
