#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mstring.h"

m_string m_string_init(const char* str)
{
    m_string m;

    m.len = 0;
    m.str = (char*)calloc(M_STRING_STARTER_LEN, 1);
    m_string_concat(&m, str);

    return m;
}

void m_string_push(m_string* m, char ch)
{
    if ((m->len + 2) % M_STRING_STARTER_LEN == 0) {
        m->str = (char*)realloc(m->str, m->len + 2 + M_STRING_STARTER_LEN);
        memset(m->str + m->len + 1, 0, M_STRING_STARTER_LEN);
    }
    *(m->str + m->len) = ch;
    m->len++;
}

void m_string_concat(m_string* m, const char* str)
{
    char* buf;
    size_t al;
    size_t bl;
    size_t tl;

    al = (m->len + 1);
    bl = strlen(str);
    
    tl = al + bl;
    if (tl % M_STRING_STARTER_LEN != 0) {
        tl &= ~(M_STRING_STARTER_LEN - 1);
        tl += M_STRING_STARTER_LEN;
    }
    
    buf = (char*)calloc(tl, 1);
    memcpy(buf, m->str, m->len);
    memcpy(buf + m->len, str, bl);
    free(m->str);
    m->str = buf;
    m->len = m->len + bl;
}

char* m_string_get(m_string* m)
{
    char* buf = (char*)calloc(m->len + 1, 1);
    memcpy(buf, m->str, m->len);
    return buf;
}

void m_string_clear(m_string* m)
{
    free(m->str);
    m->len = 0;
    m->str = (char*)calloc(M_STRING_STARTER_LEN, 1);
}

char** m_string_split(m_string* m, int* len, char delim)
{
    int k = 0;
    char** res = NULL;
    m_string tmp = m_string_init("");

    for (char* ptr = m->str; *ptr != '\0'; ++ptr) {
        if (*ptr == delim) {
            k++;
            if (!res) res = (char**)malloc(sizeof(char*) * k);
            else res = (char**)realloc(res, sizeof(char*) * k);
            res[k-1] = m_string_get(&tmp);
            m_string_clear(&tmp);
        } else m_string_push(&tmp, *ptr);
    }

    if (tmp.len > 0) {
        k++;
        if (!res) res = (char**)malloc(sizeof(char*) * k);
        else res = (char**)realloc(res, sizeof(char*) * k);
        res[k-1] = m_string_get(&tmp);
        m_string_clear(&tmp);
    }

    *len = k;
    return res;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
char** _m_string_getline_windows(m_string* m, int* len)
{
    int k = 0;
    char** res = NULL;
    m_string tmp = m_string_init("");

    for (char* ptr = m->str; *ptr != '\0'; ++ptr) {
        if (*ptr == '\r') {
            k++;
            ptr++;
            if (!res) res = (char**)malloc(sizeof(char*) * k);
            else res = (char**)realloc(res, sizeof(char*) * k);
            res[k-1] = m_string_get(&tmp);
            m_string_clear(&tmp);
        } else m_string_push(&tmp, *ptr);
    }

    if (tmp.len > 0) {
        k++;
        if (!res) res = (char**)malloc(sizeof(char*) * k);
        else res = (char**)realloc(res, sizeof(char*) * k);
        res[k-1] = m_string_get(&tmp);
        m_string_clear(&tmp);
    }

    *len = k;
    return res;
}
#endif