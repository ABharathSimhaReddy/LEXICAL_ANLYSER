#include "lexical_analyser.h"

// Keywords
const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof",
    "static","struct","switch","typedef","union","unsigned","void",
    "volatile","while"
};
int keyword_count = 32;

// Delimiters
const char *Delimiters[] = {
    " ", "\t", "\n", ",", ";", "(", ")", "{", "}", "[", "]", ".", "->", ":", "?", "#"
};
int delimiter_count = 16;

// Operators
const char *Operator[] = {
    "+","-","*","/","%","=","==","!=",
    ">","<",">=","<=","++","--","+=","-=",
    "*=","/=","%=","&","|","&&","||","!",
    "~","^","<<",">>","<<=",">>=","&=","|=","^="
};
int operator_count = 32;

// Check keyword
bool isKeyword(char *word) {
    for(int i=0;i<keyword_count;i++)
        if(strcmp(word,keywords[i])==0) return true;
    return false;
}

// Check delimiter (single char)
bool isDelimiter(char ch) {
    for(int i=0;i<delimiter_count;i++)
        if(ch == Delimiters[i][0]) return true;
    return false;
}

// Check if char can start an operator
bool isOperatorStart(char ch) {
    for(int i=0;i<operator_count;i++)
        if(ch == Operator[i][0]) return true;
    return false;
}

// Match string with operator array
bool matchOperator(char *str) {
    for(int i=0;i<operator_count;i++)
        if(strcmp(str,Operator[i])==0) return true;
    return false;
}

// Check if token is number
bool isNumber(char *token){
    int dot=0;
    for(int i=0; token[i]!='\0'; i++){
        if(token[i]=='.') dot++;
        else if(!isdigit(token[i])) return false;
    }
    return true;
}

// Classify token
void classifyToken(char *token) {
    if(strlen(token)==0) return;
    if(isKeyword(token))
        printf("Keyword: %s\n", token);
    else if(isNumber(token))
        printf("Number: %s\n", token);
    else
        printf("Identifier: %s\n", token);
}

// Analyze file
// Function to read a file and print tokens
void analyzeFile(FILE *fp) {
    char ch, next;
    char token[SIZE]; // To store each token
    int t_index = 0;  // Index for token array

    while ((ch = fgetc(fp)) != EOF) { // Read file character by character

        // 1. Skip preprocessor lines starting with #
        if (ch == '#') {
            while ((ch = fgetc(fp)) != EOF && ch != '\n'); // Skip till end of line
        }

        // 2. Skip comments
        else if (ch == '/') {
            next = fgetc(fp);
            
            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
            }
            // Multi-line comment
            else if (next == '*') {
                int prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
            }
            // Division operator '/'
            else {
                if (t_index > 0) {
                    token[t_index] = '\0';
                    classifyToken(token); // Print token before operator
                    t_index = 0;
                }
                printf("Operator: %c\n", ch);
                ungetc(next, fp); // Put the next character back
            }
        }

        // 3. String literals
        else if (ch == '"') {
            if (t_index > 0) {
                token[t_index] = '\0';
                classifyToken(token);
                t_index = 0;
            }
            printf("String literal: \"");
            while ((ch = fgetc(fp)) != EOF && ch != '"') putchar(ch);
            printf("\"\n");
        }

        // 4. Delimiters (like ;, (), {}, [], etc.)
        else if (isDelimiter(ch)) {
            if (t_index > 0) {
                token[t_index] = '\0';
                classifyToken(token);
                t_index = 0;
            }
            if (ch != ' ' && ch != '\t' && ch != '\n') // Skip spaces
                printf("Delimiter: %c\n", ch);
        }

        // 5. Operators (like +, -, *, ==, !=, etc.)
        else if (isOperatorStart(ch)) {
            if (t_index > 0) {
                token[t_index] = '\0';
                classifyToken(token);
                t_index = 0;
            }

            char op[3]; // To store 1 or 2 character operators
            op[0] = ch;
            op[1] = fgetc(fp);
            op[2] = '\0';

            if (matchOperator(op)) // Check if it's a valid operator
                printf("Operator: %s\n", op);
            else {
                printf("Operator: %c\n", ch);
                ungetc(op[1], fp); // Put back the second char if not part of operator
            }
        }

        // 6. Part of a token (identifier, keyword, or number)
        else {
            token[t_index++] = ch; // Add character to token
        }
    }

    // Print the last token if any
    if (t_index > 0) {
        token[t_index] = '\0';
        classifyToken(token);
    }
}
