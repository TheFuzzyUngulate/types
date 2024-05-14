#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define m_string_getline(m, len) m_string_split(m, len, '\n')