#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// Functions used later
void ReadFile(char[3][20], float *);

int main(){
    char time[3][20];
    float temp[3];
    ReadFile(time, temp);

    return 0;
}

void ReadFile(char time[3][20], float *temp){
    FILE *fptr;
    fptr = fopen("data.txt", "r");

    if (fptr == NULL){
        printf("Error!");
        exit(-1);
    }

    char line[20];
    char ttime[20];
    char ttemp[20];
    int index = 0;
    // Read sentences:
    while (fgets(line, 100, fptr) != NULL) {
        // Read time stamp and temp
        strncpy(ttime, line, 5);
        strncpy(ttemp, line+6, 9);
        // Store time and temp in array
        temp[index] = atof(ttemp);
        *time[index] = *ttime;
        index++;
    }
}