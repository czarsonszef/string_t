#include "string_t.h"

static void _string_detail_increase_cap(string_t* string, size_t new_cap) {
    if (string->cap == 0)
        string->cap = 1;

    while (string->cap < new_cap)
        string->cap *= STRING_MULTIPLIER;

    string->ptr = realloc(string->ptr, sizeof(char) * string->cap);
}

string_t str_make(const char* str) {
    const size_t str_len = strlen(str);
    string_t out = {
        .ptr = malloc(sizeof(char) * (str_len + 1)),
        .size = str_len,
        .cap = str_len + 1
    };

    memcpy(out.ptr, str, str_len + 1);
    return out;
}

string_t str_make_n(const char* str, size_t size) {
    string_t out = {
        .ptr = malloc(sizeof(char) * (size + 1)),
        .size = size,
        .cap = size + 1
    };

    memcpy(out.ptr, str, size);
    out.ptr[size] = '\0';
    return out;
}

string_t str_copy(const string_t* string) {
    string_t out = {
        .ptr = malloc(sizeof(char) * (string->size + 1)),
        .size = string->size,
        .cap = string->size + 1
    };

    memcpy(out.ptr, string->ptr, out.cap);
    return out;
}

void _string_detail_set_cchp(string_t* string, const char* str) {
    const size_t str_len = strlen(str);
    if (str_len + 1 > string->cap)
        _string_detail_increase_cap(string, str_len + 1);
    memcpy(string->ptr, str, str_len + 1);
    string->size = str_len;
}

void _string_detail_set_cstp(string_t* dest, const string_t* src) {
    if (src->size + 1 > dest->cap)
        _string_detail_increase_cap(dest, src->size + 1);

    memcpy(dest->ptr, src->ptr, src->size + 1);
    dest->size = src->size;
}

void str_exchg(string_t* first, string_t* second) {
    string_t buf = *first;
    *first = *second;
    *second = buf;
}

void str_free(string_t* string) {
    free(string->ptr);
}

char* str_at(const string_t* string, size_t idx) {
    assert(!(idx >= string->size) && "string_at(): idx out of range");
    return &string->ptr[idx];
}

int str_equal(const string_t* first, const string_t* second) {
    return !strcmp(first->ptr, second->ptr);
}

char str_pop(string_t* string) {
    const char out = string->ptr[--string->size];
    string->ptr[string->size] = '\0';
    return out;
}

size_t str_find(const string_t* string, char c) {
    size_t i = 0;
    for (; i < string->size; ++i)
        if (string->ptr[i] == c)
            return i;

    return STRING_NPOS;
}

size_t str_rfind(const string_t* string, char c) {
    size_t i = string->size - 1;
    for (; i >= 0; --i)
        if (string->ptr[i] == c)
            return i;
    
    return STRING_NPOS;
}

size_t str_find_nth(const string_t* string, char c, size_t n) {
    assert(n > 0);

    size_t i = 0;
    for (; i < string->size; ++i)
        if (string->ptr[i] == c) {
            if (n == 1)
                return i;
            --n;
        }

    return STRING_NPOS;
}

size_t str_rfind_nth(const string_t* string, char c, size_t n) {
    assert(n > 0);

    size_t i = string->size - 1;
    for (; i >= 0; --i)
        if (string->ptr[i] == c) {
            if (n == 1)
                return i;
            --n;
        }

    return STRING_NPOS;
}

void str_set_cap(string_t* string, size_t new_cap) {
    if (new_cap > string->cap) {
        string->cap = new_cap;
        string->ptr = realloc(string->ptr, sizeof(char) * new_cap);
    } else if (new_cap < string->cap) {
        string->cap = new_cap;
        string->size = new_cap - 1;
        string->ptr = realloc(string->ptr, sizeof(char) * new_cap);
        string->ptr[string->size] = '\0';
    }
}

void str_add_cap(string_t* string, size_t n) {
    str_set_cap(string, n + string->cap);
}

