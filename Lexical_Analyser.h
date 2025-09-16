#ifndef LEXICAL_ANALYSER_H
#define LEXICAL_ANALYSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 100

// Arrays
extern const char *keywords[];
extern int keyword_count;

extern const char *Delimiters[];
extern int delimiter_count;

extern const char *Operator[];
extern int operator_count;

// Function declarations
bool isKeyword(char *word);
bool isDelimiter(char ch);
bool isOperatorStart(char ch);
bool matchOperator(char *str);
bool isNumber(char *token);
void classifyToken(char *token);
void analyzeFile(FILE *fp);

#endif
