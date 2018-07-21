/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ZenSat v1.0 - CubeSat                                                           *
 * Authors: João Matheus Siqueira Souza      (jmssouza)                            *
 *          Orlando Wozniak de Lima Nogueira (orlandowzk97)                        *
 *          Vinicius Eiji Sasaki             (sasakivinicius)                      *
 * São Carlos School of Engineering - University of São Paulo                      *
 * First semester - 2018                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "zenith.h"

//Files manipulation functions

int valueGetter(char *file_name, int *value){

    FILE *file;

    file = fopen(file_name, "r");
    if (file!=NULL){
        fscanf(file, "%d", value);
        fclose(file);
        return 1;
    }
    else{
        printf("ERROR - file %s cannot be opened", file_name);
        return 0;
    }
}

int valueSetter(char *file_name, int value){
    FILE *file;

    file = fopen(file_name, "w");
    if (file!=NULL){
        fprintf(file,"%d", value);
        fclose(file);
        return 1;
    }
    else{
        system("cls");
        printf("ERROR - file %s cannot be created", file_name);
        return 0;
    }
}

int writeMessage(char *file_name, char *message, int position, int size, int check){

    FILE *file;
    int i;

    file = fopen(file_name, "r+b");

    if (file != NULL){
        fseek(file, position*(size+check), SEEK_SET);
        fwrite(message, size, 1, file);
        fclose(file);
        return 1;
    }
    else{
        printf("Error - file %s cannot be opened.", file_name);
        return 0;
    }
}

int readMessage(char *file_name, char *message, int position, int size, int check){

    FILE *file;
    int i;

    for(i=0;i<size;i++){
        message[i]=0;
    }

    file = fopen(file_name, "r+b");

    if (file != NULL){
        fseek(file, position*(size+check), SEEK_SET);
        fread(message, size, 1, file);
        fclose(file);
        return 1;
    }
    else{
        printf("Error - file cannot be opened.");
        return 0;
    }
}




//General purpose functions

void delay(unsigned int micros){
    clock_t goal = micros + clock();
    while(goal>clock());
}

