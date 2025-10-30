#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 20
#define MAX_ARGUMENTS 10

char namtab[MAX_TABLE_SIZE][10];
int namtab_ptr = 0;

char deftab[MAX_TABLE_SIZE * MAX_ARGUMENTS][80];
int deftab_ptr = 0;

char argtab[MAX_ARGUMENTS][20];


void extract_arguments(char *opnd, int *arg_count) {
    int i = 0, j = 0;
    *arg_count = 0;
    
    for(int k=0; k<MAX_ARGUMENTS; k++) argtab[k][0] = '\0';
    
    while (opnd[i] != '\0' && *arg_count < MAX_ARGUMENTS) {
        j = 0;
        
        while(opnd[i] == ' ' || opnd[i] == '\t') i++;
        
        while (opnd[i] != '\0' && opnd[i] != ',') {
            argtab[*arg_count][j++] = opnd[i++];
        }
        argtab[*arg_count][j] = '\0';
        
        if (j > 0) {
             (*arg_count)++;
        }

        if (opnd[i] == ',') i++;
    }
}

int find_macro(char *mne) {
    for (int i = 0; i < namtab_ptr; i++) {
        if (strcmp(namtab[i], mne) == 0) {
            return i; 
        }
    }
    return -1; 
}

void main() {
    FILE *f1, *f5;
    char la[20], mne[20], opnd[20];
    int arg_count, macro_index, current_def_ptr;

    f1 = fopen("input.txt", "r");
    f5 = fopen("output.txt", "w"); 

    if (f1 == NULL || f5 == NULL) {
        printf("Error opening files.\n");
        return;
    }

    if (fscanf(f1, "%s%s%s", la, mne, opnd) != 3) {
        goto cleanup;
    }

    while (strcmp(mne, "END") != 0) {
        macro_index = find_macro(mne);

        if (strcmp(mne, "MACRO") == 0) {
            
            strcpy(namtab[namtab_ptr], la); 
            namtab_ptr++;

            sprintf(deftab[deftab_ptr], "%s\t%s", la, opnd); 
            deftab_ptr++;

            extract_arguments(opnd, &arg_count); 

            if (fscanf(f1, "%s%s%s", la, mne, opnd) != 3) goto cleanup;

            while (strcmp(mne, "MEND") != 0) {
                char temp_opnd[20];
                strcpy(temp_opnd, opnd); 
                
                for (int i = 0; i < arg_count; i++) {
                    char formal_param[20], positional[5];
                    
                    sprintf(formal_param, "&%s", argtab[i]); 
                    sprintf(positional, "?%d", i + 1); 
                    
                    if (strcmp(temp_opnd, formal_param) == 0) {
                        strcpy(temp_opnd, positional);
                        break; 
                    }
                }

                sprintf(deftab[deftab_ptr], "%s\t%s", mne, temp_opnd);
                deftab_ptr++;

                if (fscanf(f1, "%s%s%s", la, mne, opnd) != 3) goto cleanup;
            }
            strcpy(deftab[deftab_ptr], mne);
            deftab_ptr++;

        } else if (macro_index != -1) {
            
            printf("Expanding macro: %s\n", mne);

            extract_arguments(opnd, &arg_count);
            
            current_def_ptr = 0; 
            for(int i=0; i<deftab_ptr; i++){
                if(strcmp(deftab[i], mne) == 0){
                    current_def_ptr = i + 1;
                    break;
                }
            }
            if(current_def_ptr == 0)

            current_def_ptr++; 

            while (strcmp(deftab[current_def_ptr], "MEND") != 0) {
                char body_line[80], body_mne[20], body_opnd[20];
                
                strcpy(body_line, deftab[current_def_ptr]);
                sscanf(body_line, "%s%s", body_mne, body_opnd);

                if (body_opnd[0] == '?') {
                    int pos = atoi(body_opnd + 1) - 1; 
                    
                    if (pos >= 0 && pos < arg_count) {
                        fprintf(f5, "-\t%s\t%s\n", body_mne, argtab[pos]);
                    } else {
                        fprintf(f5, "Error: Missing arg for pos %d\n", pos + 1);
                    }
                } else {
                    fprintf(f5, "-\t%s\t%s\n", body_mne, body_opnd);
                }
                current_def_ptr++;
            }
            
        } else {
            fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
        }

        if (fscanf(f1, "%s%s%s", la, mne, opnd) != 3) {
            break;
        }
    }

    fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
    printf("Successful! Output written to output.txt\n");

cleanup:
    if (f1) fclose(f1);
    if (f5) fclose(f5);
}
