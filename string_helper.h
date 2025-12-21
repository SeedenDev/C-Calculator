//
// Created by Seeden on 2025/05/11.
//

#pragma once

#ifndef STRING_HELPER_H
#define STRING_HELPER_H
#include <stdbool.h>
#include <stdlib.h>

#define emptyStr() initstrl(0)

#endif //STRING_HELPER_H

typedef struct {
    char* data;
    size_t max_size;
    size_t cursor;
} string;

string initstrl(const size_t length);

string initstrd(char data[]);

void resizestr(string* str, const size_t size);

void expandstr(string *str, const size_t size);

void shrinkstr(string *str, const size_t size);

void setcharat(string* str, const char c, const size_t pos);

void appendchar(string* str, const char c);

void appendstr(string* str, const char* src);

void cleanstr(string* str);

bool streqc(const string* str, const char* c);

bool streqs(const string* str1, const string* str2);

bool strisempty(const string* str);

void printstr(const string* str);

void destroystr(string* str);