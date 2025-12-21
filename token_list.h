//
// Created by Seeden on 2025/05/11.
//

#pragma once

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include <stdlib.h>

#include "token.h"

#endif //LIST_H

typedef struct {
    size_t max_size;
    size_t size;
    Token* data;
} TokenList;

TokenList initlist();

void expandlist(TokenList *list, const size_t size);

void shrinklist(TokenList *list, const size_t size);

size_t listadd(TokenList* list, Token* token);

Token listremove(TokenList* list, const size_t index);

Token* listget(const TokenList* list, size_t index);

bool listcontains(const TokenList* list, const Token* token);

bool listisempty(const TokenList* list);

void clearlist(TokenList* list);

void printlist(const TokenList* list);

void destroylist(TokenList* list);
