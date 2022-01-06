// CSCI 113 Assignment 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//There are 3 function. oneBitAlu, sixTeenAlu(16bitAlu), and boothsMultiplication function.
//sixTeenAlu uses a for loop to loop oneBitAlu 16 times, simulating 16 one bit Alu's
//boothsMultiplication has a for loop that uses the 16 bit Alu function 16 times.
//inside the boothsMultiplication are the output loops
//Also wanted to mention that for the Cycle clock, I simulated doing -1 each iteration by using 4 one bit ALu used the twos complement of 0001 which is 1111

#include <iostream>
#include <vector>
#include<sstream>
using namespace std;


int oneBitALU(int A, int B, int Binvert, int& carryIn, int oP, int& carryOut, int result = 0) {


    if (Binvert == 1) { // Check for B invert. twos complement subtraction
        carryIn = 1;

        if (B == 1) { // invert B
            B = 0;
        }
        else {
            B = 1;
        }

        if (B == A) {

            if (B == 0) { //Both A and B are 0. Adding them will equal 0. Add the carryIn
                result = 1;
                carryOut = 0; // 0 + 0 + 1 = 01. Result is 1, carry out is 0;
            }
            else { // that means A and B are both 1. SO 1 + 1 + 1.

                result = 1;
                carryOut = 1;

            }


        }
        else {
            result = 0; // if they are not equal to, that means A or B is 1. So it will be 1 + 0 + 1 which equals 10. Carry out is 1, result is 0
            carryOut = 1;


        }

       
        return result;


    }




    if (carryIn == 0) { // check carry in before we do addition

        if (A == B) {

            if (A == 0) { // that means they are both 0. 0 + 0

                carryOut = 0;
                result = 0;
            }
            else { // that means they are both 1. 1 + 1
                carryOut = 1;
                result = 0;





            }



        }
        else { // this means they are different. At least A or B is 1.

            carryOut = 0;
            result = 1;


        }

    }
    else if (carryIn == 1) { // Carry in Bit is 1.

        if (B == A) {

            if (B == 0) { //Both A and B are 0. Adding them will equal 0. Add 
                result = 1;
                carryOut = 0; // 0 + 0 + 1 = 01. Result is 1, carry out is 0;
            }
            else { // that means A and B are both 1. SO 1 + 1 + 1;

                result = 1;
                carryOut = 1;

            }


        }
        else {
            result = 0; // if they are not equal to, that means A or B is 1. So it will be 1 + 0 + 1 which equals 10. Carry out is 1, result is 0
            carryOut = 1;


        }




    }

   // cout << carryOut << result << endl;
    return result;

}



vector<int> sixTeenAlu(vector<int> a, vector<int> b, int Binvert, int oP) {

    int carryIn = 0;
    int carryOut = 0;

    
    vector<int> result1(16);
    if (Binvert == 0) {

        for (int i = 15; i >= 0; --i) { // 16, 1 bit alu's

            carryIn = carryOut;
            int result2 = oneBitALU(a[i], b[i], Binvert, carryIn, 10, carryOut);

            result1[i] = result2;





        }


    }
    else if(Binvert == 1) {

        for (int i = 0; i < 16; ++i) { // flip the bits

            if (b[i] == 0) {
                b[i] = 1;
            }
            else{
                b[i] = 0;
            }

        }

        carryOut = 1; // just to make carryIn = 1 in the loop since we need to add 1 after we flip the bits

        for (int i = 15; i >= 0; --i) { // 16, 1 bit alu's

            carryIn = carryOut;
            int result2 = oneBitALU(a[i], b[i], 0, carryIn, 10, carryOut); // don't need B invert in the 1 bit alu since we already flipped the bits

            result1[i] = result2;





        }





    }
    







    return result1;



}


