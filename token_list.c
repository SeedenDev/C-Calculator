//
// Created by Seeden on 2025/05/11.
//

#include "token_list.h"

#include <stdio.h>
#include <string.h>

TokenList initlist() {
    Token* ptr = malloc(10*sizeof(Token));
    if (ptr == NULL) {
        printf("Error allocating memory for list.\n");
        exit(EXIT_FAILURE);
    }
    TokenList list = {.max_size = 10, .size = 0, .data = ptr};
    return list;
}

void expandlist(TokenList* list, const size_t size) {
    printf("Expanding list..");
    const size_t new_size = list->max_size + size;
    Token* ptr = realloc(list->data, new_size*sizeof(Token));
    //Token* ptr = malloc(size*sizeof(Token));
    //memcpy(ptr, list->data, list->max_size*sizeof(Token));
    if (ptr==NULL) {
        printf("Error while reallocating (expanding list) memory at address: %p", list->data);
        free(list->data);
        exit(EXIT_FAILURE);
    }
    list->data = ptr;
    list->max_size = new_size;
    printf("Expanded list size to %llu\n", list->max_size);
}

void shrinklist(TokenList* list, const size_t size) {
    printf("Shrinking list (attempt)..\n");
    Token* ptr = realloc(list->data, size*sizeof(Token));
    if (ptr==NULL) {
        printf("Error while reallocating (list) memory at address: %p (listremove() shrinking)", list->data);
        free(list->data);
        exit(EXIT_FAILURE);
    }
    list->data = ptr;
    list->max_size = size;
    printf("Shrinked list size to %llu\n", list->max_size);
}

size_t listadd(TokenList* list, Token* token) {
    if (list->size>=list->max_size) expandlist(list, list->max_size);
    const size_t cursor = /*list->unit_size**/list->size;
    printf("Size: %llu, MaxSize: %llu, Cursor: %llu\n", list->size, list->max_size, cursor);
    list->data[cursor] = *token;
    list->size += 1;

    printf("Add %d to [%p]\n", token->type, list->data);

    return list->size-1; // Return the index of the entry
}

Token listremove(TokenList* list, const size_t index) {
    if (index>=list->size) {
        printf("Warning: trying to remove a data out of bound (index:%llu over a size of %llu)\n", index, list->size);
        return;
    }
    printf("Removing %llu on list [%llu;%llu]\n", index, list->size, list->max_size);
    Token* item = &list->data[index];
    Token removedToken = *item; // We retrieve the token data
    // Then, "clear" the data at index, moving all the elements after the index one step before
    memcpy(item, &list->data[index+1], sizeof(Token)*(list->size-index-1));
    // And finally, "clear" the data of the former last element of the list by just lowering the "size" value
    list->size -= 1;
    // BUT, if difference between size and maxSize become to big, realloc to free memory of the last unused elements
    if (list->size <= list->max_size/4) shrinklist(list, list->max_size/2);
    return removedToken;
}

Token* listget(const TokenList* list, const size_t index) {
    if (index>=list->size) {
        printf("Warning: trying to access a data out of bound (index:%llu over a size of %llu)\n", index, list->size);
        return NULL;
    }
    return &list->data[index];
}

bool listcontains(const TokenList* list, const Token* token) {
    printf("COMPARE: %d ; %s\n", token->type, token->value.data);
    const TokenType tokenType = token->type;
    for (size_t i = 0; i < list->size; i++) {
        const Token tokenI = list->data[i];
        printf("With %llu: %d ; %s\n", i, tokenI.type, tokenI.value.data);
        // If the searched token is a number, don't care to check if the iterated one is also a NUMBER.
        // If it's not, it's value is defaulted to "" at instancing, so it'll be false.
        // But yeah for performance matter, maybe checking if the iterated token is a NUMBER to prevent
        // the "equality" calculation if not.
        if (tokenType == NUMBER && streqs(&token->value, &tokenI.value)) return true;
        if (token->type == tokenI.type) return true;
    }
    return false;
}

bool listisempty(const TokenList* list) {
    return list->size==0;
}

void clearlist(TokenList* list) {
    printf("Clearing list\n");
    for(size_t i = 0; i < list->size; i++){
        destroystr(&list->data[i].value);
    }
    free(list->data);
    Token* ptr = malloc(10*sizeof(Token));
    if (ptr == NULL) {
        printf("Error allocating memory for cleared list.\n");
        exit(EXIT_FAILURE);
    }
    list->data = ptr;
    list->size = 0;
    list->max_size = 10;
}

void printlist(const TokenList* list) {
    printf("-----------------\n");
    if (listisempty(list)) printf("LIST IS EMPTY\n");
    for (size_t i = 0; i < list->size; i++) {
        const Token token = list->data[i];
        const int tokenType = token.type;
        char* value = tokenType==NUMBER ? token.value.data : "Nothing";
        printf("Token[%p] %llu: %s(%s)\n", &list->data[i], i, mapping[tokenType-1], value);
    }
    printf("-----------------\n");
}

void destroylist(TokenList* list) {
    for(size_t i = 0; i < list->size; i++){
        destroystr(&list->data[i].value);
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->max_size = 0;
}