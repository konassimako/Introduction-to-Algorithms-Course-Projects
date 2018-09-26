//
//  main.cpp
//  Project 1o
//
//  Created by Konstantinos Asimakopoulos on 4/3/18.
//  Copyright © 2018 Konstantinos Asimakopoulos. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

int * CreateRandomNumbers(unsigned int seed) {  // Returns a pointer to an array of random 10000 ints between [-10,10]
    static int A[10000];
    int i;
    srand(seed);
    for (i = 0; i < 10000; i++) {
        A[i] = rand() % 21 +(-10);
    }
    return A;
}

int main() {
    int *p;
    int i, j, k, m = 0, s;
    int S[10000], M[10000];
    const int N = 10000;
    
    time_t t_start;
    time_t t_end;
    
    p = CreateRandomNumbers(1046966);
    
    // O(N^3) Complexity Algorithm
    
    t_start = time(NULL);
    
    for (j = 0; j < N; j++) {
        for (k = j; k < N; k++) {
            s = 0;
            for (i = j; i <= k; i++) {
                s = s + p[i];
            }
            if (s > m) m = s;
        }
    }
    
    t_end = time(NULL);
    
    cout << "O(N^3) Algorithm" << endl;
    cout << m << endl;
    cout << t_end - t_start << " seconds" << endl;
    
    // O(N^2) Complexity Algorithm
    
    t_start = time(NULL);
    
    S[0] = 0;
    for (i = 1; i < N; i++) {
        S[i] = S[i-1] + p[i];
    }
    m = 0;
    for (j = 1; j < N; j++) {
        for (k = j; k < N; k++) {
            s = S[k] - S[j-1];
            if (s > m ) m = s;
        }
    }
    
    t_end = time(NULL);
    
    cout << "O(N^2) Algorithm" << endl;
    cout << m << endl;
    cout << t_end - t_start << " seconds" << endl;
    
    // O(N) Complexity Algorithm
    
    t_start = time(NULL);
    
    M[0] = 0;
    for (i = 1; i < N; i++) {
        if (M[i-1] + p[i] >=0) {
            M[i] = M[i-1] + p[i];
        } else {
            M[i] = 0;
        }
    }
    m = 0;
    for (i = 0;i < N ; i++) {
        if (M[i] > m) m = M[i];
    }
    
    t_end = time(NULL);
    
    cout << "O(N) Algorithm" << endl;
    cout << m << endl;
    cout << t_end - t_start << " seconds" << endl;
    
    
    
    return 0;
}
