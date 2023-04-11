//
// Created by National Cyber City on 2/20/2023.
//

#ifndef DIPLEVEL1_ZOOM_ONLINE_BANK_H
#define DIPLEVEL1_ZOOM_ONLINE_BANK_H

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#define SIZE 1000 // symbolic constant
struct trans{
    char note[200];
    char withdrawNote[200];
};
//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
    float loan_rate;
    char acc_s[10]; //account status
    int acc_level; // copy
    unsigned int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];
    int withdraw_count;

};

struct data db[SIZE];


struct my_time{
    char c_time[25];

};

struct my_time Ctime[1];

//current time array
struct my_day{
    char data[2];
};
struct my_day date[1];

struct node1{
    char year_name[4];
};
struct node1 year[1];

struct node3{
    char money_arr[20];
};
struct node3 addMoney[0];

// Global Variable Declaration
int users=0;
int gValid=-1;
int emailExist=-1;
int pass_Exist=-1;
int two_charArray=-1;
int nrc_valid = -1;
int strongPass=-1;
int phone_valid=-1;
int phone_found=-1;

int trans_limit=0;
int receive_limit=0;

// current time variables
int current_date=0;
struct node{
    char month_name[3];
};
struct node month[1];
int current_year=0;
unsigned int current_receive_amount=0;

// global array
int space_array[30];
char int_to_char_array_data[10];
unsigned int charArray_to_unsignedInt_data=0;


unsigned int current_day_to_transfer=0;
unsigned int current_amount_to_transfer=0;

int user_count=0;


// For Function Declaration
void welcome();
void login();
void userSector();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void compare_two_charArray(char first[50] , char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned int phone);
void copy_two_char_array(char receiver[200] ,char transmitter[200] );
void finding_phone_number(unsigned int tofind);
void transfer_money(int transfer , int receiver , unsigned int amount);
void space_counter();
void recording_alldata_toFile();
void transaction_record(int transfer , int receiver , char who,unsigned int amount);
void integer_to_char(unsigned int value);

void get_time();
void get_limit_amount(int user_index);
unsigned int calculate_amounts_same_days(int to_calcu_index);

unsigned int charArray_to_unsigned_fun(char charArray[]);
unsigned int charArray_to_unsigned_fun2(char charArray[],int length);
void current_data_toTransfer(unsigned int current_amount_toTransfer);
void checking_record_day(int user_index);
void get_same_day();
void withdraw_record(unsigned int amount,int userIndex);
void withdraw(int userIndex);
void checking_today_activities(int userIndex);

void welcome(){

    int option=0;
    printf("Welcome to our Bank!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!:::");
    scanf("%d",&option);

    if(option == 1){

        login();

    } else if(option == 2){
        registration();

    } else if( option == 3){

        recording_alldata_toFile();
        exit(1);
    } else {
        welcome();
    }

}

void login(){

    char l_email[50];
    char l_pass[50];
    emailExist=-1;
    two_charArray=-1;

    while (emailExist == -1 || two_charArray==-1){
        printf("This is login:\n");

        printf("Enter your email:");
        scanf(" %[^\n]",&l_email[0]);
        printf("Enter your password:");
        scanf(" %[^\n]",&l_pass[0]);
        emailExistChecking(l_email);
        compare_two_charArray(db[emailExist].password,l_pass);

        if(emailExist == -1 || two_charArray==-1){
            emailExist=-1;
            two_charArray=-1;
            printf("Your login credential was wrong:\n");
        }
    }
    printf("Welcome Mr/Mrs: %s\n",db[emailExist].name);
    printf("Your current amount : %u\n",db[emailExist].cur_amount);
    userSector();

}


