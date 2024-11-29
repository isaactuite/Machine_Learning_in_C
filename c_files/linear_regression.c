/*
Title: Implementation of linear regression
Author: Isaac Tuite
Date: 28/10/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//define structure for Training Data
typedef struct{
    int price;
    int area;
    int bedrooms;
    int bathrooms;
    int stories;
    int mainroad;
    int guestroom;
    int basement;
    int hotwaterheating;
    int airconditioning;
    int parking;
    int prefarea;
} HouseDataTrain;

//Define structure for test data
typedef struct{
    int price;
    int area;
    int bedrooms;
    int bathrooms;
    int stories;
    int mainroad;
    int guestroom;
    int basement;
    int hotwaterheating;
    int airconditioning;
    int parking;
    int prefarea;
} HouseDataTest;


int main(void){

    float b = 785.1811367994083;
    float w[] = {0, 0, 0, 0, '\0'};
    int train_read, test_read, train_records, test_records, r;
    char header[1024];
    FILE *data = fopen("../datasets/housing_prices_dataset.csv", "r");
    

    //Initialize rand
    srand(time(NULL));


    train_read = 0;
    test_read = 0;
    train_records = 0;
    test_records=0;


    if (data == NULL){
        printf("Error opnening file");
        return 1;
    }

    
    HouseDataTrain houses_train[1000];
    HouseDataTest houses_test[400];
    fgets(header, sizeof(header), data);
    do{
        if (train_records >= 1000 || test_records >= 400) {
            printf("Maximum array size reached. Stopping data loading.\n");
            break;
        }
        r = rand()%5;
        if (r == 0){
            test_read = fscanf(data,
                   "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                   &houses_test[test_records].price,
                   &houses_test[test_records].area,
                   &houses_test[test_records].bedrooms,
                   &houses_test[test_records].bathrooms,
                   &houses_test[test_records].stories,
                   &houses_test[test_records].mainroad,
                   &houses_test[test_records].guestroom,
                   &houses_test[test_records].basement,
                   &houses_test[test_records].hotwaterheating,
                   &houses_test[test_records].airconditioning,
                   &houses_test[test_records].parking,
                   &houses_test[test_records].prefarea);
            
            if (test_read != 12 && !feof(data)){
                printf("File format incorrect.\n");
                return 1;
            }
            if(test_read == 12){
                test_records++;
            }
            if (ferror(data)){
                printf("Error Reading File");
                return 1;
            }


        } else {
            train_read = fscanf(data,
                   "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                   &houses_train[train_records].price,
                   &houses_train[train_records].area,
                   &houses_train[train_records].bedrooms,
                   &houses_train[train_records].bathrooms,
                   &houses_train[train_records].stories,
                   &houses_train[train_records].mainroad,
                   &houses_train[train_records].guestroom,
                   &houses_train[train_records].basement,
                   &houses_train[train_records].hotwaterheating,
                   &houses_train[train_records].airconditioning,
                   &houses_train[train_records].parking,
                   &houses_train[train_records].prefarea);
        
        

            if (train_read == 12){
                train_records++;
            }            

            if (train_read != 12 && !feof(data)){
                printf("File format incorrect.\n");
                return 1;
            }

            if (ferror(data)){
                printf("Error Reading File");
                return 1;
            }
        }

    }while(!feof(data));

    fclose(data);
    printf("\n%d training records read\n\n", train_records+test_records);
    printf("\n================================================================\n");
    printf("Training Data:\n");
    printf("%s\n", header);

    for (int i=0; i<train_records; i++){
        printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n", 
        houses_train[i].price,
        houses_train[i].area,
        houses_train[i].bedrooms,
        houses_train[i].bathrooms,
        houses_train[i].stories,
        houses_train[i].mainroad,
        houses_train[i].guestroom,
        houses_train[i].basement,
        houses_train[i].hotwaterheating,
        houses_train[i].airconditioning,
        houses_train[i].parking,
        houses_train[i].prefarea);
    }

    printf("\n================================================================\n");
    printf("Test Data:\n");
    printf("%s\n", header);

    for (int i=0; i<test_records; i++){
        printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n", 
        houses_test[i].price,
        houses_test[i].area,
        houses_test[i].bedrooms,
        houses_test[i].bathrooms,
        houses_test[i].stories,
        houses_test[i].mainroad,
        houses_test[i].guestroom,
        houses_test[i].basement,
        houses_test[i].hotwaterheating,
        houses_test[i].airconditioning,
        houses_test[i].parking,
        houses_test[i].prefarea);
    }




    return 0;
}

int predict_single_loop(){

}












//gcc linear_regression.c -o linear_regression.exe -lm
//.\linear_regression.exe