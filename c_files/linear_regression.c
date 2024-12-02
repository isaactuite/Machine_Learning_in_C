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


double predict_single_loop(HouseDataTest *house, double *w, int n, double b);
double compute_cost(HouseDataTrain *house, int train_records, double *y, double *w, double b);

int main(void){

    double b = 785.1811367994083;
    double w[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
    double prediction=0;
    int train_read, test_read, train_records, test_records, r;
    char header[1024];
    double cost;
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

    for (int i=0; i<train_records && i<5; i++){
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

    for (int i=0; i<test_records && i<5; i++){
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
    double y[train_records];
    for (int i = 0; i < train_records; i++) {
        y[i] = houses_train[i].price;


    prediction = predict_single_loop(&houses_train[0], w, 11, b);
    printf("Prediction: %lf", prediction);
    
    cost = compute_cost(houses_train, train_records, y, w, b);
    printf("Compute Cost: %.2lf", cost);

    return 0;
}

double predict_single_loop(HouseDataTest *house, double *w, int n, double b){
    /*
    single predict using linear regression
    
    Args:
      x (double *): Pointer to an array representing the example with multiple features.
      w (double *): Pointer to an array representing model parameters (weights).
      n (int): Number of features.
      b (double): Model parameter (bias). 
      
    Returns:
      p (double)  prediction
    */

   double p = b;

    p += house->area * w[0];
    p += house->bedrooms * w[1];
    p += house->bathrooms * w[2];
    p += house->stories * w[3];
    p += house->mainroad * w[4];
    p += house->guestroom * w[5];
    p += house->basement * w[6];
    p += house->hotwaterheating * w[7];
    p += house->airconditioning * w[8];
    p += house->parking * w[9];
    p += house->prefarea * w[10];

    return p;
}

double compute_cost(HouseDataTrain *houses_train, int train_records, double *y, double *w, double b){
    /*
    compute cost
    Args:
      X Structure Data, m examples with n features
      y array : target values
      w double array : model parameters  
      b double       : model parameter
      
    Returns:
      cost double: cost
    */

    double cost = 0.0;
    for (int i = 0; i<train_records; i++){
        double f_wb_i =(
            houses_train[i].area * w[0] +
            houses_train[i].bedrooms * w[1] +
            houses_train[i].bathrooms * w[2] +
            houses_train[i].stories * w[3] +
            houses_train[i].mainroad * w[4] +
            houses_train[i].guestroom * w[5] +
            houses_train[i].basement * w[6] +
            houses_train[i].hotwaterheating * w[7] +
            houses_train[i].airconditioning * w[8] +
            houses_train[i].parking * w[9] +
            houses_train[i].prefarea * w[10] + b);
        cost = cost + pow(f_wb_i - y[i].price, 2);
    }
    cost = cost / (2 * train_records);   
    return cost;

}











//gcc linear_regression.c -o linear_regression.exe -lm
//.\linear_regression.exe