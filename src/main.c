#include <stdio.h>
#include <stdlib.h>

double expression(void);

double vars[26];

char get(void) { char c = getchar(); return c; } // get one byte
char peek(void) { char c = getchar(); ungetc(c, stdin); return c; }
double number(void) { double d; scanf("%lf", &d); return d; }

void expect(char c) {
    char d = get();
    if (c != d) {
        fprintf(stderr, "\n"
                        "Error: Expected %c but got %c.\n"
                        , c, d);
    }
}

double factor(void) {
    double f;
    char c = peek();
    if (c == '(') {
        expect('(');
        f = expression();
        expect(')');
    } else if (c >= 'A' && c <= 'Z') {
        expect(c);
        f = vars[c - 'A'];
    } else {
        f = number();
    }
    return f;
}

double term(void) {
    double t = factor();
    while (peek() == '*' || peek() == '/') {
        char c = get();
        if (c == '*') {
            t = t * factor();
        } else {
            t = t / factor();
        }
    }
    return t;
}

double expression(void) {
    double e = term();
    while (peek() == '+' || peek() == '-') {
        char c = get();
        if (c == '+') {
            e = e + term();
        } else {
            e = e - term();
        }
    }
    return e;
}

double statement(void) {
    double ret;
    char c = peek();
    if (c >= 'A' && c <= 'Z') {
        expect(c);
        if (peek() == '=') {
            expect('=');
            double val = expression();
            vars[c - 'A'] = val;
            ret = val;
        } else {
            ungetc(c, stdin);
            ret = expression();
        }
    } else {
        ret = expression();
    }
    expect('\n');
    return ret;
}

int main(void) {
    printf("> "); fflush(stdout);

    for (;;) {
        double v = statement();
        printf(" = %lf\n> ", v); fflush(stdout);
    }
    return EXIT_SUCCESS;
}