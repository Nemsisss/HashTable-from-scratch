#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>
#include <deque>
using namespace std;

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
        unsigned long long w[5];
        long long unsigned int coeffs[5][6];
        HASH_INDEX_T result=0;
        int ind;
        deque<string> stringDeq; //to be able to push_front in O(1) , since using vector's insert() would be O(n)

        //extract the strings
        for(int i=0; i<= (int)k.length()/6;i++)
        {
            if((int)k.length()- i*6 >=0)
            {
                if((k.substr(k.length()- (i)*6, 6)!=""))
                {
                    stringDeq.push_front(k.substr(k.length()- (i)*6, 6)); //add string only if it's not empty string
                }
                ind=(k.length()- i*6); 
            }
        }
        stringDeq.push_front(k.substr(0, ind));

        //compute the coeffs
        for(long unsigned int i=0; i<stringDeq.size(); i++ )
        {
            int strSize= stringDeq[i].length();
            for(int j=5; j>=0;j--)
            {
                 if(strSize>0)
                 {
                    coeffs[i][j]=  letterDigitToNumber(stringDeq[i][strSize-1]);
                 }
                 else
                 {
                     coeffs[i][j]=0;
                 }
                 strSize--;
            }
        }

        //compute w[i]'s
        for(int i=4; i>=0; i--)
        {
            int factor=1;
            w[i]=0;
            if(!stringDeq.empty())
            {
                long long unsigned int* temp= coeffs[stringDeq.size()-1];
                for(int j=0; j<6;j++) 
                {
                    w[i]+=(long long unsigned int)temp[5-j]* (long long unsigned int)factor;
                    factor=factor * 36;
                }
                stringDeq.pop_back();
            }
        }

        // compute h(k)
        for(int i=0;i<5;i++)
        {
            /* uncomment the following line for debugging */
            // cout<<"W["<<i<<"] = "<<w[i]<<endl;
            result+= (long long unsigned int)w[i]*rValues[i];
        }
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(isalpha(letter))
        {
            return ( ((int)(tolower(letter))) - 97);
        }
        else
        {
            return ((int)letter - 22);
        }
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
