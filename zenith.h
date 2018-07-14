#ifndef CODE_ZENITH_H
#define CODE_ZENITH_H


    //Libraries are declared here
        #include <stdio.h>
        #include <stdlib.h>
        #include <math.h>
        #include <time.h>
        //#include <unistd.h>
        //#include <fcntl.h>
        //#include <sys/ioctl.h>
        //#include <linux/i2c-dev.h>
        #include <string.h>
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
            void reverse(char *str, int len);
            int intToStr(int x, char str[], int d);
            void ftoa(float n, char *res, int afterpoint);
            int correctValue(int *values);
        //Package manipulation functions
            int blockBuilder(char *block, int operating_mode, int aux);
            int packageCreator(char *pack_num_file, char *pack_cycle_file, char *block, char *message);
            int missedPackagesChecker(int expected_package, int received_package, int expected_cycle, int received_cycle);
            int packageAnalyzer();
        //Initialize and check functions
            int createBackup();
            int initializingCubeSat(int check);
        //Communication functions
            //int write_i2c(char *file_name, int packet, int qt, int addr,int chan);
            //int read_i2c(char *file_name, int position, int addr,int chan);
            int sendSimpleMessage(char *block, int op_moode, int aux);
        //Base interface functions
            int headerInterface();
            int interfaceOperator();
            int displayData(char *package);
            int changeOperatingMode();
            int checkZenSatState();
            int readPackages(int mode);
            int changeToMasterMode();
            int shutdownZenSat();
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
