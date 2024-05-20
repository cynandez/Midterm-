/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 *Name: Cynthia Hernandez
 *
 * 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void calculateProbability() {
    int trials = 1000000;
    int successes = 0;

    for (int i = 0; i < trials; ++i) {
        int num1 = rand() % 100 + 1;
        int num2 = rand() % 100 + 1;
        int num3 = rand() % 100 + 1;
        int num4 = rand() % 100 + 1;
        int num5 = rand() % 100 + 1;

        if (num1 <= 40 && num2 <= 40 && num3 <= 40 && num4 <= 40 && num5 <= 40) {
            ++successes;
        }
    }

    double probability = static_cast<double>(successes) / trials;
    cout << "Chance of all numbers being within 40%: " << probability << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    calculateProbability();
    return 0;
}

