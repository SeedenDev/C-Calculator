//
// Created by Seeden on 2025/05/11.
//

#include "string_helper.h"

#include <stdio.h>
#include <string.h>

string initstrl(const size_t length) {
    char* ptr = malloc(length+1);
    if (ptr==NULL) {
        printf("Error allocating memory for string (length).\n");
        exit(EXIT_FAILURE);
    }
    memset(ptr, ' ', length);
    ptr[length] = '\0';
    const string str = {.data=ptr, .max_size=length, .cursor=0};
    return str;
}

string initstrd(char data[]) {
    const size_t length = strlen(data);
    char* ptr = malloc(length+1);
    if (ptr == NULL) {
        printf("Error allocating memory for string (data).\n");
        exit(EXIT_FAILURE);
    }
    //memmove(ptr, data, length+1);
    strcpy(ptr, data);
    //ptr[length] = '\0';
    printf("TEKI%s|%s\n", ptr, data);
    const string str = {.data=ptr, .max_size=length, .cursor=length};
    return str;
}

void resizestr(string *str, const size_t size) {
    if (size==str->max_size) {
        printf("Warning: attempting to resize a string to its current size.");
        return;
    }
    if (size<str->max_size) {
        printf("Warning: shrinking string size is not supported.");
        return;
    }
    char* ptr = realloc(str->data, size+1);
    printf("TOI%p:%s\n|", ptr, ptr);
    if (ptr==NULL) {
        printf("Error while reallocating memory at address: %p", str->data);
        free(str->data);
        exit(EXIT_FAILURE);
    }
    str->data = ptr;
    for (size_t i = str->max_size; i < size; i++) {
        str->data[i] = ' ';
    }
    str->max_size = size;
    str->data[size] = '\0';
    printf("LUI%p=%s\n|", str->data, str->data);
}

void expandstr(string *str, const size_t size) {
    resizestr(str, str->max_size+size);
}

void shrinkstr(string *str, const size_t size) {
    printf("Currently not supported");
}

void setcharat(string *str, const char c, const size_t pos) {
    if (pos>=str->max_size) expandstr(str, 10);
    if (str->cursor<pos) {
        for (size_t i = str->cursor; i < pos; i++) {
            str->data[i] = ' ';
        }
    }
    str->data[pos] = c;
    if (str->cursor<=pos) {
        str->cursor = pos+1;
        str->data[str->cursor] = '\0';
    }
}

void appendchar(string *str, const char c) {
    setcharat(str, c, str->cursor);
}

void appendstr(string *str, const char *src) {
    // "Hello_____" + " World!" = "Hello WorlXX" -> 10+7=17 but starting from index 5 = 5+7=12
    if (strlen(src)==0) {
        printf("Warning: attempting to append a blank string.");
        return;
    }
    if (strlen(src)>1) {
        if (str->cursor+strlen(src)>=str->max_size) expandstr(str, strlen(src));
        printf("Avant:");
        printstr(str);
        printf("Adding %s to %s\n", src, str->data);
        strncpy(str->data+str->cursor, src, strlen(src));
        str->cursor += strlen(src);
        printf("Après:");
        printstr(str);
        str->data[str->cursor] = '\0';
    }
    else appendchar(str, *src);
}

void cleanstr(string* str) {
    memset(str->data, ' ', str->max_size+1);
    str->data[str->max_size] = '\0';
    str->cursor = 0;
}

bool streqc(const string* str, const char* c) {
    return strcmp(str->data, c)==0;
}

bool streqs(const string* str1, const string* str2) {
    if (str1==NULL || str2==NULL) {
        printf("Warning: comparing to string in which one of them is a NULL ptr.\n");
        return false;
    }
    if (str1->data==NULL || str2->data==NULL) {
        printf("Warning: comparing to string in which one of them has a value being a NULL ptr.\n");
        return false;
    }
    return strcmp(str1->data, str2->data)==0;
}

bool strisempty(const string* str) {
    return str->cursor==0;
}

void printstr(const string* str) {
    printf("Data(adr): %p; Data: %s; max_size: %llu; cursor: %llu\n", str->data, str->data, str->max_size, str->cursor);
}

void destroystr(string* str) {
    free(str->data);
    str->data = NULL;
}