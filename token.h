//
// Created by Seeden on 2025/05/17.
//

#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include "string_helper.h"

#endif //TOKEN_H

#define numberToken(value) {NUMBER, initstrd(value)}
#define symbolToken(token) {token, emptyStr()}

typedef enum TokenType {
    UNKNOWN, NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, OPEN_BRACKET, CLOSE_BRACKET, POWER, // formula ready
    SQRT, E10, PI, PERCENTAGE, ABS, // Add to formula
    COS, SIN, TAN, ACOS, ASIN, ATAN, EULER, EXP, LOG10, LOG2, LN, FACTORIAL // "Later"
} TokenType;

static const char* mapping[] = {"nb", "+", "-", "*", "/", "(", ")", "^", "sqrt", "E", "pi", "%", "abs", "cos", "sin", "tan", "acos", "asin", "atan",
                            "e", "exp", "log", "logb", "ln", "!"};

typedef struct {
    TokenType type;
    string value; // For number (parser creates integer/long/float/double after cast check)
    // (and then creates the tree passed to solver, priority is working (thanks to the tree) and it should be the one
    // in charge of throwing errors if the formula is wrecked "There should be a NUMBER after ^ bro"
    // because it will check for the token after a ^ to be a NUMBER, if not THROW ERROR.
    // And it's because things are resolved by priority: if there were () after ^ np bc it would have been transformed
    // in a NUMBER in the tree. Well, it should. So yeah, "parsing" creates a tree of priority. And "solving" only go through it.
} Token;