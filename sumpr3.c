#include "sumpr3.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s input_file output_file pattern replacement\n", argv[0]);
        return 1;
    }

    setlocale(LC_ALL, "RUS");
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];
    const char *pattern = argv[3];
    const char *replacement = argv[4];

 
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    replace(inputFile, outputFile, pattern, replacement);

    fclose(inputFile);
    fclose(outputFile);

    printf("Replacement complete.\n");

    return 0;
}