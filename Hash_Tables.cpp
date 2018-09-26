//
//  main.cpp
//  Hashing_Credit_Cards
//
//  Created by Konstantinos Asimakopoulos on 13/5/18.
//  Copyright © 2018 Konstantinos Asimakopoulos. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct sale{                                    // Data structure that represents a specific sale
    string card_number;
    int price = 0;
    int visits = 0;
};

long int getkey(string card_number) {           // This function takes as input the card id and calculates and returns the key using the hash function
    int i, c;
    long int key = 0;
    for (i = 0; i < 16; i++) {
        c = card_number.at(i);
        key = key + c * pow(5,i+1);
    }
    return key;
}

string create_card() {                          // This functions creates the card numbers
    int a, b, c, d;
    string temp = "1234567890123456";
    a = rand() % 16;
    do {
        b = rand() % 16;
    } while (b == a);
    do {
        c = rand() % 16;
    } while (c == a || c == b);
    do {
        d = rand() % 16;
    } while (d == a || d == b || d == c);

    temp.insert(a,"A");
    temp.insert(b,"B");
    temp.insert(c,"C");
    temp.insert(d,"D");
    return temp;
}

void save_sale(sale * A, int ind, string temp, int price) {             // This function stores the sale data in the Hash Table

    if (A[ind].visits == 0) {
        A[ind].card_number = temp;
        A[ind].price = price;
        A[ind].visits = 1;
    } else if (A[ind].card_number == temp) {
        A[ind].price += price;
        A[ind].visits += 1;
    } else {
        do {
            if (ind == 87382) ind = 0;
            else ind++;
        } while (A[ind].visits != 0 && A[ind].card_number != temp);
        if (A[ind].visits == 0) {
            A[ind].card_number = temp;
            A[ind].price = price;
            A[ind].visits = 1;
        } else {
            A[ind].price += price;
            A[ind].visits += 1;
        }
    }
}

void find_print_results(sale * A) {                     // Searching and printing the results

    int i, value = 0, visits = 0;
    string max_spender, max_buyer;

    for (i = 0; i < 87383; i++) {
        if (A[i].visits != 0 ) {
            if (A[i].price > value) {
                value = A[i].price;
                max_spender = A[i].card_number;
            }
            if (A[i].visits > visits) {
                visits = A[i].visits;
                max_buyer = A[i].card_number;
            }
        }
    }

    cout << "The credit card " << max_spender << " paid the most money. Total cost: " << value << "\n";
    cout << "The credit card " << max_buyer << " made the most visits. Total visits: " << visits << "\n";
}


int main() {

    int i, ind, price;
    long int key;
    string temp, max_buyer, max_spender;
    sale A[87383];

    srand(1046966);

    // Creating 1 million sales and storing them in a Hash Table

    for (i = 0; i < 1000000; i++) {

        temp = create_card();               // Creating the random card ID

        price = rand() % 991 + 10;          // Getting the random price

        key = getkey(temp);                 // Calculating the key of the alpharethmetic string

        ind = key % 87383;                  // Getting the index from the key

        save_sale(A, ind, temp, price);     // Saving the sale's data in Hash Table

    }

    find_print_results(A);                  // Display results

    return 0;
}