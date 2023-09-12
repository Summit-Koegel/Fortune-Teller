#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]) {

    char* file = NULL;
    char* numN = NULL;
    char* numB = NULL;
    char* numO = NULL;
    int tracker;
    int oFlag;

    if(argc < 5){
        printf("USAGE: \n\tbadger-fortune -f <file> -n <number> (optionally: -o <output file>) \n\t\t OR \n\tbadger-fortune -f <file> -b <batch file> (optionally: -o <output file>)\n");
	    exit(1);
    }

    int error_count1;
    int nbcounter;
    for(int i = 1; i < argc; i=i+2){
        if(strcmp(argv[i], "-f") == 0){
            file = argv[i+1];

            error_count1 = error_count1 + 1;
        }

        else if(strcmp(argv[i], "-n") == 0){
            numN = argv[i+1];
            tracker = 1;
            if(nbcounter == 0){
            nbcounter = 1;
            }
            else{
                printf("ERROR: You can't specify a specific fortune number in conjunction with batch mode\n");
                exit(1);	
            }
        }

        else if(strcmp(argv[i], "-b") == 0){
            numB = argv[i+1];
            tracker = 2;
            if(nbcounter == 0){
                nbcounter = 1;
            }
            else{
                printf("ERROR: You can't use batch mode when specifying a fortune number using -n\n");
                exit(1);
            }

        }

        else if(strcmp(argv[i], "-o") == 0){
            numO = argv[i+1];
            oFlag = 1;
        }

        else{
            printf("ERROR: Invalid Flag Types\n");
            exit(1);
        }

        
    }

    if(error_count1 == 0){
        printf("ERROR: No fortune file was provided\n");
        exit(1);
    }


    char* num_fortune = malloc(sizeof(char) * 1024);
    char* max_length = malloc(sizeof(char) * 1024);

    FILE *fp = fopen(file, "r"); 
        if (fp == NULL) { 
            printf("ERROR: Can't open fortune file\n");
            exit(1); 
        }
    
        
    fgets(num_fortune, sizeof(char) * 1024, fp);
    fgets(max_length, sizeof(char) * 1024, fp);

    if(strcmp(num_fortune, "") == 0 && strcmp(max_length, "") == 0){
        printf("ERROR: Fortune File Empty\n");
        exit(1);
    }

    int buffer = 80;
    char* temp = malloc(sizeof(char) * buffer);
    char* temp2 = malloc(sizeof(char) * buffer);
    char* fortunes[atoi(num_fortune)];
    char* batchNums[atoi(num_fortune)];
    fgets(temp, sizeof(char) * buffer, fp);
    for(int i = 0; i < atoi(num_fortune); i++){
        
        fortunes[i] = malloc(sizeof(char) * atoi(max_length));

        while(fgets(temp, sizeof(char) * buffer, fp) && strcmp(temp, "%\n") != 0){
            strcat(fortunes[i], temp);
        }
        
    }
    

    if(tracker == 1){
        if(atoi(numN) <= 0){
            printf("ERROR: Invalid Fortune Number\n");
            exit(1);
        }
        else if(atoi(numN) > atoi(num_fortune)){
            printf("ERROR: Invalid Fortune Number\n");
            exit(1);
        }
        else if(fortunes[atoi(numN) - 1] == NULL){
            printf("ERROR: Fortune File Empty\n");
            exit(1);
        }

        else if(oFlag == 1){
            FILE *output1 = fopen(numO, "w"); 
            if (output1 == NULL) { 
                printf("ERROR: Can't open output file\n");
                exit(1); 
            }
            fputs(fortunes[atoi(numN) - 1], output1);
            fclose(output1);
        }

        else{
            printf("%s", fortunes[atoi(numN) - 1]);
        }
    }

    else if(tracker == 2){

        FILE *batch = fopen(numB, "r"); 
        if (batch == NULL) { 
            printf("ERROR: Can't open batch file\n");
            exit(1); 
        }
        
        int emptyFlag = 0;
        int i;
        while(fgets(temp2, sizeof(char) * buffer, batch)){
            
            while(atoi(temp2) <= 0 || atoi(temp2) > atoi(num_fortune)){
                printf("ERROR: Invalid Fortune Number\n\n");
                fgets(temp2, sizeof(char) * buffer, batch);
            }

            batchNums[i] = malloc(sizeof(char) * atoi(max_length));
            strcat(batchNums[i], temp2);

            printf("%s\n\n", fortunes[atoi(batchNums[i]) - 1]);

            i = i + 1;
            emptyFlag = emptyFlag + 1;
        }

        if(emptyFlag == 0){
            printf("ERROR: Batch File Empty\n");
            exit(1);
        }

        fclose(batch);
    }

    else if(tracker == 2 && oFlag == 1){
        FILE *output1 = fopen(numO, "w"); 
        if (output1 == NULL) { 
            printf("ERROR: Can't open output file\n");
            exit(1); 
        }

        for(int i = 0; i < atoi(num_fortune); i++){
            fputs(fortunes[atoi(batchNums[i]) - 1], output1);
            fputs("\n\n", output1);
        }
        
    }
    

    fclose(fp);
    free(num_fortune);
    free(max_length);
    free(temp);
    free(temp2);
    for(int i = 0; i < atoi(num_fortune); i++){
        free(fortunes[i]);
        free(batchNums[i]);
    }
    return 0;
    
}