void userSector(){

    int user_option=0;
    unsigned int phone=0;
    unsigned int amount_to_transfer=0;
    printf("This is user Sector\n");
    checking_today_activities(emailExist);
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:\nPress 3 to update your information\nPress 4 Cash in :\nPress 5 to Loan:\nPress 6 to view your history:\nPress 7 Exit");
    scanf("%d",&user_option);

    if(user_option==1){
        printf("This is for Transfer Option:\n");

        phone_found=-1;

        while (phone_found==-1){
            printf("Enter receive phone number : ");
            scanf("%u",&phone);
            finding_phone_number(phone);
            if(phone_found==-1){
                printf("Phone number does not belong to any user:\n");
            }

        }
        printf("Are u sure to send for %s email: %s:\n",db[phone_found].name,db[phone_found].email);

        while (amount_to_transfer<db[emailExist].cur_amount){

            printf("Enter your amount: to transfer:");
            scanf("%u",&amount_to_transfer);

            if(db[emailExist].cur_amount-1000>amount_to_transfer){
                break;
            } else{
                printf("not sufficient balance:\n");
                amount_to_transfer=0;
            }


        }
        two_charArray=-1;
        char tran_pass[50];
        while (two_charArray==-1){
            printf("Enter password to proceed transaction:");
            scanf(" %[^\n]",&tran_pass[0]);
            compare_two_charArray(db[emailExist].password,tran_pass);

            if(two_charArray==-1){
                printf("Wrong credential:\n");
            }


        }

        transfer_money(emailExist,phone_found,amount_to_transfer);

        userSector();


    }else if(user_option==2){
        withdraw(emailExist);
    } else if(user_option==7){
        welcome();
    }


}

void withdraw(int userIndex){
    unsigned int withdrawMoney;
    char tempoPass[50];
    printf("This is withdraw section\n");
    printf("This is your amount: %u\n",db[userIndex].cur_amount);
    printf("Enter amount that you want to withdraw:");
    scanf("%u",&withdrawMoney);
    if(withdrawMoney>=db[userIndex].cur_amount-1000){
        printf("Insufficient money to withdraw\n");
        printf("Your can only withdraw %uks\n",db[userIndex].cur_amount-1000);
        withdraw(userIndex);
    }else{
        printf("Enter your password to confirm:");
        scanf(" %[^\n]",&tempoPass[0]);
        two_charArray=-1;
        compare_two_charArray(db[userIndex].password,tempoPass);
        if(two_charArray!=1){
            printf("Your password is wrong,Try again\n");
            withdraw(userIndex);
        }else{
            int option;
            db[userIndex].cur_amount-=withdrawMoney;
            printf("Withdraw success\n");
            withdraw_record(withdrawMoney,userIndex);
            printf("Your amount has left %u ks\n",db[userIndex].cur_amount);
            printf("Press 1 to withdraw again:\nPress 2 to go User Sector:");
            scanf("%d",&option);
            if(option==1){
                withdraw(userIndex);
            }else if(option==2){
                userSector();
            }else{
                printf("Invalid option\n");
                userSector();
            }
        }
    }
}

void withdraw_record(unsigned int amount,int userIndex){
    int index_point=0;

    char withdraw[15]={'Y','o','u','-','w','i','t','h','d','r','a','w','e','d','-'};
    char preposition[3]={'-','a','t'};

    for(int i=0 ; i<10 ; i++){
        int_to_char_array_data[i]='\0';
    }

    integer_to_char(amount);
    int char_count = charCounting(int_to_char_array_data);

    db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]='?';
    index_point++;

    for (int i = 0; i <15 ; i++) {
        db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]=withdraw[i];
        index_point++;
    }

    db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]='$';
    index_point++;

    for (int i = 0; i < char_count; i++) {
        db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]=int_to_char_array_data[i];
        index_point++;
    }

    for (int i = 0; i < 3; i++) {
        db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]=preposition[i];
        index_point++;
    }

    get_time();
    for (int i = 0; i < 25; i++) {
        db[userIndex].trc[db[userIndex].withdraw_count].withdrawNote[index_point]=Ctime[0].c_time[i];
        index_point++;
    }

    db[userIndex].withdraw_count += 1;
    space_array[userIndex]+=1;
}

void get_time(){
    time_t tm;
    time(&tm);

//    printf("Current time : %s\n", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));

    fclose(fptr);

    int index=0;
    int time_space_counter=0;

    Ctime[0].c_time[index]='-';
    index++;

    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while (!feof(fptr2)){

        if( c==' '){

            time_space_counter++;

            if(time_space_counter == 1){
                Ctime[0].c_time[index]='!';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter==4){
                Ctime[0].c_time[index]='@';
                c = fgetc(fptr2);
                index++;
            } else{
                Ctime[0].c_time[index]='-';
                c = fgetc(fptr2);
                index++;
            }


        } else{

            Ctime[0].c_time[index]=c;
            c = fgetc(fptr2);
            index++;

        }


    }

}