void reverse(char *str, int len){
    // reverses a string 'str' of length 'len'
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int intToStr(int x, char str[], int d){
    // Converts a given integer x to string str[].  d is the number
    // of digits required in output. If d is more than the number
    // of digits in x, then 0s are added at the beginning.
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint){
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

int correctValue(int *values){
    if ((values[0]==values[1]) && (values[1]==values[2])){
        return values[0];
    }
    else if ((values[0]==values[1]) && (values[1]!=values[2])){
        return values[0];
    }
    else if ((values[0]!=values[1]) && (values[1]==values[2])){
        return  values[2];
    }
    else {
        return -1;
    }
}

void tenBlock(char *str){

    int size;
    int i = 0;

    size = strlen(str);

    if(size>=9){
        str[9] = ';';
        str[10] = '\0';
    }
    else if(size<9){
        for(i = 0; i< size; i++){ str[8-i] = str[size - (i+1)]; }
        for(i = 0; i< 9 - size; i++){ str[i] = '0'; }
        str[9]=';';
        str[10] = '\0';
    }
}

int headerInterface(){
    system("clear");
    printf("=========================================================================\n");
    printf("=                          CubeSat v1 - ZenSat                          =\n");
    printf("=========================================================================\n");
    return 0;
}

void getDate(char *time){
    time[0] = '\0';
    strcat(time,__DATE__);
    strcat(time, " ");
    strcat(time,__TIME__);
}




//Package manipulation functions

int blockBuilder(char *block, int operating_mode, int whoami, int aux){

    int i = 0;
    char cubesat[11]    = "ZenSatEESC";
    char base[11]       = "BaseZenSat";
    char zenith_eesc[3] = "ZE";
    char time[TIME_SIZE];

    for (i=0;i<BLOCK_SIZE;i++){ block[i] = 0; }

    switch (operating_mode){
        case 1 : { // Mission 1 - Simple telemetry service
            if (whoami == 0) {

                char zeros[214];
                char zero_aux[2] = "0";

                getDate(time);

                for (i=0;i<213;i++){zeros[i]= '0';}
                zeros[213] = '\0';

                strcat(block, base);
                strcat(block, zeros);
                strcat(block, time);
                strcat(block,zenith_eesc);
                block[BLOCK_SIZE-1] = '\0';

                block[11] = aux;
            }
            else if (whoami == 1){ //ZenSat block builder

                int ps_block_number = 0;
                int adc_block_number = 0;
                char ps_data[81];
                char adc_data[56];

                valueGetter(PS_NUMBER, &ps_block_number);
                readMessage(PS_FILE, ps_data, ps_block_number, PS_SIZE, 0);
                valueGetter(ADC_RX_NUMBER, &adc_block_number);
                readMessage(ADC_RX_FILE, adc_data, adc_block_number, ADC_SIZE, 0);
                getDate(time);

                strcat(block, cubesat);
                strcat(block, ps_data);
                strcat(block, adc_data);
                strcat(block, time);
                strcat(block, zenith_eesc);
                block[BLOCK_SIZE-1] = '\0';
            }
            else { printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 2 : { //Mission 2 - Power supply checking
            if (whoami == 0) {

                char zeros[216];
                char zero_aux[3] = "00";

                getDate(time);

                for (i=0;i<215;i++){zeros[i]= '0';}
                zeros[215] = '\0';

                strcat(block, base);
                strcat(block, zeros);
                strcat(block, time);
                strcat(block,zenith_eesc);
                block[BLOCK_SIZE] = '\0';

                block[11] = aux;
                block[12] = 10;
            }
            else if (whoami == 1){ //ZenSat block builder
                char ps_data[161];
                char zeros[56];
                int i = 0;

                for (i=0;i<55;i++){zeros[i]= '0';}
                zeros[55] = '\0';

                readMessage(PS_FILE, ps_data, aux, PS_SIZE, 0);
                getDate(time);

                strcat(block, cubesat);
                strcat(block, ps_data);
                strcat(block, zeros);
                strcat(block, time);
                strcat(block,zenith_eesc);
                block[BLOCK_SIZE-1] = '\0';
            }
            else { printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 3 : { //Mission 3 - ADC stabilization
            if (whoami == 0){}
            else if (whoami == 1){}
            else{ printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 4 : { //Mission 4 - Horizon determination
            if (whoami == 0){}
            else if (whoami == 1){}
            else{ printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 5 : {
            if (whoami == 0){}
            else if (whoami == 1){}
            else{ printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break; //Mission 5 - Pointing
        }
        case 6 : { //Mission 6 - Send picture
            //Mandar o tamanho da foto que é desejado
            readMessage(PICTURE_NAME, block, aux, BLOCK_SIZE, 0);
            break;
        }
        case 7 : {
            if (whoami == 0){}
            else if (whoami == 1){}
            else{ printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 8 : { //Minimum telemetry service
            if(whoami == 0){
                for(i=0;i<BLOCK_SIZE-1;i++){
                    block[i] = '0';
                    block[BLOCK_SIZE-1] = '\0';
                }
            }
            else if(whoami == 1){

                char message[22] = "Telecommand received!";
                char zeros[194];

                getDate(time);
                for (i=0;i<194;i++){zeros[i]= '0';}
                zeros[194] = '\0';

                strcat(block, cubesat);
                strcat(block, message);
                strcat(block, zeros);
                strcat(block, time);
                strcat(block, zenith_eesc);
                block[BLOCK_SIZE-1] = '\0';
            }
            else{ printf("Error - in 'blockBuilder', whoami passed is incorrect. \n"); }
            break;
        }
        case 9 : { //Mission failed once or twice
            break;
        }
        case 10 : { //Mission failed three times
            break;
        }
        default: { return 0; }
    }
    return 1;
}

int packageCreator(char *pack_num_file, char *pack_cycle_file, char *block, char *package){

    int i;
    int aux;
    int position;
    int pack_number;
    int pack_cycle;
    int op_mode;

    for (i=0;i<PACK_SIZE+1;i++){
        package[i] = 0;
    }

    //Getting data and setting the system
    valueGetter(pack_num_file  , &pack_number);        //Getting the number of the last package created
    valueGetter(pack_cycle_file, &pack_cycle );        //Getting the number of the current cycle in CubeSat
    valueGetter(MODE_FILE      , &op_mode    );        //Getting the number of operating mode

    pack_number++;
    if (pack_number>PACK_SIZE){
        pack_number=0;
        pack_cycle++;
    }

    valueSetter(pack_num_file  , pack_number);
    valueSetter(pack_cycle_file, pack_cycle );

    //Building the package

    package[0]=pack_number;
    package[1]=pack_cycle;
    package[2]=op_mode;

    package[123]=pack_number;
    package[124]=op_mode;

    package[252]=pack_number;
    package[253]=op_mode;

    for(i=3;i<252;i++){
        if (i<123){
            package[i]=*(block+(i-3));
        }
        else if (i>124){
            package[i] = *(block+(i-5));
        }
    }

    position = pack_cycle*PACK_SIZE + pack_number;
    writeMessage(TM_FILE, package, position, PACK_SIZE, 0);

    return 0;
} //finished

int missedPackagesChecker(int expected_package, int received_package, int expected_cycle, int received_cycle){

    int missed_packages = 0;

    if ((expected_package == received_package)&&(expected_cycle == received_cycle)){
        valueSetter(TC_NUMBER, expected_package);
        valueSetter(TC_CYCLE , expected_cycle  );
        return 0;
    }
    else {
        //Criar função que trate os pacotes perdidos
        if((received_cycle-expected_cycle<2) &&(received_cycle>=expected_cycle)){
            missed_packages = expected_cycle * expected_package - received_cycle * received_package;
            valueSetter(TC_NUMBER, received_package);
            valueSetter(TC_CYCLE , received_cycle  );
            return missed_packages;
        }
        else{
            return -1;
        }
    }
}

int packageAnalyzer(){

    char message[255];
    char missed_array[255];
    int aux;
    int temp;
    int i = 0;
    int pack_num_system       = 0;
    int pack_cycle_system     = 0;
    int operating_mode_system = 0;
    int missed_packages       = 0;
    int pack_num_received[3]  = {0,0,0};
    int pack_cycle_received   = 0;
    int operating_mode_rec[3] = {0,0,0};

    valueGetter(TC_NUMBER, &pack_num_system  );
    valueGetter(TC_CYCLE , &pack_cycle_system);
    readMessage(NEW_TC, message, 0, PACK_SIZE, 1);

    pack_num_received[0]  = message[0];
    pack_num_received[1]  = message[123];
    pack_num_received[2]  = message[252];

    pack_cycle_received   = message[1];

    operating_mode_rec[0] = message[2];
    operating_mode_rec[1] = message[124];
    operating_mode_rec[2] = message[253];

    aux = correctValue(operating_mode_rec);
    if (aux >= 0 && aux <= 9){
        operating_mode_system = aux;
        valueSetter(MODE_FILE, operating_mode_system);
        aux = correctValue(pack_num_received);
        if (aux >= 0){
            if (pack_num_system>aux){ temp = pack_cycle_system + 1; }
            else {temp = pack_cycle_system; }

            missed_packages = missedPackagesChecker(pack_num_system+1, aux, temp,  pack_cycle_received);
            pack_num_system = aux;

            if(missed_packages>=0){
                pack_cycle_system = temp;
                writeMessage(TC_FILE, message, pack_num_system + pack_cycle_system*PACK_SIZE, PACK_SIZE, 1);

                if (missed_packages != 0) {
                    valueSetter(MISSED_PACKAGES, missed_packages);
                    for (i = 0; i < missed_packages; i++) {
                        missed_array[i] = pack_num_system - missed_packages + i;
                    }
                    writeMessage(MISSED_PACKAGES, missed_array, 0, PACK_SIZE, 1);
                }
                else {
                    for (i = 0; i < missed_packages; i++) {
                        missed_array[i] = 0;
                    }
                    writeMessage(MISSED_PACKAGES, missed_array, 0, PACK_SIZE, 1);
                }
            }
            else{
                printf("Corrupted package\n");
                return 0;
            }
        }
        else{
            printf("Corrupted package\n");
            return 0;
        }
        return 1;
    }
    else{
        printf("Corrupted package\n");
        return 0;
    }
}




//Initialize and check functions

int createBackup(){

    system("cp " CHECK_POWERED   " "  CHECK_POWERED_CP   );
    system("cp " NEW_TM          " "  NEW_TM_CP          );
    system("cp " TM_FILE         " "  TM_FILE_CP         );
    system("cp " TM_NUMBER       " "  TM_NUMBER_CP       );
    system("cp " TM_CYCLE        " "  TM_CYCLE_CP        );
    system("cp " NEW_TC          " "  NEW_TC_CP          );
    system("cp " TC_FILE         " "  TC_FILE_CP         );
    system("cp " TC_NUMBER       " "  TC_NUMBER_CP       );
    system("cp " TC_CYCLE        " "  TC_CYCLE_CP        );
    system("cp " MISSED_PACKAGES " "  MISSED_PACKAGES_CP );
    system("cp " MODE_FILE       " "  MODE_FILE_CP       );
    system("cp " PS_FILE         " "  PS_FILE_CP         );
    system("cp " PS_NUMBER       " "  PS_NUMBER_CP       );
    system("cp " ADC_TX_FILE     " "  ADC_TX_FILE_CP     );
    system("cp " ADC_RX_NUMBER   " "  ADC_TX_NUMBER_CP   );
    system("cp " ADC_RX_FILE     " "  ADC_RX_FILE_CP     );
    system("cp " ADC_RX_NUMBER   " "  ADC_RX_NUMBER_CP   );
    system("cp " FILE_SLAVE      " "  FILE_SLAVE_CP      );
    system("cp " FILE_MASTER     " "  FILE_MASTER_CP     );
    system("cp " STD_LOOP        " "  STD_LOOP_CP        );
    system("cp " PS_AUX          " "  PS_AUX_CP          );

    return 0;
}

int recoveryFiles(){

    system("cp " CHECK_POWERED_CP   " "  CHECK_POWERED   );
    system("cp " NEW_TM_CP          " "  NEW_TM          );
    system("cp " TM_FILE_CP         " "  TM_FILE         );
    system("cp " TM_NUMBER_CP       " "  TM_NUMBER       );
    system("cp " TM_CYCLE_CP        " "  TM_CYCLE        );
    system("cp " NEW_TC_CP          " "  NEW_TC          );
    system("cp " TC_FILE_CP         " "  TC_FILE         );
    system("cp " TC_NUMBER_CP       " "  TC_NUMBER       );
    system("cp " TC_CYCLE_CP        " "  TC_CYCLE        );
    system("cp " MISSED_PACKAGES_CP " "  MISSED_PACKAGES );
    system("cp " MODE_FILE_CP       " "  MODE_FILE       );
    system("cp " PS_FILE_CP         " "  PS_FILE         );
    system("cp " PS_NUMBER_CP       " "  PS_NUMBER       );
    system("cp " ADC_TX_FILE_CP     " "  ADC_TX_FILE     );
    system("cp " ADC_RX_NUMBER_CP   " "  ADC_TX_NUMBER   );
    system("cp " ADC_RX_FILE_CP     " "  ADC_RX_FILE     );
    system("cp " ADC_RX_NUMBER_CP   " "  ADC_RX_NUMBER   );
    system("cp " FILE_SLAVE_CP      " "  FILE_SLAVE      );
    system("cp " FILE_MASTER_CP     " "  FILE_MASTER     );
    system("cp " STD_LOOP_CP        " "  STD_LOOP        );
    system("cp " PS_AUX_CP          " "  PS_AUX          );

    return 0;
}

int initializingCubeSat(int check){
    system("clear");
    printf("Initializing Zenith CubeSat...\n");
    if(check == 0){
        printf("CubeSat is initilizing for the first time... \n");

        valueSetter(CHECK_POWERED  ,  1);
        valueSetter(MODE_FILE      ,  0);
        valueSetter(TM_NUMBER      ,  0);
        valueSetter(TM_CYCLE       ,  0);
        valueSetter(TC_NUMBER      ,  0);
        valueSetter(TC_CYCLE       ,  0);
        valueSetter(MISSED_PACKAGES,  0);
        valueSetter(PS_NUMBER      ,  0);
        valueSetter(ADC_TX_NUMBER  ,  0);
        valueSetter(ADC_RX_NUMBER  ,  0);
        valueSetter(STD_LOOP,      , 20);
        createBackup();

    }
    else if (check == 1){
        printf("CubeSat is not initializing for the first time...\n");
        printf("Activating recovery mode...\n");
        delay(1000000);
        recoveryFiles();
        printf("Recovering system...\n");
        delay(3000000);
        createBackup();
        printf("System recovered.\n");
    }
    else{
        printf("ERROR - System cracked.\n");
        delay(2000000);
        return 0;
    }
    //Implementar inicialização da outra rasp

    return 1;
}




//Communication functions

/*

int write_i2c(char *file_name, int packet, int qt, int addr, int chan){

    FILE *file;
    int i;
    char message[256];
    int file_i2c = 0;
    int length;
    int a = 0;
    int v = 0;
    int y = 0;
    char buffer[256] = {0};
    char send[256] = {0};
    char env[256] = {0};
    if (chan == 1){
        char *filename = (char*)"/dev/i2c-1";
    }
    else{
        if (chan == 2) {
            char *filename = (char *) "/dev/i2c-2";
        }
        else
            return 0;
    }
    file = fopen(file_name, "r+b");
    if (file != NULL){
        fseek(file, packet*(PACK_SIZE), SEEK_SET);
        fread(message, PACK_SIZE, qt, file);
        fclose(file);
    }
    else{

        return 0;
    }
    if ((file_i2c = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the i2c bus");
        return 0;
    }

    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        return 0;
    }
    for (y = 0; y<qt;y++)
    {
        length = 32;
        for (a = 0; a<7; a++){
            for (v = 0;v<32;v++)
            {
                env[v] = message[a*32 + y*255 + v];
            }
            write(file_i2c, env, length);
        }
        length = 31;
        for (v = 0;v<31;v++)
        {
            env[v] = message[7*32 + y*255 + v];
        }
        write(file_i2c, env, length);

    }

    return 1;
}

int read_i2c(char *file_name, int position, int addr, int chan){

    FILE *file;
    int i = 0;
    int file_i2c = 0;
    int length;
    int a = 0;
    int aux = 1;
    int b = 0;
    int v = 0;
    char message[256];
    char buffer[256] = {0};
    char send[256] = {0};
    char rec[256] = "";
    char env[256] = {0};

    if (chan == 1){
        char *filename = (char*)"/dev/i2c-1";
    }
    else
    {if (chan == 2)
            char *filename = (char*)"/dev/i2c-2";
        else
            return 0;
    }

    if ((file_i2c = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the i2c bus");
        return 0;
    }

    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        return 0;
    }

    length = 32;

    for (a = 0; a<7; a++){
        read(file_i2c, env, length);
        strcat(rec,env);
    }

    length = 31;
    read(file_i2c, env, length);
    strcat(rec,env);
    aux = rec[3];
    auxi = aux - 1;
    if (rec[2] == 0)
        return 0;
    while (auxi > 0){
        length = 32;
        for (a = 0; a<7; a++){
            read(file_i2c, env, length);
            strcat(rec,env);
        }
        length = 31;
        read(file_i2c, env, length);
        strcat(rec,env);
        auxi--;
    }

    file = fopen(file_name, "r+b");

    if (file != NULL){
        fseek(file, position*(PACK_SIZE), SEEK_SET);
        fwrite(rec, PACK_SIZE, aux, file);
        fclose(file);
    }
    else{
        return 0;
    }

    return 1;
}

*/

int sendSimpleMessage(char *block, int op_mode, int whoami, int aux){

    int check;
    char pack[PACK_SIZE];

    blockBuilder(block, op_mode, whoami, aux);
    packageCreator(TM_NUMBER, TM_CYCLE, block, pack);
    writeMessage(NEW_TM, pack, 0, PACK_SIZE, 0);
    if(whoami == 0){check = write_i2c(NEW_TM, 0, 1, ADD_I2C_ATMEGA_BASE, 1);}
    else if (whoami == 1){check = write_i2c(NEW_TM, 0, 1, ADD_I2C_ATMEGA, 1);}
    else { return 0; }
    return check;
}

int powerSupplyMaster(){

    char ps_block[161];
    char aux1 [11];
    int i;

    values[0] = '/0';

    //LEITURA INAS RASP MASTER E ESCRITA ARQUIVO PS_FILE
    system("python ina.py");
    //AQUI É LIDO A PRIMEIRA PARTE DO QUE SERA ENVIADO SOBRE O PS

    //ENVIA CARACTERE VIA UART PARA RASP SLAVE PARA LEITURA INAS RASP SLAVE
    tx_uart('a');

    //LEITURA VIA UART DADOS INA RASP SLAVE
    rx_uart(aux1); //MUDAR TAMANHO DO VETOR
    //AQUI É LIDO A SEGUNDA PARTE DO QUE SERA ENVIADO SOBRE O PS

    //ESCREVER NO ARQUIVO OS VALORES RESTANTES, REFERENTES A SEGUNDA PARTE DA INFO

    readMessage(PS_AUX, ps_block, 0, PS_SIZE, 0);

    valueGetter(PS_NUMBER, &i);
    writeMessage(PS_FILE, ps_block, i+1, PS_SIZE, 0);
    valueSetter(PS_NUMBER, i+1);

    return 0;
}

int powerSupplySlave(){

    return 0;
}

int ADC(){
    return 0;
}




//CubeSatMaster missions functions

int standardState(){

    int loop_control = 0;
    int check_received;
    int check_package;
    int counter = 0;
    int std_loop;
    char block[BLOCK_SIZE];

    system("clear");
    printf("Operating mode 0 - Standard mode\n");
    valueGetter(STD_LOOP, &std_loop);
    while (loop_control == 0) {
        delay(1000000);
        printf("Checking microcontroller for new commands - Attempt: %d; \n", counter + 1);
        check_received = read_i2c(NEW_TC, 0, ADD_I2C_ATMEGA, 1);

        if (check_received == 1) {
            printf("Message received!\n");
            printf("Analyzing message and setting the system...\n");
            check_package = packageAnalyzer();
            if (check_package == 1){
                printf("System seted. \nInitializing new actions.\n");
                loop_control = 1;
            }
            else{
                printf("Package corrupted. Waiting for new packages...\n");
                counter = 0;
                delay(1000000);
                system("clear");
                printf("Operating mode 0 - Standard mode\n");
            }
        }
        else if (check_received == 0) {
            counter++;
            if (counter == std_loop) {
                counter = 0;
                //REQUISITAR ATUALIZAÇÂO DOS ARQUIVOS DE SISTEMA (ADC E PS)
                sendSimpleMessage(block, 0, 1, 0);
                system("clear");
                printf("Operating mode 0 - Standard mode\n");
            }
        }
    }
    return 0;
}

int healthInfo(){

    int  block_position;
    char block[BLOCK_SIZE];
    char package[PACK_SIZE];
    int check;
    int cycles;

    readMessage(NEW_TC, package, 0, PACK_SIZE, 0);
    cycles = package[13];
    valueSetter(STD_LOOP, cycles);

    system("clear");
    printf("Operating mode 1 - Sending a simple message about Cubesat Health\n");
    printf("Requiring Power Supply System informations ...\n");
    //REQUERER INFORMAÇÕES DO PS, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)
    printf("Requiring ADC System informations...\n");
    //REQUERER INFORMAÇÕES DO ADC, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)

    printf("Building and sending the package...\n");
    check = sendSimpleMessage(block, 1, 1, 0);

    if (check==1){
        printf("Package sended.\n Mission 1 - completed.");
        return 1;
    }
    else {
        printf("The package cannot be sended.\n Mission 1 - failed.");
        return 0;
    }
}

int powerSupplyCheck(){

    int block_position;
    char block[BLOCK_SIZE];
    int check;

    system("clear");
    printf("Operating mode 2 - Checking current and voltage\n");
    printf("Requiring Power Supply System informations ...\n");
    //REQUERER INFORMAÇÕES DO PS, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)
    powerSupplySimulator();


    printf("Building and sending the package...\n");
    valueGetter(PS_NUMBER, &block_position);
    check = sendSimpleMessage(block, 2, 1, block_position);

    delay(7000);

    if (check == 1){
        printf("Package sended.\n Mission 2 - completed.");
        return 1;
    }
    else {
        printf("The package cannot be sended.\n Mission 2 - failed.");
        return 0;
    }
}

int oneAxisStabilization(){

    int block_position;
    char block[BLOCK_SIZE];
    int check;

    system("clear");
    printf("Operating mode 3 - ZenSat stabilization\n");
    printf("Activating reaction wheel stabilization mode...\n");
    //ATIVAR MODO DE ESTABILIZAÇÃO - MANDAR COMANDO PARA O STM
    //ESPERAR FINALIZAÇÃO (o stm deverá manter-se ativado para que o cubesat continue estabilizado)
    printf("ZenSat stabilized!\n");
    printf("Requiring ADC System informations...\n");
    //REQUERER INFORMAÇÕES DO ADC, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)

    printf("Building and sending the package...\n");
    //valueGetter(ADC_NUM, &block_position);
    check = sendSimpleMessage(block, 3, 1, block_position );
    //ESSE PROVAVELMENTE N SERA O CHECK QUE DIRA SE A MISSÃO FOI CONCLUÍDA OU NÃO
    if (check==1){
        printf("Package sended.\n Mission 3 - completed.");
        return 1;
    }
    else {
        printf("The package cannot be sended.\n Mission 3 - failed.");
        return 0;
    }
}

int horizonDetermination(){
    return 0;
}

int pointing(){
    return 0;
}

int livefeed(){
    return 0;
}

int temperatureMonitor(){

    return 0;
}




//Base interface functions

int interfaceOperator(){

    int mode = 0;

    headerInterface();
    printf(" Options:\n");
    printf("   1. Change operating mode;\n");
    printf("   2. Verifies the current state of ZenSat (sleep mode);\n");
    printf("   3. Read packages received;\n");
    printf("   4. Read packages sended;\n");
    printf("   5. Change to master operating mode;\n");
    printf("   9. Shutdown 'ZenSat' and exit 'CubeSat Monitor'.\n\n\n\n\n\n\n");
    printf(" Your option: ");
    scanf ("%d", &mode);
    printf("=========================================================================\n");

    return mode;
}

int displayData(char *package){ ;

    int pack_number = 0;
    int pack_cycle  = 0;
    int op_mode     = 0;
    int pack_num_received[3]  = {0,0,0};
    int pack_cycle_received   = 0;
    int operating_mode_rec[3] = {0,0,0};
    char aux[11];
    char zensat[11];
    char time[21];


    pack_num_received[0]  =  package[0];
    pack_num_received[1]  =  package[123];
    pack_num_received[2]  =  package[252];
    pack_cycle_received   =  package[1];
    operating_mode_rec[0] =  package[2];
    operating_mode_rec[1] =  package[124];
    operating_mode_rec[2] =  package[253];

    pack_number =  correctValue(pack_cycle_received);
    op_mode     =  correctValue(operating_mode_rec);

    headerInterface();
    printf("Pack number: &d;  Pack cycle: %d;  Operating mode: %d;\n", pack_number, pack_cycle, op_mode);

    switch (op_mode){
        case 1:{
            float ina_values[8][2];
            float euler_angles[3];
            float wheel_rpm;
            float cubesat_omega;
            float temperature;
            int i = 0;

            /* ************************************** Converting data ************************************** */
            //NAME
            for(i =  3;i < 13;i++){ zensat[i - 3] = package[i];} zensat[11] = '\0';
            //INA DATA
            for(i = 13;i < 23;i++){ aux[i - 15] = package[i];} aux[11] = '\0'; ina_values[0][0] = atof(aux);
            for(i = 23;i < 33;i++){ aux[i - 23] = package[i];} aux[11] = '\0'; ina_values[0][1] = atof(aux);
            for(i = 33;i < 43;i++){ aux[i - 33] = package[i];} aux[11] = '\0'; ina_values[1][0] = atof(aux);
            for(i = 43;i < 53;i++){ aux[i - 43] = package[i];} aux[11] = '\0'; ina_values[1][1] = atof(aux);
            for(i = 53;i < 63;i++){ aux[i - 53] = package[i];} aux[11] = '\0'; ina_values[2][0] = atof(aux);
            for(i = 63;i < 73;i++){ aux[i - 63] = package[i];} aux[11] = '\0'; ina_values[2][1] = atof(aux);
            for(i = 73;i < 83;i++){ aux[i - 73] = package[i];} aux[11] = '\0'; ina_values[3][0] = atof(aux);
            for(i = 83;i < 93;i++){ aux[i - 83] = package[i];} aux[11] = '\0'; ina_values[3][1] = atof(aux);
            for(i = 93;i <103;i++){ aux[i - 93] = package[i];} aux[11] = '\0'; ina_values[4][0] = atof(aux);
            for(i =103;i <113;i++){ aux[i -103] = package[i];} aux[11] = '\0'; ina_values[4][1] = atof(aux);
            for(i =113;i <123;i++){ aux[i -113] = package[i];} aux[11] = '\0'; ina_values[5][0] = atof(aux);
            for(i =125;i <135;i++){ aux[i -125] = package[i];} aux[11] = '\0'; ina_values[5][1] = atof(aux);
            for(i =135;i <145;i++){ aux[i -135] = package[i];} aux[11] = '\0'; ina_values[6][0] = atof(aux);
            for(i =145;i <155;i++){ aux[i -145] = package[i];} aux[11] = '\0'; ina_values[6][1] = atof(aux);
            for(i =155;i <165;i++){ aux[i -155] = package[i];} aux[11] = '\0'; ina_values[7][0] = atof(aux);
            for(i =165;i <175;i++){ aux[i -165] = package[i];} aux[11] = '\0'; ina_values[7][1] = atof(aux);
            //ADC DATA
            for(i =175;i <185;i++){ aux[i -175] = package[i];} aux[11] = '\0'; euler_angles[0] = atof(aux);
            for(i =185;i <195;i++){ aux[i -185] = package[i];} aux[11] = '\0'; euler_angles[1] = atof(aux);
            for(i =195;i <205;i++){ aux[i -195] = package[i];} aux[11] = '\0'; euler_angles[2] = atof(aux);
            for(i =205;i <215;i++){ aux[i -205] = package[i];} aux[11] = '\0'; wheel_rpm       = atof(aux);
            for(i =215;i <225;i++){ aux[i -215] = package[i];} aux[11] = '\0'; cubesat_omega   = atof(aux);
            for(i =225;i <230;i++){ aux[i -225] = package[i];} aux[11] = '\0'; temperature     = atof(aux);
            //TIME
            for(i =230;i <250;i++){ time[i -230] = package[i];} time[21] = '\0';


            /* ************************************** Printing on screen ************************************** */
            printf("Battery        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[0][0], ina_values[0][1]);
            printf("Regulator 5v   -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[1][0], ina_values[1][1]);
            printf("Regulator 3v3  -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[2][0], ina_values[2][1]);
            printf("Charger        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[3][0], ina_values[3][1]);
            printf("Panel 1        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[4][0], ina_values[4][1]);
            printf("Panel 2        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[5][0], ina_values[5][1]);
            printf("Panel 3        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[6][0], ina_values[6][1]);
            printf("Panel 4        -   Tension : %8.3f V   -   Current : %8.3f mA   \n", ina_values[7][0], ina_values[7][1]);
            printf("Euler's angles -   Roll : %8.3f;  Pitch : %8.3f;  Yaw : %8.3f;\n", euler_angles[0], euler_angles[1], euler_angles[2]);
            printf("Wheel RPM: %8.3f   -   ZenSat Angular Velocity: %8.3f\n");
            printf("%s   -   time when sended: %s\n", zensat, time );

            break;
        }
        case 2:{

            float ina_values[8][2];
            int current_pack;
            int packs_expected;
            int i = 0;

            /* ************************************** Converting data ************************************** */
            //NAME
            for(i =  3;i < 13;i++){ zensat[i - 3] = package[i];} zensat[11] = '\0';
            //INA DATA
            for(i = 13;i < 23;i++){ aux[i - 15] = package[i];} aux[11] = '\0'; ina_values[0][0] = atof(aux);
            for(i = 23;i < 33;i++){ aux[i - 23] = package[i];} aux[11] = '\0'; ina_values[0][1] = atof(aux);
            for(i = 33;i < 43;i++){ aux[i - 33] = package[i];} aux[11] = '\0'; ina_values[1][0] = atof(aux);
            for(i = 43;i < 53;i++){ aux[i - 43] = package[i];} aux[11] = '\0'; ina_values[1][1] = atof(aux);
            for(i = 53;i < 63;i++){ aux[i - 53] = package[i];} aux[11] = '\0'; ina_values[2][0] = atof(aux);
            for(i = 63;i < 73;i++){ aux[i - 63] = package[i];} aux[11] = '\0'; ina_values[2][1] = atof(aux);
            for(i = 73;i < 83;i++){ aux[i - 73] = package[i];} aux[11] = '\0'; ina_values[3][0] = atof(aux);
            for(i = 83;i < 93;i++){ aux[i - 83] = package[i];} aux[11] = '\0'; ina_values[3][1] = atof(aux);
            for(i = 93;i <103;i++){ aux[i - 93] = package[i];} aux[11] = '\0'; ina_values[4][0] = atof(aux);
            for(i =103;i <113;i++){ aux[i -103] = package[i];} aux[11] = '\0'; ina_values[4][1] = atof(aux);
            for(i =113;i <123;i++){ aux[i -113] = package[i];} aux[11] = '\0'; ina_values[5][0] = atof(aux);
            for(i =125;i <135;i++){ aux[i -125] = package[i];} aux[11] = '\0'; ina_values[5][1] = atof(aux);
            for(i =135;i <145;i++){ aux[i -135] = package[i];} aux[11] = '\0'; ina_values[6][0] = atof(aux);
            for(i =145;i <155;i++){ aux[i -145] = package[i];} aux[11] = '\0'; ina_values[6][1] = atof(aux);
            for(i =155;i <165;i++){ aux[i -155] = package[i];} aux[11] = '\0'; ina_values[7][0] = atof(aux);
            for(i =165;i <175;i++){ aux[i -165] = package[i];} aux[11] = '\0'; ina_values[7][1] = atof(aux);
            //MISSION PACKS INFO
            for(i =175;i <180;i++){ aux[i -175] = package[i];} aux[6] = '\0'; current_pack   = (int)atof(aux);
            for(i =180;i <185;i++){ aux[i -180] = package[i];} aux[6] = '\0'; packs_expected = (int)atof(aux);
            //TIME
            for(i =230;i <250;i++){ time[i -230] = package[i];} time[21] = '\0';


            /* ************************************** Printing on screen ************************************** */
            printf("Battery        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[0][0], ina_values[0][1]);
            printf("Regulator 5v   -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[1][0], ina_values[1][1]);
            printf("Regulator 3v3  -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[2][0], ina_values[2][1]);
            printf("Charger        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[3][0], ina_values[3][1]);
            printf("Panel 1        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[4][0], ina_values[4][1]);
            printf("Panel 2        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[5][0], ina_values[5][1]);
            printf("Panel 3        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[6][0], ina_values[6][1]);
            printf("Panel 4        -   Tension : %8.3f V  -  Current : %8.3f mA   \n", ina_values[7][0], ina_values[7][1]);
            printf("\nNumber of package in mission: %d/%d\n", current_pack, packs_expected);
            printf("\n%s   -   time when sended: %s\n", zensat, time );

            break;
        }
        case 3:{ break;}
        case 4:{ break;}
        case 5:{ break;}
        case 6:{ break;}
        case 7:{ break;}
        case 8:{

            int i = 0;
            char aux1[22];

            for(i=0;i<22;i++){ aux1[i] = package[i+3];}
            printf("%s\n", aux1);
            break;
        }
    }

    return 0;
}

int changeOperatingMode(){

    char package [PACK_SIZE];
    char block [BLOCK_SIZE];
    char package_text[21] = "BaseMessage-ZenSatV1";
    int check;
    int aux = 0;
    int i;
    int op = 0;

    //User information
    headerInterface();
    printf(" Choose:");
    printf("\n     1. Check system health;");
    printf("\n     2. Power Supply verification;");
    printf("\n     3. ZenSat stabilization;");
    printf("\n     4. Horizon determination;");
    printf("\n     5. ZenSat pointing;");
    printf("\n     6. Livefeed;");
    printf("\n     7. Temperature monitor;");
    printf("\n     8. Minimum communication test;");
    printf("\n\n\n\n Your option: ");
    scanf("%d", &op);
    delay(200000);

    switch (op) {
        case 1: { //Mode 1 - Simple telemetry service

            int cycles_number;

            headerInterface();
            printf("Change delay of standard mode? (How many cycles before send a package?) \n");
            scanf ("%d", &cycles_number);
            sendSimpleMessage(block,op,0,cycles_number);

            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            //displayData(package);
            break;
        }
        case 2: { //Mode 2 - Power supply check

            int counter = 0;

            headerInterface();
            printf(" How many measurements are needed? ");
            scanf ("%d", &aux);
            printf("\nBuilding and sending command package...\n");
            sendSimpleMessage(block,op,0,aux);
            printf("Command package sended.\n");
            i = 0;

            while(i<aux){
                //check = read_i2c();
                if (check == 0){
                    counter ++;
                    if(counter == 15){
                        headerInterface();
                        printf("ZenSat don't respond.\nSystem failed.\n");
                        delay(5000000);
                        i = aux;
                    }
                }
                else if(check == 1){
                    counter = 0;
                    i++;
                    displayData(package);
                }
                else {
                    printf("Error - problem in communication with Atmega and LoRa.\n");
                }
                delay(1000000);
            }
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            displayData(package);
            break;
        }
        case 3: { //Mode 3 - Stabilization
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR DE CHECAGEM E FINALIZAÇÃO
            //OU MANDAR PACOTE DE FINALIZAÇÃO?
            displayData(package);
            break;
        }
        case 4: { //Mode 4 - Horizon determination
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            displayData(package);
            break;
        }
        case 5: { //Mode 5 - Pointing
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO E CHECAGEM DE APONTAMENTO
            displayData(package);
            break;
        }
        case 6: { //Mode 6 - Livefeed
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //displayData(package);
            //RECEBER FOTO
            //REMONTA-LA
            //EXIBIR FOTO
            break;
        }
        case 7: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            displayData(package);
            //MANDAR PACOTE DE FINALIZAÇÃO
            break;
        }
        case 8: {

            headerInterface();
            printf("Sending minimum message...\n");
            sendSimpleMessage(block, 8, 0, 0);
            aux = 1;

            while(aux){
                check = read_i2c(NEW_TC, 0, ADD_I2C_ATMEGA_BASE, 1);
                if (check == 0){
                    counter ++;
                    if(counter == 15){
                        headerInterface();
                        printf("ZenSat don't respond.\nSystem failed.\n");
                        delay(5000000);
                        aux = 0;
                    }
                }
                else if(check == 1){
                    counter = 0;
                    aux = 0;
                    displayData(package);
                }
                else {
                    printf("Error - problem in communication with Atmega and LoRa.\n");
                }
                delay(1000000);
            }
        }
        default: {
            printf("Invalid entry!");
            break;
        }
    }

    return 0;
}

int checkZenSatState(){
    int cycles = 0;
    while(cycles < 3){
        delay(2000000);
        scanf("%d",&cycles);
        /*
         received = read_i2c();
         if(received_i2c == 1){ DEU BOM PRINTA}
         else {counter ++}
         if counter >= 3) DEU RUIM, something like that
         */
        //VERIFICAR SE HÁ MENSAGEM NO ATMEGA
        //PRINTAR A MENSAGEM DO ATMEGA
        //SE NÃO HOUVER NOVOS PACOTES, AVISAR QUE DEU MUITO RUIM
    }
    return 0;
}

int readPackages(int mode){
    //Mode 0  refers to packages received and mode 1, to packages sended

    char package[PACK_SIZE];
    int pack_num = 0;

    headerInterface();
    printf("Mode: %d\n", mode);
    printf("Type the number of the package that you want to read: ");
    scanf("%d", &pack_num);
    if (mode == 0)     { readMessage(TC_FILE, package, pack_num, PACK_SIZE, 0);}
    else if (mode == 1){ readMessage(TM_FILE, package, pack_num, PACK_SIZE, 0);}
    else { printf("\nInvalid mode\n"); return 0; }

    displayData(package);

    return 1;
}

int changeToMasterMode(){
    int password = 0;

    printf("\n Password: ");
    scanf("%d", &password);
    if (password == PASSWORD){
        headerInterface();
        printf("You are on Master Operating Mode");
        delay(1000000);
        headerInterface();
        //FUTURE

        return 1;
    }
    else{
        headerInterface();
        printf("Wrong password!");
        return 0;
    }
}

int shutdownZenSat(){

    int password = 0;
    char temp;

    headerInterface();
    printf("Do you really want to shutdown ZenSat? (y,n)");
    fflush(stdin);
    scanf("%c", &temp);
    if(temp == 'y'){
        printf("\nPassword: ");
        scanf("%d", &password);
        if (password == PASSWORD) {
            headerInterface();
            printf("Shutting down ZenSat ... ");
            //ENVIAR COMANDO DE DESLIGAR
            //ESPERAR POR CONFIRMAÇÃO
            printf("\nZenSat power off.\nGood bye!\n");
            delay(1500000);
        }
    }
    else {
        printf("\n Wrong password!");
        delay(2000000);
    }
}




//Main functions

int CubeSatSlave(){
    return 0;
}

int CubeSatMaster(){

    /* *****************  Variable declarations  ***************** */

    int check_powered = 0;
    int main_loop_control = 0;
    int mission_check = 0;
    int mission_counter = 0;
    int operating_mode = 0;
    int previous_operating_mode = 0;
    char block[BLOCK_SIZE];
    char pack[PACK_SIZE];


    /* *****************  System Initilization  ***************** */

    valueGetter(CHECK_POWERED, &check_powered);
    initializingCubeSat(check_powered);
    valueGetter(MODE_FILE, &operating_mode );


    /* *****************  Functional mode  ***************** */

    while (main_loop_control == 0) {
        switch (operating_mode) {
            case 0: {
                standardState();
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
            case 1: { //Health Telemetry mode
                mission_check = healthInfo(operating_mode);
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                    }
                }
                break;
            }
            case 2: { //Power Supply Mode
                mission_check = powerSupplyCheck();
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 3: { //ADC stabilization
                mission_check = oneAxisStabilization();
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 4: { //Horizon determination
                mission_check = horizonDetermination();
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 5: { //ADC pointing
                mission_check = pointing();
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 6: { //Live feed
                mission_check = livefeed(1);
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 7: {
                mission_check = temperatureMonitor();
                if (mission_check == 1){
                    mission_counter = 0;
                    operating_mode = 0;
                    valueSetter(MODE_FILE, operating_mode);
                }
                else{
                    mission_counter ++;
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                        operating_mode = 0;
                        valueSetter(MODE_FILE, operating_mode);
                    }
                }
                break;
            }
            case 8:{
                system("clear");
                printf("Minimum telemetry service\n");
                printf("Building and send the package...\n");
                sendSimpleMessage(block, 8, 1, 0);
                printf("Package sended.\n");
                operating_mode = 0;
                valueSetter(MODE_FILE, operating_mode);
                break;
            }
            case 9: {
                system("clear");
                printf("Operating mode 9 - Shutdown\n");
                return 1;
            }
            default: {
                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
        }
        createBackup();
    }
    return 0;
}

int Base(){

    int control = 0;

    while (control != 9){

        control = interfaceOperator();
        switch (control){
            case 1: { changeOperatingMode(); break; }
            case 2: { checkZenSatState();    break; }
            case 3: { readPackages(0);       break; }
            case 4: { readPackages(1);       break; }
            case 5: { changeToMasterMode();  break; }
            case 9: { shutdownZenSat();      break; }
            default:{
                printf("Invalid entry!");
                return 0;
            }
        }
    }
    return 1;
}




//Test function

int powerSupplySimulator(){

    float ina_values[8][2];
    char aux1 [11];
    char values [PS_SIZE];
    int i;

    values[0] = '/0';

    //GETTING DATA FROM INAS - ORLANDIN IMPLEMENTA ASSIM MEU QUERIDO
    for(i=0;i<8;i++){
        printf("Entry tension from ina %d: ", i +1);
        scanf("%f", &ina_values[i][0]);
        printf("\nEntry current from ina %d: ", i +1);
        scanf("%f", &ina_values[i][1]);
        printf("\n");
    }//APAGAR ESSE "FOR" DEPOIS, USEI PARA TESTAR

    //PUT DATA INTO FILE
    for(i=0;i<8;i++){
        ftoa(ina_values[i][0], aux1, 5);
        tenBlock(aux1);
        strcat(values,aux1);
        ftoa(ina_values[i][1], aux1, 5);
        tenBlock(aux1);
        strcat(values,aux1);
    }
    valueGetter(PS_NUMBER, &i);
    writeMessage(PS_FILE, values,i+1, PS_SIZE, 0);
    valueSetter(PS_NUMBER, i+1);

    return 0;
}

int sendlandeira(char* package){
    FILE *fp = fopen("partidocomunista", "ab");

    fwrite(package, 1, BLOCK_SIZE, fp);

    fclose(fp);

    return 1;
}

int file_size(char* FILE_NAME){
    FILE *fp = fopen(FILE_NAME, "rb");

    if(fp == NULL){
        printf("Error opening file!\n");
        fclose(fp);

        return 0;
    }

    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fclose(fp);

    return length;
}

int livefeed_tx(char *FILE_NAME){

    int picture_size, packages_num, last_size, i;
    char block[BLOCK_SIZE];
    char package[PACK_SIZE];
    picture_size = file_size(FILE_NAME);

    if(picture_size == 0){
        return 0;
    }

    packages_num = picture_size/BLOCK_SIZE;
    last_size = picture_size%BLOCK_SIZE;


    for(i = 0; i < (packages_num - 1); i++){
        //blockBuilder(block, 6, i);
        packageCreator(TM_NUMBER, TM_CYCLE, block, package);
        sendlandeira(block);
    }

    if(i == (packages_num - 1)){
        FILE *fp = fopen(FILE_NAME, "rb");

        if(fp != NULL){
            fseek(fp, BLOCK_SIZE*i, SEEK_SET);
            fread(block, 1, last_size, fp);

            for(int j = last_size; j < BLOCK_SIZE; j++){
                block[j] = 0;
            }

            packageCreator(TM_NUMBER, TM_CYCLE, block, package);
            sendlandeira(block);

            return 1;
        }
    }
}

int CubeSatTest(){
    int i = 0;
    int j = 0;
    int mode = 0;
    int pack = 0;
    char msg[255];

    while (i == 0){
        system("cls");
        for(j=0;j<255;j++) {
            msg[i] = 0;
        }

        printf(" Digite o modo de operacao - ");
        scanf ("%d", &mode);
        printf("\n Digite o num do pack - ");
        scanf ("%d", &pack);


        msg[0]=pack;
        msg[1]=0;
        msg[2]=mode;

        msg[123]=pack;
        msg[124]=mode;

        msg[252]=pack;
        msg[253]=mode;

        writeMessage(NEW_TC, msg, 0, PACK_SIZE, 0);

        printf("\nDigite 1 para sair.\n");
        scanf ("%d", &i);
    }

    return 0;
}




//Install functions

int createFile(char *file_name){

    FILE * file;

    printf("Creating file %s ...\n", file_name);
    delay(800000);

    file = fopen(file_name, "wb");
    if (file != NULL){
        fclose(file);
        printf("File %s created.\n", file_name);
        return 1;
    }
    else{
        printf("ERROR - File %s cannot be created.\n", file_name);
        return 0;
    }
}

int createZenithFiles(){

    int i = 0;
    int counter;
    int aux[21];

    aux[ 0] = createFile(CHECK_POWERED);
    aux[ 1] = createFile(NEW_TM);
    aux[ 2] = createFile(TM_FILE);
    aux[ 3] = createFile(TM_NUMBER);
    aux[ 4] = createFile(TM_CYCLE);
    aux[ 5] = createFile(NEW_TC);
    aux[ 6] = createFile(TC_FILE);
    aux[ 7] = createFile(TC_NUMBER);
    aux[ 8] = createFile(TC_CYCLE);
    aux[ 9] = createFile(MISSED_PACKAGES);
    aux[10] = createFile(MODE_FILE);
    aux[11] = createFile(PS_FILE);
    aux[12] = createFile(PS_NUMBER);
    aux[13] = createFile(ADC_TX_FILE);
    aux[14] = createFile(ADC_TX_NUMBER);
    aux[15] = createFile(ADC_RX_FILE);
    aux[16] = createFile(ADC_RX_NUMBER);
    aux[17] = createFile(FILE_SLAVE);
    aux[18] = createFile(FILE_MASTER);
    aux[19] = createFile(STD_LOOP);
    aux[20] = createFile(PS_AUX);


    for (i=0;i<21;i++){ if (aux[i] == 0){ counter ++; }}

    if   (counter>0) { printf("\n%d files cannot be created", counter); return 1;}
    else { printf("\nFiles successfully created\n");                    return 0;}
}

int compileCodes(int mode){

    if (mode == 1){
        printf("Compiling cube.c file... \n");
        delay(600000);
        system("gcc cube.c -o cube -lm");
        printf("File cube.c was already compiled.\n");
        delay(600000);
    }
    else if (mode == 2){
        printf("Compiling base.c file... \n");
        delay(600000);
        system("gcc base.c -o base -lm");
        printf("File base.c was already compiled. \n");
        delay(600000);
    }
    else if (mode == 3){
        printf("Compiling cube.c file... \n");
        delay(600000);
        system("gcc cube.c -o cube -lm");
        printf("File cube.c was already compiled.\n");
        delay(600000);
        printf("Compiling base.c file... \n");
        delay(600000);
        system("gcc base.c -o base -lm");
        printf("File base.c was already compiled. \n");
        delay(600000);
    }
    else {
        printf("This mode of compilation is not valid\n");
    }
    return 0;
}

int installer(){

    int mode;

    headerInterface();
    printf("Zenith Cube Sat v.1.0 installer ... \n");
    printf("Press: \n1 - to install CubeSat version;\n2 - to install Base version;\n3 - to install both;\n");
    scanf("%d", &mode);
    delay(1500000);
    printf("Creating files... \n");
    createZenithFiles();
    printf("Compiling files... \n");
    compileCodes(mode);
    delay(1000000);
    printf("zenith.h is already installed!\n\n");
    delay(2000000);

    return 0;
}
