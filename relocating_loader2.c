#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[20];
char bit[40];

void convert(char h[]) {
    int i, l;
    strcpy(bit, "");
    l = strlen(h);

    for (i = 0; i < l; i++) {
        switch (h[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': case 'a': strcat(bit, "1010"); break;
            case 'B': case 'b': strcat(bit, "1011"); break;
            case 'C': case 'c': strcat(bit, "1100"); break;
            case 'D': case 'd': strcat(bit, "1101"); break;
            case 'E': case 'e': strcat(bit, "1110"); break;
            case 'F': case 'f': strcat(bit, "1111"); break;
        }
    }
}

int main() {
    char input[10], pn[10];
    int start, addr, len, address, opcode, actualadd, tlen, i;
    char relocbit;

    FILE *fp1, *fp2;
    fp1 = fopen("rel_input.txt", "r");
    fp2 = fopen("rel_output.txt", "w");

    if (!fp1) {
        printf("Error: rel_input.txt not found!\n");
        return 1;
    }

    printf("Enter the actual starting address (in hex): ");
    scanf("%x", &start);

    while (fscanf(fp1, "%9s", input) == 1) {
        if (strcmp(input, "E") == 0)
            break;

        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s", pn);
            fscanf(fp1, "%x", &addr);
            fscanf(fp1, "%x", &len);
        }

        else if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);
            fscanf(fp1, "%x", &tlen);
            fscanf(fp1, "%s", bitmask);

            address += start;
            convert(bitmask);

            int bitlen = strlen(bit);
            for (i = 0; i < bitlen; i++) {
                if (fscanf(fp1, "%x", &opcode) == EOF) break;
                if (fscanf(fp1, "%x", &addr) == EOF) break;

                relocbit = bit[i];
                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = start + addr;

                fprintf(fp2, "%04X\t%02X\t%04X\n", address, opcode, actualadd);
                address += 3;
            }
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("\nRelocating Loader executed successfully.\nOutput written to rel_output.txt\n");
    return 0;
}
