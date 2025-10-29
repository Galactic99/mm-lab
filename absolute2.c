#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *input, *output;
    int staddr1, i, j;
    char line[100], name[20], uName[20], staddr[20];

    input = fopen("abs.txt", "r");
    output = fopen("output.txt", "w");

    if (!input) {
        printf("Error: Cannot open abs.txt\n");
        return 1;
    }

    fscanf(input, "%s", line);

    printf("Enter the name of the program: ");
    scanf("%s", uName);

    for (i = 2, j = 0; i < 8 && line[i] != '^'; i++, j++) {
        name[j] = line[i];
    }
    name[j] = '\0';

    if (strcmp(name, uName) == 0) {
        do {
            if (fscanf(input, "%s", line) == EOF)
                break;

            if (line[0] == 'T') {
                for (i = 2, j = 0; i < 8; i++, j++) {
                    staddr[j] = line[i];
                }
                staddr[j] = '\0';
                staddr1 = atoi(staddr);

                i = 12;

                while (line[i] != '$' && line[i] != '\0') {
                    if (line[i] != '^') {
                        fprintf(output, "%04d\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } else if (line[0] == 'E') {
                break;
            }

        } while (!feof(input));
    } else {
        printf("Program name mismatch. Expected: %s, Found: %s\n", uName, name);
    }

    fclose(input);
    fclose(output);
    printf("\nAbsolute Loader executed successfully. Output written to output.txt\n");
    return 0;
}
