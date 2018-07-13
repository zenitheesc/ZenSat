#ifndef CODE_ZENITH_H
#define CODE_ZENITH_H


//Global variables are declared here

int global_pack_tm_number = 0;
int global_pack_tc_number = 0;

//Libraries are declared here

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "constants.h"
#include "zenith.c"

    //Functions body are declared here
        //Files manipulation functions
            int valueGetter(char *file_name, int *value);
            int valueSetter(char *file_name, int value);
            int writeMessage(char *file_name, char *message, int position, int size, int check);
            int readMessage(char *file_name, char *message, int position, int size, int check);
        //General purpose functions
            void delay(unsigned int micros);
            int headerInterface();
            int interfaceOperator(int mode, int pack_num, char *info);
            int correctValue(int *values);
        //Package manipulation functions
            int blockBuilder(char *block, int operating_mode, int aux);
            int packageCreator(char *pack_num_file, char *pack_cycle_file, char *block, char *message);
            int missedPackagesChecker(int expected_package, int received_package);
            int packageAnalyzer();
        //Initialize and check functions
            int createBackup();
            int initializingCubeSat(int check);
        //Install functions
            int createFile(char *file_name);
            int createZenithFiles();
            int compileCodes(int mode);
            int installer();

int sendlandeira(char* package);
int file_size(char* FILE_NAME);
int livefeed_tx(char *FILE_NAME);
        //Main functions
            int CubeSat();
            int Base();
        //Test functions
            int CubeSatTest();


#endif //CODE_ZENITH_H
