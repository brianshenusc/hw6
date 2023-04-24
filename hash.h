#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned int long long w[5];
        int num;
        if(k.size() == 6 || k.size() < 6) {
            num = 1;
        }
        else {
            num = k.size() / 6 + 1;
        }
        int leading_zeroes = 5 - num;

        int i = 0;
        for(i = 0; i < leading_zeroes; i++) {
            w[i] = 0;
        }
        std::string str = k;
        int index = 4;
        for(int j = 0; j < num; j++) {
            std::string curr_string;
            if(str.size() < 6) {
                while(str.size() < 6) {
                    str.insert(0, "-");
                }
                curr_string = str;
            }
            else {
                curr_string = str.substr(str.size()-6);
            }
            str = str.substr(0, str.size()-6);

            HASH_INDEX_T a[6];
            for(unsigned int m = 0; m < curr_string.size(); m++) {
                if(curr_string[m] == '-') {
                    a[m] = 0;
                }
                else {
                    a[m] = letterDigitToNumber(curr_string[m]);
                }
            }
            w[index] = ((((((a[0]) * 36 + a[1]) * 36 + a[2]) * 36 + a[3]) * 36 + a[4]) * 36 + a[5]);
            index = index - 1;
        }
        HASH_INDEX_T h = (rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4]);
        return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T conv;
        if(isalpha(letter)) {
            letter = tolower(letter);
            conv = int(letter);
            conv -= 97;
        }
        else if(isdigit(letter)) {
            conv = int(letter);
            conv -= 22;
        }
        return conv;


    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
