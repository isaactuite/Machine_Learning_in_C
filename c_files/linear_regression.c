/*
Title: Implementation of linear regression
Author: Isaac Tuite
Date: 28/10/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    FILE *train_data = fopen("house_prices_train.csv", "r");

    if (train_data == NULL){
        printf("Unable to open file, sorry!");
        exit(-1);
    }

    printf("I was able to open the file");
    
    return 0;
}