void checking_today_activities(int userIndex){

    get_same_day();

    printf("\nToday Activities histories\n");

    int withdraw_note_record = db[userIndex].withdraw_count;
    int withdraw_check=0;

    for (int i = withdraw_note_record-1; i >=0 ; i--) {

        int money_index=0;
        int index_point=0;
        int current_record_length = charCounting(db[userIndex].trc[i].withdrawNote);

        for (int j = 0; j < current_record_length; j++) {

          if(db[userIndex].trc[i].withdrawNote[index_point]=='$'){
                money_index=index_point+1;
            }else if(db[userIndex].trc[i].withdrawNote[index_point]=='!'){
                break;
            }
            index_point++;

        }

        index_point+=1;

        int month_check=0;
        for (int j = 0; j < 3; j++) {

            if(db[userIndex].trc[i].withdrawNote[index_point]!=month[0].month_name[j]){
                month_check=1;
            }
            index_point++;

        }

        if(month_check!=1){

            index_point++;

            date[0].data[0]=db[userIndex].trc[i].withdrawNote[index_point];
            index_point++;
            date[0].data[1]=db[userIndex].trc[i].withdrawNote[index_point];
            index_point++;

            unsigned int c_day = charArray_to_unsigned_fun2(date[0].data,2);

            if(c_day == current_date){

                for (int j = index_point; j < current_record_length; j++) {

                    if(db[userIndex].trc[i].withdrawNote[j]=='@'){
                        break;
                    }
                    index_point++;

                }

                index_point++;
                year[0].year_name[0]=db[userIndex].trc[i].withdrawNote[index_point];
                index_point++;
                year[0].year_name[1]=db[userIndex].trc[i].withdrawNote[index_point];
                index_point++;
                year[0].year_name[2]=db[userIndex].trc[i].withdrawNote[index_point];
                index_point++;
                year[0].year_name[3]=db[userIndex].trc[i].withdrawNote[index_point];

                unsigned int c_year = charArray_to_unsigned_fun2(year[0].year_name,4);

                if(c_year==current_year){

                    for(int m=0;m<10;m++){
                        addMoney[0].money_arr[m]='\0';
                    }

                    int money_number=0;

                    for (int j = money_index; j <current_record_length ; j++) {

                        if(db[userIndex].trc[i].withdrawNote[j]=='-'){
                            break;
                        }
                        money_number++;

                    }

                    for (int j = 0; j < money_number ; j++) {

                        addMoney[0].money_arr[j] = db[userIndex].trc[i].withdrawNote[money_index];
                        money_index++;

                    }

                    unsigned int money_amount = charArray_to_unsigned_fun2(addMoney[0].money_arr,money_number);

                    withdraw_check=1;

                    printf("You withdrew %uks today\n",money_amount);

                }else{
                    break;
                }

            }else{
                break;
            }

        }else{
            break;
        }

    }

    if(withdraw_check==0){

        printf("No withdraw history today\n");

    }

    int note_record = space_array[userIndex]-15-db[userIndex].withdraw_count;
    int transfer_and_receive_check=0;

    for (int i = note_record-1; i >=0 ; i--) {

        int money_index=0;
        int index_point=0;
        int current_record_length = charCounting(db[userIndex].trc[i].note);
        int transfer_or_receive=0;

        for (int j = 0; j < current_record_length; j++) {

            if(db[userIndex].trc[i].note[index_point]=='&'){
                transfer_or_receive=1;
            }else if(db[userIndex].trc[i].note[index_point]=='$'){
                money_index=index_point+1;
            }else if(db[userIndex].trc[i].note[index_point]=='!'){
                break;
            }
            index_point++;

        }

        index_point+=1;

        int month_check=0;
        for (int j = 0; j < 3; j++) {

            if(db[userIndex].trc[i].note[index_point]!=month[0].month_name[j]){
                month_check=1;
            }
            index_point++;

        }

        if(month_check!=1){

            index_point++;

            date[0].data[0]=db[userIndex].trc[i].note[index_point];
            index_point++;
            date[0].data[1]=db[userIndex].trc[i].note[index_point];
            index_point++;

            unsigned int c_day = charArray_to_unsigned_fun2(date[0].data,2);

            if(c_day == current_date){

                for (int j = index_point; j < current_record_length; j++) {

                    if(db[userIndex].trc[i].note[j]=='@'){
                        break;
                    }
                    index_point++;

                }

                index_point++;
                year[0].year_name[0]=db[userIndex].trc[i].note[index_point];
                index_point++;
                year[0].year_name[1]=db[userIndex].trc[i].note[index_point];
                index_point++;
                year[0].year_name[2]=db[userIndex].trc[i].note[index_point];
                index_point++;
                year[0].year_name[3]=db[userIndex].trc[i].note[index_point];

                unsigned int c_year = charArray_to_unsigned_fun2(year[0].year_name,4);

                if(c_year==current_year){

                    for(int m=0;m<10;m++){
                        addMoney[0].money_arr[m]='\0';
                    }

                    int money_number=0;

                    for (int j = money_index; j <current_record_length ; j++) {

                        if(db[userIndex].trc[i].note[j]=='-'){
                            break;
                        }
                        money_number++;

                    }

                    for (int j = 0; j < money_number ; j++) {

                        addMoney[0].money_arr[j] = db[userIndex].trc[i].note[money_index];
                        money_index++;

                    }

                    unsigned int money_amount = charArray_to_unsigned_fun2(addMoney[0].money_arr,money_number);

                    transfer_and_receive_check=1;

                    if(transfer_or_receive==1){
                        printf("You received %uks today\n",money_amount);
                    }else{
                        printf("You transfer %uks today\n",money_amount);
                    }

                }else{
                    break;
                }

            }else{
                break;
            }

        }else{
            break;
        }

    }

    if(transfer_and_receive_check==0){
        printf("No transfer and received today\n\n");
    }else{
        printf("\n");
    }

}

