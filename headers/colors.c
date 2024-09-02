#include "colors.h"
#include <stdio.h>

// ANSI color codes
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

void printf_error(const char* text) {
  fprintf(stderr, "%s%s%s", RED, text, RESET);
}

void printf_red(const char* text) {
  printf("%s%s%s", RED, text, RESET);
}

void printf_green(const char* text) {
  printf("%s%s%s", GREEN, text, RESET);
}

void printf_yellow(const char* text) {
  printf("%s%s%s", YELLOW, text, RESET);
}

void printf_blue(const char* text) {
  printf("%s%s%s", BLUE, text, RESET);
}

void printf_magenta(const char* text) {
  printf("%s%s%s", MAGENTA, text, RESET);
}

void printf_cyan(const char* text) {
  printf("%s%s%s", CYAN, text, RESET);
}

void printf_white(const char* text) {
  printf("%s%s%s", WHITE, text, RESET);
}

void red() {
  printf("%s", RED);
}

void green() {
  printf("%s", GREEN);
}

void yellow() {
  printf("%s", YELLOW);
}

void blue() {
  printf("%s", BLUE);
}

void magenta() {
  printf("%s", MAGENTA);
}

void cyan() {
  printf("%s", CYAN);
}

void white() {
  printf("%s", WHITE);
}

void reset_color() {
  printf("%s", RESET);
}