string_t str_substr(const string_t* src, size_t idx_first, size_t idx_last) {
    /* [first, last) */
    assert(idx_last >= idx_first && idx_last <= src->size && "string_substre(): idxes out of range");

    const size_t len = idx_last - idx_first + 1;
    string_t out = {
        .ptr = malloc(sizeof(char) * len),
        .size = len - 1,
        .cap = len
    };

    memcpy(out.ptr, src->ptr + idx_first, out.size);
    out.ptr[out.size] = '\0';
    return out;
}

char* str_write(const string_t* src, char* buf) {
    memcpy(buf, src->ptr, src->size + 1);
    return buf;
}

char* str_write_nt(const string_t* src, char* buf) {
    memcpy(buf, src->ptr, src->size);
    return buf;
}

char* str_write_n(const string_t* src, char* buf, size_t max) {
    size_t len;
    if (src->size >= max) len = max;
    else len = src->size;
    memcpy(buf, src->ptr, len);
    buf[len] = '\0';
    return buf;
}

char* str_write_n_nt(const string_t* src, char* buf, size_t max) {
    size_t len;
    if (src->size >= max) len = max;
    else len = src->size;
    memcpy(buf, src->ptr, len);
    return buf;
}

char* str_substr_write(const string_t* src, char* buf, size_t idx_first, size_t idx_last) {
    assert(idx_last >= idx_first && idx_last <= src->size && "string_substr_write(): idxes out of range");
    const size_t len = idx_last - idx_first;
    memcpy(buf, src->ptr + idx_first, len);
    buf[len] = '\0';
    return buf;
}

char* str_substr_write_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last) {
    assert(idx_last >= idx_first && idx_last <= src->size && "string_substr_write(): idxes out of range");
    const size_t len = idx_last - idx_first;
    memcpy(buf, src->ptr + idx_first, len);
    return buf;
}

char* str_substr_write_n(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max) {
    assert(idx_last >= idx_first && idx_last <= src->size);
    size_t len = idx_last - idx_first;
    if (len > max) len = max;
    memcpy(buf, src->ptr + idx_first, len);
    buf[len] = '\0';
    return buf;
}

char* str_substr_write_n_nt(const string_t* src, char* buf, size_t idx_first, size_t idx_last, size_t max) {
    assert(idx_last >= idx_first && idx_last <= src->size);
    size_t len = idx_last - idx_first;
    if (len > max) len = max;
    memcpy(buf, src->ptr + idx_first, len);
    return buf;
}

void str_app(string_t* dest, const string_t* src) {
    _string_detail_increase_cap(dest, dest->size + src->size + 1);
    memcpy(dest->ptr + dest->size, src->ptr, src->size + 1);
    dest->size += src->size;
}

void str_app_chars(string_t* dest, const char* src) {
    const size_t src_len = strlen(src);
    _string_detail_increase_cap(dest, src_len + dest->size + 1);
    memcpy(dest->ptr + dest->size, src, src_len + 1);
    dest->size += src_len;
}

void str_clear(string_t* string) {
    memset(string->ptr, '\0', string->size);
}

void str_reset(string_t* string) {
    free(string->ptr);
    *string = STRING_EMPTY;
}

const char* str_end(const string_t* string) {
    return string->ptr + string->size + 1;
}

int str_is_empty(const string_t* string) {
    return string->size == 0;
}

string_t str_move(string_t* string) {
    string_t out = *string;
    *string = STRING_EMPTY;
    return out;
}

int str_fgetln(string_t* dest, FILE* fp) {
    return fgets(dest->ptr, dest->cap, fp) != NULL;
}

int str_fgetln_n(string_t* dest, FILE* fp, size_t max) {
    size_t len;
    ++max;

    if (max > dest->cap) {
        _string_detail_increase_cap(dest, max);
        len = dest->cap;
    } else
        len = max;

    return fgets(dest->ptr, len, fp) != NULL;
}

int str_fwrite(const string_t* src, FILE* fp) {
    return fputs(src->ptr, fp);
}

int str_suf(const string_t* src, const string_t* suf) {

}
