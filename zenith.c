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

int headerInterface(){
    system("clear");
    printf("=========================================================================\n");
    printf("=                          CubeSat v1 - ZenSat                          =\n");
    printf("=========================================================================\n");
    return 0;
}


//Package manipulation functions

int blockBuilder(char *block, int operating_mode, int whoami, int aux){

    int i = 0;

    for (i=0;i<BLOCK_SIZE;i++){ block[i] = 0; }

    switch (operating_mode){

        case 0 : {
            if (whoami == 1){
                block = (char*)"I'mStillAlive";
            }
            else { printf("whoami incorrect. \n"); }
            break;
        }
        case 1 : { // Mission 1
            if (whoami == 0){//Base code
                block[0] = 'Z';
                block[1] = 'e';
                block[2] = 'n';
                block[3] = 'S';
                block[4] = 'a';
                block[5] = 't';
                block[6] = '\0';
            }
            else if (whoami == 1){//ZenSat code

            }
            else{ printf("whoami incorrect. \n"); }
            break;
        }
        case 2 : {
            break;
        }
        case 3 : { break; }
        case 4 : { break; }
        case 5 : { break; }
        case 6 : {
            readMessage(PICTURE_NAME, block, aux, BLOCK_SIZE, 0);
            break;
        }
        case 7 : { break; }
        case 8 : { break; }
        case 9 : { //Mission failed once or twice
            break;
        }
        case 10 : { //Mission failed three times
            break;
        }
        default:{ return 0; }
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
    if (aux >= 0 && aux <= 8){
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
    system("cp " HEALTH_FILE     " "  HEALTH_FILE_CP     );
    system("cp " HEALTH_NUMBER   " "  HEALTH_NUMBER_CP   );
    system("cp " PS_FILE         " "  PS_FILE_CP         );
    system("cp " PS_NUMBER       " "  PS_NUMBER_CP       );
    system("cp " ADC_FILE        " "  ADC_FILE_CP        );
    system("cp " ADC_NUMBER      " "  ADC_NUMBER_CP      );
    system("cp " CV_FILE         " "  CV_FILE_CP         );
    system("cp " CV_NUMBER       " "  CV_NUMBER_CP       );

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
    system("cp " HEALTH_FILE_CP     " "  HEALTH_FILE     );
    system("cp " HEALTH_NUMBER_CP   " "  HEALTH_NUMBER   );
    system("cp " PS_FILE_CP         " "  PS_FILE         );
    system("cp " PS_NUMBER_CP       " "  PS_NUMBER       );
    system("cp " ADC_FILE_CP        " "  ADC_FILE        );
    system("cp " ADC_NUMBER_CP      " "  ADC_NUMBER      );
    system("cp " CV_FILE_CP         " "  CV_FILE         );
    system("cp " CV_NUMBER_CP       " "  CV_NUMBER       );

    return 0;
}

int initializingCubeSat(int check){
    system("clear");
    printf("Initializing Zenith CubeSat...\n");
    if(check == 0){
        printf("CubeSat is initilizing for the first time... \n");

        valueSetter(CHECK_POWERED  , 1);
        valueSetter(TM_NUMBER      , 0);
        valueSetter(TM_CYCLE       , 0);
        valueSetter(TC_NUMBER      , 0);
        valueSetter(TC_CYCLE       , 0);
        valueSetter(MISSED_PACKAGES, 0);
        valueSetter(HEALTH_NUMBER  , 0);
        valueSetter(PS_NUMBER      , 0);
        valueSetter(ADC_NUMBER     , 0);
        valueSetter(CV_NUMBER      , 0);
    }
    else if (check == 1){
        printf("CubeSat is not initializing for the first time...\n");
        printf("Activating recovery mode...\n");
        delay(1000000);
        recoveryFiles();
        printf("Recovering system...\n");
        delay(3000000);
        printf("System recovered.\n");
    }
    else{
        printf("ERROR - System cracked.\n");
        delay(2000000);
        return 0;
    }
    return 1;
}


//Communication functions

/*

int write_i2c(char *file_name, int packet, int qt, int addr,int chan){

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

int read_i2c(char *file_name, int position, int addr,int chan){

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
    //check = write_i2c(NEW_TM, 0, 1, adr, chanel);
    if (check == 1){
        return 1;
    }
    else{
        return 0;
    }
}


//CubeSat missions functions

int standardState(){

    int loop_control;
    int check_received;
    int check_package;
    int counter = 0;
    char block[BLOCK_SIZE];

    system("clear");
    printf("Operating mode 0 - Standard mode\n");
    while (loop_control == 0) {
        delay(2000000);
        printf("Checking microcontroller for new commands - Attempt: %d; \n", counter + 1);
        //temp = read_i2c(NEW_TC); //PASSAR ARGS
        if (check_received == 1) {
            printf("Message received!\n");
            printf("Analyzing message and setting the system...\n");
            check_package = packageAnalyzer();
            if (check_package == 1){
                printf("System seted. \nInitializing new actions.\n");
                delay(800000);
                loop_control = 1;
            }
            else{
                printf("Waiting for new packages...\n");
                counter = 0;
                delay(1000000);
                system("clear");
                printf("Operating mode 0 - Standard mode\n");
            }
        }
        else if (check_received == 0) {
            counter++;
            if (counter == 15) {
                counter = 0;
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
    int check = 0;

    system("clear");
    printf("Operating mode 2 - Checking current and voltage\n");
    printf("Requiring Power Supply System informations ...\n");
    //REQUERER INFORMAÇÕES DO PS, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)


    printf("Building and sending the package...\n");
    valueGetter(PS_NUM, &block_position);
    check = sendSimpleMessage(block, 2, 1, block_position);

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

    system("clear");
    printf("Operating mode 3 - ZenSat stabilization\n");
    printf("Activating reaction wheel stabilization mode...\n");
    //ATIVAR MODO DE ESTABILIZAÇÃO
    //ESPERAR FINALIZAÇÃO (o stm deverá manter-se ativado para que o cubesat continue estabilizado)
    printf("ZenSat stabilized!\n");
    printf("Requiring ADC System informations...\n");
    //REQUERER INFORMAÇÕES DO ADC, ESTAS DEVEM SER SALVAS EM SEUS RESPECTIVOS ARQUIVOS
    //MOSTRAR EM TELA ESSAS INFORMAÇÕES (para checagem de sistema, depois deve ser comentado)

    printf("Building and sending the package...\n");
    valueGetter(ADC_NUM, &block_position);
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

int livefeed(int mode){
    return 0;
}


//Base interface functions

int interfaceOperator(){

    int mode = 0;

    headerInterface();
    printf(" Options:\n");
    printf("   1. Change operating mode;\n");
    printf("   2. Verifies the current state of ZenSat;\n");
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
    printf(" Pack number: &d;  Pack cycle: %d;");

    switch (op_mode){
        case 1:{ break;}
        case 2:{ break;}
        case 3:{ break;}
        case 4:{ break;}
        case 5:{ break;}
        case 6:{ break;}
        case 7:{ break;}
    }

    return 0;
}

int changeOperatingMode(){

    char package [PACK_SIZE];
    char block [BLOCK_SIZE];
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
    printf("\n\n\n\n Your option: ");
    scanf("%d", &op);

    switch (op) {
        case 1: {

            sendSimpleMessage(block,op,0,0);
            readMessage(NEW_TM, package, 0, PACK_SIZE, 0);
            printf("\n\n\n%s", package);
            //displayData(package);
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            //displayData(package);
            break;
        }
        case 2: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            displayData(package);
            break;
        }
        case 3: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR DE CHECAGEM E FINALIZAÇÃO
            //OU MANDAR PACOTE DE FINALIZAÇÃO?
            displayData(package);
            break;
        }
        case 4: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO
            displayData(package);
            break;
        }
        case 5: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            //PRINTAR INFO E CHECAGEM DE APONTAMENTO
            displayData(package);
            break;
        }
        case 6: {
            //CRIAR PACOTE DE MUDANÇA DE MODE COM INFO NECESSÁRIA
            //ESPERAR POR PACOTE DE INFO
            displayData(package);
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
    printf("Put the number of the package that you want to read: ");
    scanf("%d", &pack_num);
    if (mode == 0)     { readMessage(TC_FILE, package, pack_num, PACK_SIZE, 0);}
    else if (mode == 1){ readMessage(TM_FILE, package, pack_num, PACK_SIZE, 0);}
    else { printf("\nInvalid mode"); return 0; }

    //displayData(package);

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

int CubeSat(){

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
                    sendSimpleMessage(block, 9, 1, operating_mode);
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
                    sendSimpleMessage(block, 9, 1, operating_mode);
                    if (mission_counter == 3){
                        mission_counter = 0;
                        sendSimpleMessage(block, 10, 1, operating_mode);
                    }
                }break;
            }
            case 3: { //ADC stabilization
                break;
            }
            case 4: { //Horizon determination
                system("clear");
                printf("Operating mode 4 - Horizon determination");

                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
            case 5: { //ADC pointing
                system("clear");
                printf("Operating mode 5 - Pointing");

                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
            case 6: { //Live feed
                system("clear");
                printf("Operating mode 6 - Sending a picture");

                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
            case 7: {
                system("clear");
                printf("Operating mode 7 - Checking ZenSat temperature");

                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
            case 9: {
                system("clear");
                printf("Operating mode 9 - Shutdown");
                main_loop_control = 1;
            }
            default: {
                valueSetter(MODE_FILE, 0);
                valueGetter(MODE_FILE, &operating_mode);
                break;
            }
        }
        createBackup();
    }
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
        blockBuilder(block, 6, i);
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
        printf("\n Digite a msg - ");
        scanf("%s",msg);

        msg[0]=pack;
        msg[1]=1;
        msg[2]=mode;

        msg[123]=pack;
        msg[124]=mode;

        msg[252]=pack;
        msg[253]=mode;

        writeMessage(NEW_TM, msg, 0, PACK_SIZE, 0);

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
    int counter = 0;
    int aux[19];

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
    aux[11] = createFile(HEALTH_FILE);
    aux[12] = createFile(HEALTH_NUMBER);
    aux[13] = createFile(PS_FILE);
    aux[14] = createFile(PS_NUMBER);
    aux[15] = createFile(ADC_FILE);
    aux[16] = createFile(ADC_NUMBER);
    aux[17] = createFile(CV_FILE);
    aux[18] = createFile(CV_NUMBER);

    for (i=0;i==19;i++){
        if (aux[i] == 0){
            counter ++;
        }
    }

    if   (counter>0) { printf("\n%d files cannot be created", counter); return 1;}
    else { printf("\nFiles successfully created");                      return 0;}
}

int compileCodes(int mode){

    if (mode == 1){
        printf("Compiling cube.c file... \n");
        delay(600000);
        system("gcc cube.c -o cube -lm");
        printf("File cube.c was already compiled.");
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
        printf("File cube.c was already compiled.");
        delay(600000);
        printf("Compiling base.c file... \n");
        delay(600000);
        system("gcc base.c -o base -lm");
        printf("File base.c was already compiled. \n");
        delay(600000);
    }
    else {
        printf("This mode of compilation is not valid");
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
    printf("zenith.h is already installed!");
    delay(2000000);

    return 0;
}

/*
int PS(){

    typedef struct {
        float shuntvoltage = 0;
        float busvoltage = 0;
        float current_mA = 0;
        float loadvoltage = 0;
    } inaData;

    inaData ina_1, ina_2, ina_3, ina_4, ina_5, ina_6;

    //READ_INAS_VALUES;
    //CONVERT_UNITS
    //SAVE_IN_FILE;
}
*/