void transfer_money(int transfer , int receiver , unsigned int amount){

    printf("loading to transfer.....\n");

    // to insert transaction amount limit per day function
    db[transfer].cur_amount = db[transfer].cur_amount-amount;
    db[receiver].cur_amount = db[receiver].cur_amount+amount;
    printf("transaction complete!\n");
    transaction_record(transfer,receiver,'t',amount);
    transaction_record(transfer,receiver,'r',amount);
    printingAllData();

}

void transaction_record(int transfer , int receiver , char who,unsigned int amount){
// from-WinHtut-to-lonelone-100
    int trans_name_counter = charCounting(db[transfer].name);
    int receive_name_counter = charCounting(db[receiver].name);
    integer_to_char(amount);
    int amount_counter = charCounting(int_to_char_array_data);

    char from[5]={'F','r','o','m','-'};
    char to[4]={'-','t','o','-'};

    if(who == 't'){
        int index_point=0;
        for(int i=0; i<5; i++){
            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[i] = from[i];
            index_point++;
        }
        //int aaa=0;
        //int end_point = trans_name_counter+index_point;
        for(int a=0; a<trans_name_counter; a++){

            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]=db[transfer].name[a];
            index_point++;

        }
        for(int a=0; a<4; a++){
            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]=to[a];
            index_point++;
        }
        for (int aaa = 0; aaa < receive_name_counter; ++aaa) {
            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]=db[receiver].name[aaa];
            index_point++;

        }

        db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]='$';
        index_point++;
        for(int aaa=0; aaa<amount_counter; aaa++){
            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]=int_to_char_array_data[aaa];
            index_point++;
        }

        get_time();
        for(int i=0; i<25; i++){

            db[transfer].trc[space_array[transfer]-15-db[transfer].withdraw_count].note[index_point]=Ctime[0].c_time[i];
            index_point++;
        }


        space_array[transfer] +=1;


    } else{
        //lonelone-
        char rec[15]={'-','&','R','e','c','e','i','v','e','-','F','r','o','m','-'};

        int index_point=0;

        for(int a=0; a<receive_name_counter; a++){
            db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]=db[receiver].name[a];
            index_point++;

        }
        for(int a=0; a<15; a++){
            db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]=rec[a];
            index_point++;
        }
        for(int a=0; a<trans_name_counter; a++){
            db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]=db[transfer].name[a];
            index_point++;
        }
        db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]='$';
        index_point++;
        for(int aaa=0; aaa<amount_counter; aaa++){
            db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]=int_to_char_array_data[aaa];
            index_point++;
        }


        get_time();
        for(int a=0; a<25; a++){
            db[receiver].trc[space_array[receiver]-15-db[transfer].withdraw_count].note[index_point]=Ctime[0].c_time[a];
            index_point++;
        }

        space_array[receiver] +=1;


    }


}



