#ifndef MSTRING_H
#define MSTRING_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_STRING_INCR 5
#define M_STRING_STARTER_LEN (1 << M_STRING_INCR)

typedef struct
m_string
{
    char* str;
    size_t len;
}
m_string;

m_string m_string_init(const char*);
void m_string_push(m_string* m, char ch);
void m_string_concat(m_string* m, const char* str);
char* m_string_get(m_string* m);
void m_string_clear(m_string* m);
char** m_string_split(m_string* m, int* len, char delim);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
char** _m_string_getline_windows(m_string* m, int* len);
#define m_string_getline(m, len) _m_string_getline_windows(m, len)
#else
#define m_string_getline(m, len) m_string_split(m, len, '\n')
#endif

#endif