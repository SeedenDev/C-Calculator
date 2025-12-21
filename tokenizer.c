//
// Created by Seeden on 2025/05/09.
//

#include "tokenizer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

TokenType getTokenTypeFromSymbol(const string* symbol) {
    if(streqc(symbol, "+")) return PLUS;
    if(streqc(symbol, "-")) return MINUS;
    if(streqc(symbol, "*")) return MULTIPLY;
    if(streqc(symbol, "/")) return DIVIDE;
    if(streqc(symbol, "(")) return OPEN_BRACKET;
    if(streqc(symbol, ")")) return CLOSE_BRACKET;
    if(streqc(symbol, "^")) return POWER;
    if(streqc(symbol, "sqrt")) return SQRT;
    if(streqc(symbol, "E")) return E10;
    if(streqc(symbol, "pi")) return PI;
    if(streqc(symbol, "%")) return PERCENTAGE;
    if(streqc(symbol, "abs")) return ABS;
    if(streqc(symbol, "cos")) return COS;
    if(streqc(symbol, "sin")) return SIN;
    if(streqc(symbol, "tan")) return TAN;
    if(streqc(symbol, "acos")) return ACOS;
    if(streqc(symbol, "asin")) return ASIN;
    if(streqc(symbol, "atan")) return ATAN;
    if(streqc(symbol, "exp")) return EXP;
    if(streqc(symbol, "e")) return EULER;
    if(streqc(symbol, "log")) return LOG10;
    if(streqc(symbol, "logb")) return LOG2;
    if(streqc(symbol, "ln")) return LN;
    if(streqc(symbol, "!")) return FACTORIAL;
    return UNKNOWN;
}

bool isFakeSpecialCase(const TokenType* tokenType, const char* ptr) {
    if (*tokenType==EULER) {
        if (*ptr!='\0' && *(ptr+1)!='\0') return *ptr=='x' && *(ptr+1)=='p';
    }
    else if (*tokenType==LOG10) {
        if (*ptr!='\0') return *ptr=='b';
    }
    return false;
}

void tokenize(const string* formula, TokenList* outTokenList) {
    TokenList tokensList = initlist();

    char* ptr = formula->data;
    string buffer = initstrl(10);
    bool digit = false;
    while (*ptr != '\0') {
        const char c = *ptr;
        printf("%c|%p-%p\n", c, formula->data, ptr);
        if (isdigit(c) || c=='.') {
            if (!digit && !strisempty(&buffer)) {
                const TokenType tokenType = getTokenTypeFromSymbol(&buffer);
                if (tokenType!=UNKNOWN) {
                    Token token = symbolToken(tokenType);
                    listadd(&tokensList, &token);
                    cleanstr(&buffer);
                }
                else {
                    printf("Invalid expression, unknown token: %s", buffer.data);
                    destroystr(&buffer);
                    destroylist(&tokensList);
                    exit(EXIT_FAILURE);
                }
            }
            digit = true;
            printf("WEREHERE: %c/", c);
            printf("%s/", &c);
            printf("%p ; ", &c);
            printf("%c/", *ptr);
            printf("%s/", ptr);
            printf("%p\n", ptr);
            appendchar(&buffer, c);
        }
        else if (isalpha(c) || ispunct(c)) {
            if (digit) {
                printf("NANI? %s/", buffer.data);
                Token token = numberToken(buffer.data);
                listadd(&tokensList, &token);
                cleanstr(&buffer);
            }
            else {
                const TokenType tokenType = getTokenTypeFromSymbol(&buffer);
                if (tokenType!=UNKNOWN && !isFakeSpecialCase(&tokenType, ptr)) {
                    Token token = symbolToken(tokenType);
                    listadd(&tokensList, &token);
                    cleanstr(&buffer);
                }
            }
            digit = false;
            appendchar(&buffer, c);
        }
        else if (!isspace(c)){
            printf("Expression contains invalid character: %c", c);
            destroystr(&buffer);
            destroylist(&tokensList);
            exit(EXIT_FAILURE);
        }
        ++ptr;
    }
    if (!strisempty(&buffer)) {
        TokenType tokenType = UNKNOWN;
        if (isdigit(buffer.data[0])) {
            tokenType = NUMBER;
        }
        else tokenType = getTokenTypeFromSymbol(&buffer);
        if (tokenType==UNKNOWN){
            printf("Invalid expression, unknown token: %s", buffer.data);
            destroystr(&buffer);
            destroylist(&tokensList);
            exit(EXIT_FAILURE);
        }
        Token token = {.type = tokenType};
        if (tokenType==NUMBER) {
            token.value = initstrd(buffer.data);
        }
        listadd(&tokensList, &token);
    }
    destroystr(&buffer);
    outTokenList->data = tokensList.data;
    outTokenList->size = tokensList.size;
    outTokenList->max_size = tokensList.max_size;
    //memcpy(outTokenList->data, tokensList.data, sizeof(Token)*tokensList.size);
    //destroylist(&tokensList);
}