//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
void loadingAllDataFromFile(){

    FILE *fptr = fopen("ncc_db1.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%u%u%s%d",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,
                   &db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,
                   &db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,
                   &db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay);

            char c = fgetc(fptr);
            int check=0;

            int note_point=0;
            int withdraw_note_point=0;

            for(int gcc=0; gcc<space_array[ncc]-15 ; gcc++){
                c=fgetc(fptr);
                if(c=='?'){
                    db[ncc].trc[withdraw_note_point].withdrawNote[0]=c;
                    fscanf(fptr,"%s",&db[ncc].trc[withdraw_note_point].withdrawNote[1]);
                    withdraw_note_point++;
                    check++;
                }else{
                    db[ncc].trc[gcc].note[0]=c;
                    fscanf(fptr,"%s",&db[ncc].trc[note_point].note[1]);
                    note_point++;
                }
                c= fgetc(fptr);
            }
            if(check==0){
                db[ncc].withdraw_count=0;
            }else{
                db[ncc].withdraw_count=check;
            }



            if(db[ncc].email[0] == '\0'){
                break;
            }

            users++;
            user_count++;

        }

    }

    fclose(fptr);

}
void printingAllData(){

    for(int ncc=0; ncc<user_count ; ncc++){


        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%u-%u-%s-%d",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address,db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15-db[ncc].withdraw_count ; gcc++){
            printf("-%s",&db[ncc].trc[gcc].note[0]);
        }

        for (int i = 0; i < db[ncc].withdraw_count; i++) {
            printf("-%s",&db[ncc].trc[i].withdrawNote[0]);
        }

        printf("\n");
    }

}

void recording_alldata_toFile(){
    FILE *fptr = fopen("ncc_db1.txt","w");
    if(fptr==NULL){
        printf("cannot open file to record:\n");

    }

    for(int ncc=0; ncc<user_count; ncc++){
        fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%u%c%u%c%s%c%d",db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',db[ncc].email,' ',db[ncc].password,
                ' ',db[ncc].pOrb, ' ',db[ncc].loan_s,' ',db[ncc].monthly_income,' ',db[ncc].loan_amount ,' ',db[ncc].loan_rate ,' ', db[ncc].acc_s ,' ',db[ncc].acc_level,
                ' ',db[ncc].phNumber , ' ',db[ncc].cur_amount,' ',db[ncc].address,' ',db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15-db[ncc].withdraw_count ; gcc++){
            fprintf(fptr," %s",&db[ncc].trc[gcc].note[0]);
        }
        for(int i=0; i<db[ncc].withdraw_count; i++){
            fprintf(fptr," %s",&db[ncc].trc[i].withdrawNote[0]);
        }
        fprintf(fptr,"%c",'\n');
    }



}

void space_counter(){
    FILE *fptr = fopen("ncc_db1.txt","r");

    if(fptr==NULL){
        printf("File opening error at space_counter fun:\n");
    } else{
        char c = fgetc(fptr);
        int index=0;

        while (!feof(fptr)){
            if( c !='\n'){
                if(c==' '){
                    space_array[index]+=1;

                }
                c = fgetc(fptr);

            } else{

                index++;
                c = fgetc(fptr);
            }

        }

        for (int aaa = 0; aaa < 30; ++aaa) {
            printf("%d ",space_array[aaa]);
        }
        printf("\n");



    }


}



