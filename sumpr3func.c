#include "sumpr3.h"

void replace(FILE* inputFile, FILE* outputFile, const char* pattern, const char* replacement) {

	char buffer[BUFFER_SIZE];

	size_t patternLength = strlen(pattern);
	size_t replacementLength = strlen(replacement);
	if (strlen(pattern) > MAX_PATTERN_SIZE) {
		printf("Превышена длина исходной подстроки\n");
		exit(1);
	}
	size_t countSame = 0;
	size_t flag = 0, flajok = 0;
	size_t saveLen = 0, indexMemory = 0, saveLen1 = 0;
	size_t readNew = 0;
	size_t check = 0;
	size_t choice = 0;
	size_t empty = 0;

	while (!feof(inputFile)) {

		size_t i;
		size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, inputFile);
		size_t indexPattern = 0;
		empty = 0;
		for (i = 0; i < bytesRead; i++) {

			if (buffer[i] == pattern[0] || readNew == 1 || check >= 1) {
				if (check >= 1) {
					countSame = 0;

					int a = 0;
					int k;
					int q = 0;
					int status = 0;
					int decrease = 0;
					int savecheck = check;
					int checkend = 0;
					for (k = savecheck; q < savecheck; ) {
						
						if (decrease) 
							a++;
						if (buffer[i] == pattern[k]) {
							
							for (size_t j = savecheck; j < patternLength; j++) {
								if (buffer[a] == pattern[j]) {
									countSame++;
									a++;
									if (countSame + check == patternLength) {
										saveLen1 = patternLength - check;
										countSame = patternLength;
										q = check;
										k = patternLength;
										break;
									}
								}
								else if (buffer[i + j] < 0) {
									saveLen = countSame;
									readNew = 1;
									check = countSame;
									break;
								}
								else {
									checkend++;
									status = 1;
									fwrite(&pattern[indexPattern], sizeof(char), 1, outputFile);
									k = check - 1;
									q++;
									indexPattern++;
									countSame = 0;
									a = 0;
									j = 0;
									if (checkend == savecheck) {
										j = patternLength;
									}
								}
							}
							checkend = 0;
						}
						else if (readNew == 1) {
							checkend++;
							
							fwrite(&pattern[indexPattern], sizeof(char), 1, outputFile);
							q++;
							i++;
							indexPattern++;
							decrease = 1;
							countSame = 0;
						}
						else {

							fwrite(&buffer[q], sizeof(char), 1, outputFile);
							countSame = 0;
							indexMemory = 0;
							saveLen = 0;
						}
					}
					check = 0;
					choice = 1;
					
					if (empty == 0 && countSame + check != patternLength) {
						i = -1;
						empty = 1;
						k = 0;
					}
				}
				indexPattern = 0;
				int k = 0;
				if (check == 0 && choice == 0) {
					if (buffer[i] == pattern[0]) {
						for (size_t j = 0 ;j < patternLength; j++) {

							if (readNew == 1 && saveLen != 0) {
								readNew = 0;

								for (; k < patternLength; k++, j++) {

									if (buffer[j] == pattern[k]) {
										countSame++;
										indexMemory++;
									}
									else {
										saveLen = 0;
										break;
									}
								}
								flajok = 1;
								break;
							}
							if (buffer[i + j] == pattern[j]) {
								countSame++;
							}
							else if (buffer[i + j] < 0) {
								saveLen = countSame;
								readNew = 1;
								check = countSame;
								i += countSame;
								break;
							}
							else {
								flajok = 0;
								readNew = 0;
								break;
							}
						}
					}
					else {
						fwrite(&buffer[i], sizeof(char), 1, outputFile);
						countSame = 0;
						indexMemory = 0;
						saveLen = 0;
					}
				}

				if (countSame == patternLength) {

					fwrite(replacement, sizeof(char), replacementLength, outputFile);
					countSame = 0;
					indexMemory = 0;
					if (flajok) {
						i += patternLength - 1;
						flajok = 0;
					}
					else if (choice) {
						i += saveLen1 - 1;
						readNew = 0;
						saveLen = 0;
						saveLen1 = 0;
					}
					else
						i += patternLength - 1;
				}
				else if (countSame < patternLength && readNew == 0) {
					fwrite(&buffer[i], sizeof(char), 1, outputFile);
					indexMemory = 0;
					countSame = 0;
				}
				choice = 0;
			}
			else {
				fwrite(&buffer[i], sizeof(char), 1, outputFile);
				countSame = 0;
				indexMemory = 0;
				saveLen = 0;
			}
		}
	}
}
