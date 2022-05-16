#include "string_t.h"

static void _string_detail_increase_cap(string_t* string, size_t new_cap) {
    while (string->cap < new_cap)
        string->cap *= STRING_MULTIPLIER;

    string->ptr = realloc(string->ptr, new_cap * sizeof(char));
}

string_t string_make(const char* str, size_t size) {
    string_t out = {
        .ptr = malloc(sizeof(char) * (size + 1)),
        .size = size,
        .cap = size + 1
    };

    if (out.ptr == NULL)
        exit(-1);

    memcpy(out.ptr, str, size);
    out.ptr[size] = '\0';
    return out;
}

void string_exchg(string_t* first, string_t* second) {
    string_t buf = *first;
    *first = *second;
    *second = buf;
}

void string_free(string_t* string) {
    free(string->ptr);
    string->ptr = NULL;
    string->cap = 0ull;
    string->size = 0ull;
}

char string_at(const string_t* string, size_t idx) {
    assert(!(idx >= string->size));
    return string->ptr[idx];
}

int string_equal(const string_t* first, const string_t* second) {
    return !strcmp(first->ptr, second->ptr);
}

void string_pop(string_t* string) {
    string->ptr[--string->size] = '\0';
}

size_t string_find(const string_t* string, char c) {
    size_t i = 0ull;
    for (; i < string->size; ++i)
        if (string->ptr[i] == c)
            return i;

    return STRING_NPOS;
}

size_t string_rfind(const string_t* string, char c) {
    size_t i = string->size - 1ull;
    for (; i >= 0ull; --i)
        if (string->ptr[i] == c)
            return i;
    
    return STRING_NPOS;
}

size_t string_find_nth(const string_t* string, char c, size_t n) {
    assert(n > 0);

    size_t i = 0ull;
    for (; i < string->size; ++i)
        if (string->ptr[i] == c) {
            if (n == 1ull)
                return i;
            --n;
        }

    return STRING_NPOS;
}

size_t string_rfind_nth(const string_t* string, char c, size_t n) {
    assert(n > 0);

    size_t i = string->size - 1ull;
    for (; i >= 0ull; --i)
        if (string->ptr[i] == c) {
            if (n == 1ull)
                return i;
            --n;
        }

    return STRING_NPOS;
}

void string_set_cap(string_t* string, size_t new_cap) {
    if (new_cap > string->cap) {
        string->cap = new_cap;
        realloc(string->ptr, sizeof(char) * new_cap);
    } else if (new_cap < string->cap) {
        string->cap = new_cap;
        string->size = new_cap - 1ull;
        realloc(string->ptr, sizeof(char) * new_cap);
        string->ptr[string->size] = '\0';
    }
}

void string_add_cap(string_t* string, size_t n) {
    string_set_cap(string, n + string->cap);
}

string_t string_substr(const string_t* src, size_t idx_first, size_t idx_last) {
    /* [first, last) */
    assert(idx_last >= idx_first && idx_last <= src->size);

    const size_t len = idx_last - idx_first + 1ull;
    string_t out = {
        .ptr = malloc(sizeof(char) * len),
        .size = len - 1ull,
        .cap = len
    };

    memcpy(out.ptr, src->ptr + idx_first, out.size);
    out.ptr[out.size] = '\0';
    return out;
}

void string_substr_write(const string_t* src, char* buf, size_t idx_first, size_t idx_last) {
    assert(idx_last >= idx_first && idx_last <= src->size);

    const size_t len = idx_last - idx_first + 1ull;
    memcpy(buf, src->ptr + idx_first, len - 1);
    buf[len - 1] = '\0';
}

void string_substr_write_n(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max /* - includes null terminator */) {
    assert(idx_last >= idx_first && idx_last <= src->size);

    size_t len = idx_last - idx_first + 1ull;
    if (len > max) len = max;
    memcpy(buf, src->ptr + idx_first, len - 1);
    buf[len - 1] = '\0';
}

void string_app(string_t* dest, const string_t* src) {
    char* const dest_last = dest->ptr + dest->size;
    _string_detail_increase_cap(dest, dest->size + src->size + 1);
    memcpy(dest_last, src->ptr, src->size + 1);
    dest->size += src->size;
}

void string_app_chars(string_t* dest, const char* src) {
    const size_t src_len = strlen(src);
    char* const dest_last = dest->ptr + dest->size;
    _string_detail_increase_cap(dest, src_len + dest->size + 1);
    memcpy(dest_last, src, src_len + 1);
    dest->size += src_len;
}

void string_clear(string_t* string) {
    memset(string->ptr, '\0', string->size);
}