void registration(){

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_pass[50];
    unsigned int re_phone=0;

    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    gValid=-1;
    myGmailValidation(reEmail);
    if( gValid != -1){

        emailExist=-1;
        emailExistChecking(reEmail);

        if( emailExist == -1 ){

            printf("Your email is valid!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&re_name[0]);
            nrc_valid=-1;
            while (nrc_valid==-1){
                printf("Enter your NRC:");
                scanf(" %[^\n]",&re_nrc[0]);

                nrc_validation(re_nrc);
                if(nrc_valid == -1){
                    printf("Your NRC Format was Not Valid!\n");
                }

            }
            printf("Your NRC Format was Valid!\n");
            strongPass=-1;
            while (strongPass == -1){
                printf("Enter your password!:");
                scanf(" %[^\n]",&re_pass[0]);
                myStrongPassword(re_pass);
                if(strongPass == -1){
                    printf("Your Password Format too weak and Try Again!\n");
                }
            }
            printf("Your password format was valid and saved!\n");

            phone_valid=-1;
            while (phone_valid==-1){
                printf("[X]Enter your Phone Number:");
                scanf("%u",&re_phone);

                phone_validation(re_phone);

                if(phone_valid == -1){

                    printf("[-]Your phone number is already registered:\n");
                }

            }
            printf("[+] Your phone is correct and saved!\n");

            printf("[+] Enter your monthly income:");
            scanf("%u",&db[users].monthly_income);
            printf("[+] Enter your current amount:");
            scanf("%u",&db[users].cur_amount);

            printf("[+]Enter your address");
            scanf(" %[^\n]",&db[users].address[0]);

            copy_two_char_array(db[users].pOrb , db[2].pOrb);
            copy_two_char_array(db[users].loan_s,db[2].loan_s);

            db[users].loan_amount= db[2].loan_amount;
            db[users].phNumber= re_phone;
            db[users].loan_rate= db[2].loan_rate;
            copy_two_char_array(db[users].acc_s,db[2].acc_s);
            db[users].acc_level= db[2].acc_level;
            db[users].transAmoLimitPerDay= db[2].transAmoLimitPerDay;
            copy_two_char_array(db[users].trc[0].note,db[2].trc[0].note);
            copy_two_char_array(db[users].email,reEmail);
            copy_two_char_array(db[users].nrc,re_nrc);
            copy_two_char_array(db[users].password,re_pass);
            copy_two_char_array(db[users].name,re_name);

//            char pOrb[20]; // personal or business
//            char loan_s[2]; // loan status
//            unsigned int monthly_income;x
//            unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
//            float loan_rate;
//            char acc_s[10]; //account status
//            int acc_level; // copy
//            unsigned int phNumber;x
//            unsigned int cur_amount; //current amountx
//            char address[100];x
//            int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
//            struct trans trc[100];
            db[users].id = users+1;
            users++;
            printingAllData();
            welcome();




        } else{

            printf("Your gmail already taken!\n");
            registration();

        }


    } else{
        printf("Your gmail format not valid!\n");
        registration();
    }



}

int charCounting(char toCount[100]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<100 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char toValidate[50]){

    // winhtut@gmail.com
    int toEndPoint = charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;

    for(int i=0; i<toEndPoint; i++){

        if(toValidate[i] == '@' || toValidate[i] ==' '){
            break;
        }else{
            count++;
        }

    }
    int tocheck=0;
    for( int i=0 ; i< toEndPoint ; i++){

        if( toValidate[count] != form[i]){
            break;
        } else{
            count++;
            tocheck++;
        }
    }

    if( tocheck == 10){
        gValid=1;
    }

}

void emailExistChecking(char toCheck[50]){

    int toCheckCount = charCounting(toCheck);
    int sameCounting=0;

    for(int ncc=0; ncc<users ; ncc++){
        int dbEmailCount = charCounting(db[ncc].email);

        sameCounting=0;
        if( toCheckCount == dbEmailCount){

            for(int gcc=0; gcc<toCheckCount ; gcc++){

                if(toCheck[gcc] != db[ncc].email[gcc] ){
                    break;
                } else{
                    sameCounting++;
                }

            }


        }

        if(toCheckCount == sameCounting){

            emailExist = ncc;
        }

    }


}

void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }

    }


}

void compare_two_charArray(char first[50] , char second[50]){

    int first_counter =  charCounting(first);
    int second_counter = charCounting(second);
    int same_counter = 0;

    if( first_counter == second_counter) {
        for (register int i = 0; i < first_counter; i++) {
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if( first_counter == same_counter){
            two_charArray = 1;
        }
    }

}

void myStrongPassword(char pass[50]){

    int i=0;
    int special=0;
    int numberChar=0;
    int capChar=0;
    int smallChar=0;
    int pass_counter = charCounting(pass);
    while (strongPass == -1){
        if( i == pass_counter){
            strongPass=-1;
            break;
        }
        if( pass[i] >= 33 && pass[i] <= 42){

            special++;
        } else  if( pass[i] >= 48 && pass[i] <= 57){

            numberChar++;

        } else if( pass[i] >= 65 && pass[i] <= 90){

            capChar++;
        } else if( pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }
        i++;
        if( special > 0 && numberChar >0 && capChar > 0 && smallChar >0){
            strongPass = 1;
        }
    }


}

void phone_validation(unsigned int phone){
    int phone_counter=0;
    for(int i=0; i<users ; i++){

        if(phone != db[i].phNumber){

            phone_counter++;
        } else{
            phone_valid=-1;
            break;
        }

    }
    if(phone_counter == users){
        phone_valid=1;
    }

}

void copy_two_char_array(char receiver[200] ,char transmitter[200] ){


//    for(register int i=0; i<200; i++){
//        receiver[i]='\0';
//    }

    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }


}

void finding_phone_number(unsigned int tofind){

    for(int i=0; i<users ; i++){

        if(db[i].phNumber==tofind){
            phone_found=i;
            break;
        }
    }



}