vector<int> boothsMultiplication(vector<int> MD, vector<int> MQ) {


    vector<int> cycleCounter{ 1, 1, 1, 1 };
    vector<int>AC{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vector<int>MD1 = MD;
    vector<int>MQ1 = MQ;
    vector<int>Zero{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>product(32);
    int MQminus1 = 0;
    cout << "Cycle Counter          " << "MD                       " << "AC                    " << " MQ                   " << "MQ-1" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
    cout << "  ";
    for (int i = 0; i < 4; ++i) {
        cout << cycleCounter[i];


    }
    cout << "           ";
    for (int i = 0; i < 16; ++i) {

        cout << MD1[i];

    }
    
    cout << "       ";

    for (int i = 0; i < 16; ++i) {

        cout << AC[i];

    }
    cout << "          ";
    for (int i = 0; i < 16; ++i) {

        cout << MQ1[i];

    }

    cout << "           ";

    cout << MQminus1;



    cout << endl;


    for (int i = 0; i < 16; ++i) {

        if (MQ1[15] == 0 && MQminus1 == 0) {

            AC = sixTeenAlu(AC, Zero, 0, 10);

        }
        else if (MQ1[MQ1.size() - 1] == 0 && MQminus1 == 1) {
           

            





            AC = sixTeenAlu(AC, MD1, 0, 10); //Binvert = 0

            
            

        }
        else if (MQ1[MQ1.size() - 1] == 1 && MQminus1 == 0) {

            AC = sixTeenAlu(AC, MD1, 1, 10); //Binvert = 1
        }
        else if (MQ1[MQ1.size() - 1] == 1 && MQminus1 == 1) {
            AC = sixTeenAlu(AC, Zero, 0, 10);
        }
        cout << "  ";
        for (int i = 0; i < 4; ++i) {
            cout << cycleCounter[i];


        }
        cout << "           ";
        for (int i = 0; i < 16; ++i) {

            cout << MD1[i];

        }

        cout << "       ";

        for (int i = 0; i < 16; ++i) {

            cout << AC[i];

        }
        cout << "          ";
        for (int i = 0; i < 16; ++i) {

            cout << MQ1[i];

        }

        cout << "           ";

        cout << MQminus1;



        cout << endl;






        //display contents

        MQminus1 = MQ1[MQ1.size() - 1];
       
        vector<int> MQ2 = MQ1;
        for (int i = 0; i < 15; ++i) { //shift right
            MQ1[i + 1] = MQ2[i];
        }
        MQ1[0] = AC[AC.size() - 1];

        vector<int> AC1 = AC;
        for (int i = 1; i < 15; ++i) { //shift right
            AC[i + 1] = AC1[i];
        }
        cout << "  ";
        for (int i = 0; i < 4; ++i) {
            cout << cycleCounter[i];


        }
        cout << "           ";
        for (int i = 0; i < 16; ++i) {

            cout << MD1[i];

        }

        cout << "       ";

        for (int i = 0; i < 16; ++i) {

            cout << AC[i];

        }
        cout << "          ";
        for (int i = 0; i < 16; ++i) {

            cout << MQ1[i];

        }

        cout << "           ";

        cout << MQminus1;



        cout << endl;

        cout << endl;

        
        int carryIn = 0;
        int carryOut = 0;
        vector<int> minusOne{ 1,1,1,1 }; // 2s complement 1. Use 4 ALU so modify cycleCounter
        cycleCounter[3] = oneBitALU(cycleCounter[3], minusOne[3], 0, carryIn, 10, carryOut);
        carryIn = carryOut;
        carryOut = 0;
        cycleCounter[2] = oneBitALU(cycleCounter[2], minusOne[2], 0, carryIn, 10, carryOut);
        carryIn = carryOut;
        carryOut = 0;
        cycleCounter[1] = oneBitALU(cycleCounter[1], minusOne[1], 0, carryIn, 10, carryOut);
        carryIn = carryOut;
        carryOut = 0;
        cycleCounter[0] = oneBitALU(cycleCounter[0], minusOne[0], 0, carryIn, 10, carryOut);
    }

    for (int i = 0; i < 32; ++i) {
        if (i < 16) {
            product[i] = AC[i];
        }
        else {
            product[i] = MQ1[i-16];
        }

    }

    return product;

}


int main()
{

    

    string MD1;
    vector<int>MD;
    cout << "Please enter a MD(multiplicant)-- Press enter when done :";
    getline(cin, MD1);
    for (int i = 0; i < 16; ++i) {
        MD.push_back(MD1[i] - '0');

    }


    string MQ1;
    vector<int> MQ;
    cout << "Please enter a MQ(multiplyer)-- Press enter when done :";
    getline(cin, MQ1);
    for (int i = 0; i < 16; ++i) {
        MQ.push_back(MQ1[i] - '0');
    }



    cout << endl;
   
 

    

    
    
    vector<int> result = boothsMultiplication(MD, MQ);

    

   

    cout << "Product is: ";
    for (int i = 0; i < result.size(); ++i) {

        cout << result[i];


    }
    





}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
