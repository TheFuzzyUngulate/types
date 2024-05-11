#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mstring.h"

m_string m_string_init()
{
    m_string m;

    m.len = 0;
    m.str = (char*)calloc(128, 1);

    return m;
}

void m_string_push(m_string* m, char ch)
{
    if ((m->len + 2) % 128 == 0) {
        m->str = (char*)realloc(m->str, (m->len + 1) + 128);
        memset(m->str + m->len + 1, 0, 128);
    }
    *(m->str + m->len) = ch;
    m->len++;
}

void m_string_concat(m_string* m, char* str)
{
    char* buf;
    size_t al;
    size_t bl;
    size_t tl;

    al = (m->len + 1);
    if (al % 128 != 0) {
        al &= ~((1 << 7) - 1);
        al += 128; 
    }

    bl = strlen(str);
    
    tl = al + bl;
    if (tl % 128 != 0) {
        tl &= ~((1 << 7) - 1);
        tl += 128;
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
    m->str = (char*)calloc(128, 1);
}

char** m_string_split(m_string* m, int* len, char delim)
{
    int k = 0;
    char** res = NULL;
    m_string tmp = m_string_init();

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