void get_limit_amount(int user_index){

    // 1 for personal and 2 for business
    int acc_level = db[user_index].acc_level;
    char pOrb =db[user_index].pOrb[0];
    int p_or_b = 0;
    if(pOrb == 'p'){
        p_or_b=1;
    } else{
        p_or_b=2;
    }

    switch (acc_level) {
        case 1:
            if(p_or_b==1){
                trans_limit=100000;
                receive_limit=100000;
            } else{
                trans_limit=1000000;
                receive_limit=1000000;
            }
            break;
        case 2:
            if(p_or_b==1){
                trans_limit=50000;
                receive_limit=50000;
            } else{
                trans_limit=500000;
                receive_limit=500000;
            }
            break;
        case 3:
            if(p_or_b==1){
                trans_limit=10000;
                receive_limit=10000;
            } else{
                trans_limit=100000;
                receive_limit=100000;
            }
            break;
        default:
            break;
    }


}

void current_data_toTransfer(unsigned int current_amount_toTransfer){
    char get_current_day[2];
    get_time();
    printf("current info : %s : current amount to transfer: %u",Ctime[0].c_time,current_amount_toTransfer);

    get_current_day[0]=Ctime[0].c_time[9];
    get_current_day[1]=Ctime[0].c_time[10];
    unsigned int current_day_to_transferL = charArray_to_unsigned_fun(get_current_day);
    // printf("\nCurrent day : %d\n",current_day_to_transfer);

    current_amount_to_transfer=current_amount_toTransfer;
    current_day_to_transfer=current_day_to_transferL;

}

// to calculate all amount of same days
unsigned int calculate_amounts_same_days(int to_calcu_index){

    int record_counter =space_array[to_calcu_index]-15;
    int index_counter=0;

    char amount_char_array[10];
    char day_char_array[3];
    for(int a=record_counter-1; a>=0 ; a--){


        int current_record_counter =  charCounting(db[to_calcu_index].trc[a].note);

        // to get $
        for(int aa=0; aa<current_record_counter; aa++){
            if(db[to_calcu_index].trc[a].note[aa]=='$'){
                break;
            }

            index_counter++;
        }
        int quantity_of_amount=0;
        for(int aaa=index_counter; aaa<current_record_counter; aaa++){

            if(db[to_calcu_index].trc[a].note[aaa]=='-'){

                break;

            }
            quantity_of_amount++;

        }
        index_counter++;
        for(int x=0; x<quantity_of_amount-1 ; x++){

            amount_char_array[x]=db[to_calcu_index].trc[a].note[index_counter];
            index_counter++;

        }
        unsigned int current_record_amount = charArray_to_unsigned_fun(amount_char_array);
        printf("current_record_amount: %d\n",current_record_amount);

        //to get day of current record:

        for(int xx=index_counter; xx<current_record_counter; xx++){

            if(db[to_calcu_index].trc[a].note[xx]=='!'){
                break;
            }
            index_counter++;
        }

        day_char_array[0]=db[to_calcu_index].trc[a].note[index_counter+5];
        day_char_array[1]=db[to_calcu_index].trc[a].note[index_counter+6];
        unsigned int current_record_day= charArray_to_unsigned_fun(day_char_array);

        printf("Current record day: %d\n",current_record_day);

        if(current_record_day!=current_day_to_transfer){
            break;
        }

        index_counter=0;
    }




}


void integer_to_char(unsigned int value){

    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);


}
unsigned int charArray_to_unsigned_fun(char charArray[]){
    unsigned int data=0;
    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        int length= charCounting(charArray);
        for (int i = 0; i < length; i++) {
            fprintf(fptr,"%c",charArray[i]);
        }
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%u",&data);
    fclose(fptr2);

    return data;
}

unsigned int charArray_to_unsigned_fun2(char charArray[],int length){
    unsigned int data=0;
    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        for (int i = 0; i < length; i++) {
            fprintf(fptr,"%c",charArray[i]);
        }
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%u",&data);
    fclose(fptr2);

    return data;
}


