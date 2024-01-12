#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define BUFFER_SIZE 5
#define MAX_PATTERN_SIZE 8

void replace(FILE *inputFile, FILE *outputFile, const char *pattern, const char *replacement);