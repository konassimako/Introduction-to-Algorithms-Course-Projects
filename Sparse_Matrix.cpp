//
//  main.cpp
//  Airport_Sparse_Matrix
//
//  Created by Konstantinos Asimakopoulos on 2/4/18.
//  Copyright © 2018 Konstantinos Asimakopoulos. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

float distance(int a1, int a2, int * x, int * y) {          // This function returns the distance in 100km between the airports whose ID's are a1 & a2
    float d = sqrt(pow((x[a1]-x[a2]),2) + pow((y[a1]-y[a2]),2));
    return d;
}



int main() {
    const int length = 33, width = 21;      // Length & width is measured in 100km
    int x[1000], y[1000], iloc[1000], dest[10000], next[10000];
    float  dist[10000], sum = 0, min;
    int i, j = 0, p, a1, a2, test;
    
    // Creating all the airports
    
    srand(1046966);
    for (i = 0; i < 1000; i++) {
        p = rand() % (length * width);
        x[i] = p % width;                   // Horizontal Coordinate
        y[i] = p / length;                  // Vertical Coordinate
    }
    
    // Initializing the iloc matrix and th next matrix
    
    for (i = 0; i < 1000; i++) {
        iloc[i] = 0;
    }
    
    for (i = 0; i < 10000; i++) {
        next[i] = 0;
    }
    
    
    // Creating 10000 flight connections and storing them in a sparse matrix
    
    srand(1046966);
    for (i = 0; i < 10000; i++) {
        p = rand() % 1000000;
        a1 = p / 1000;
        a2 = p % 1000;
        // Saving data in sparse matrix
        if (iloc[a1] == 0) {
            iloc[a1] = j;
            dest[j] = a2;
            dist[j] = distance(a1, a2, x, y);
            next[j] = -1;
            j++;
        } else {
            test = iloc[a1];
            do {
                test = next[test];
            } while (test != -1);
            dest[j] = a2;
            dist[j] = distance(a1, a2, x, y);
            next[j] = -1;
            next[test] = j;
            j++;
        }
    }
    
    // Calculating the minimum distances sum
    
    for (i = 0; i < 1000; i++) {                            // For each airport
        if (iloc[i] != 0) {
            test = iloc[i];
            min = dist[test];
            do {                                            // Search connections from specific airport until there are none left
                if (dist[test] < min) min = dist[test];
                test = next[test];
            } while (test != -1);
            sum += min;
        }
    }
    
    // Printing the result
    
    cout << "The sum of the minimum distances from each airport is: " << sum << endl;
    
    return 0;
}