//this function is to get current day,month and year
void get_same_day(){
    get_time();
//    printf("Current time: %s",Ctime[0].c_time);
    date[0].data[0]=Ctime[0].c_time[9];
    date[0].data[1]=Ctime[0].c_time[10];
    current_date =charArray_to_unsigned_fun2(date[0].data,2);
//    printf("Current day: %d\n",current_date);

    month[0].month_name[0]=Ctime[0].c_time[5];
    month[0].month_name[1]=Ctime[0].c_time[6];
    month[0].month_name[2]=Ctime[0].c_time[7];
//    printf("Current month: %s\n",month[0].month_name);

    year[0].year_name[0]=Ctime[0].c_time[21];
    year[0].year_name[1]=Ctime[0].c_time[22];
    year[0].year_name[2]=Ctime[0].c_time[23];
    year[0].year_name[3]=Ctime[0].c_time[24];
    current_year= charArray_to_unsigned_fun2(year[0].year_name,4);
//    printf("Current year: %d\n",current_year);
}

//this function is to check day of receive-record
void checking_record_day(int user_index){
    int record_counter = space_array[user_index]-15;
    int index_counter=0;
    int check_point=0;

    for (int i = record_counter-1; i >=0 ; i--) {
        index_counter=0;
        int current_record_length= charCounting(db[user_index].trc[i].note);
        int money_index=0;

        //check receive-rec or transfer-record
        for (int j = 0; j < current_record_length ; j++) {
            if(db[user_index].trc[i].note[j]=='-'){
                break;
            }else if(db[user_index].trc[i].note[j]=='&'){
                check_point=1;
            }
            index_counter++;
        }

        //check-point=0 means this is transfer-record or it's receive-record
        if(check_point!=0){
            check_point=0;
            //checking month
            for (int j = index_counter; j < current_record_length; j++) {
                if(db[user_index].trc[i].note[j]=='$'){
                    //this index is where amount is located. if day is confirmed we will use it later
                    money_index=j+1;
                }
                if(db[user_index].trc[i].note[j]=='!'){
                    break;
                }
                index_counter++;
            }
            index_counter+=1;
            for (int j = 0; j < 3; j++) {
                if(db[user_index].trc[i].note[index_counter]!=month[0].month_name[j]){
                    check_point=1;
                }
                index_counter++;
            }

            //check-point=0 means that month in record is not current month
            if(check_point!=1){

                //checking day
                index_counter+=1;
                date[0].data[0]=db[user_index].trc[i].note[index_counter];
                index_counter++;
                date[0].data[1]=db[user_index].trc[i].note[index_counter];
                index_counter++;
                int c_day= charArray_to_unsigned_fun2(date[0].data,2);

                //c_day!=current_date means that day is not current day
                if(c_day==current_date){

                    //checking year
                    for (int j = index_counter; j <current_record_length ; j++) {
                        if(db[user_index].trc[i].note[j]=='@'){
                            break;
                        }
                        index_counter++;
                    }
                    index_counter+=1;
                    year[0].year_name[0]=db[user_index].trc[i].note[index_counter];
                    index_counter++;
                    year[0].year_name[1]=db[user_index].trc[i].note[index_counter];
                    index_counter++;
                    year[0].year_name[2]=db[user_index].trc[i].note[index_counter];
                    index_counter++;
                    year[0].year_name[3]=db[user_index].trc[i].note[index_counter];

                    int c_year= charArray_to_unsigned_fun2(year[0].year_name,4);

                    if(c_year==current_year){
                        //add money
                        int money_number=0;
                        for (int k = money_index; k <current_record_length ; k++) {
                            if(db[user_index].trc[i].note[k]=='-'){
                                break;
                            }
                            money_number++;
                        }
                        for(int m=0;m<10;m++){
                            addMoney[0].money_arr[m]='\0';
                        }
                        for (int l = 0; l <money_number ; l++) {
                            addMoney[0].money_arr[l]=db[user_index].trc[i].note[money_index];
                            money_index++;
                        }

                        int c_money= charArray_to_unsigned_fun2(addMoney[0].money_arr,money_number);

                        current_receive_amount+=c_money;
                        printf("%u recorded\n",current_receive_amount);
                        index_counter=0;

                    }


                }else{
                    break;
                }
            }


        }


    }
    if(current_receive_amount==0){
        printf("No receive records today\n");
        printf("You can receive more\n");
    } else{
        printf("Today receive amount is : %u\n",current_receive_amount);
        get_limit_amount(user_index);
        printf("Your receive amount limit is: %d\n",receive_limit);
        if(current_receive_amount<receive_limit){
            printf("You can receive more\n");
        }else{
            printf("You can't receive nomore\n");
        }
    }
}

#endif //DIPLEVEL1_ZOOM_ONLINE_BANK_H

//error at year index !!!!!!!!!!!!!


// to write get_record function
// to calculate time different and trans limit

//to write
//for coming day
// to clear for current day and amount for each transaction record