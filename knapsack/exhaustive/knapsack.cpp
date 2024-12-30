/*
    Project Name: Exhaustive 0/1-Knapsack
    Author: Rocco Catalasan
    Date: 18 November, 2024

    Description & Note:
        The code works, but you gotta manually input the weights.
        The focus of this code is on the logic of the actual knapsack solver function, but
        outputting the results was a total pain... even more so than the knapsack algorithm itself...
        This program operates at O(n * 2^n), but will always produce the optimal solution.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

string knapsackSolve(int, int, vector<int>, vector<int>, int&, int&);
void interpreter(string, int, int, int);
string dec2bin(int);

int main(){
    // <><><><><><> INITIALIZING FIELDS <><><><><><>
    int numObjects = 0;
    int weightMax = 0;
    vector<int> profits;
    vector<int> weights;

    // <><><><><><> POPULATING FIELDS <><><><><><>
    // USE EXAMPLES FROM THE SLIDES TO POPULATE THESE
    // for problem1, use: n = 4, w = 8, p{3,5,2,6}, w{2,4,1,5}

    numObjects = 4;
    weightMax = 8;
    profits.push_back(3);
    profits.push_back(5);
    profits.push_back(2);
    profits.push_back(6);

    weights.push_back(2);
    weights.push_back(4);
    weights.push_back(1);
    weights.push_back(5);

    // <><><><><><> FUNCTIONAL CALLS <><><><><><>

    int totalP = 0, totalW = 0;
    string winningCombo = knapsackSolve(numObjects, weightMax, profits, weights, totalP, totalW);
    interpreter(winningCombo, totalP, totalW, weightMax);

    return 0;
}

string knapsackSolve(int n, int w, vector<int> profits, vector<int> weights, int &totP, int &totW) {
    // *WARNING*: This assumes the input is valid and (hopefully) 1 < n < 32
    int possibleCombos = pow(2,n);          // this is 2 to the power of n; representative of the total number of combinations of taken items
    string controlString, bestString;
    int bestProfit = 0, bestWeight = 0, runningP = 0, runningW = 0;

    for(int i=0; i < possibleCombos; i++) {
        controlString = dec2bin(i);                                         // returns a 32-bit binary word
        controlString = controlString.substr(controlString.length() - n);   // this takes the last 'n' bits of the binary word

        runningP = 0, runningW = 0;

        for(int j=0; j<n; j++) {        // gathering the total of the current combination
            switch(controlString[j]) {  // switch statement used for less comparisons
                case '1':               // no default case since it does nothing regardless if it isn't '1'
                    runningP += profits[j];
                    runningW += weights[j];
                    break;
            }
        }
        if(runningP > bestProfit && runningW <= w) {    // log the best candidate solution
            bestProfit = runningP;
            bestWeight = runningW;
            bestString = controlString;
        }

        // By the end of this loop, bestProfit should have the best profit achievable from the optimal combo.
        // bestString should be holding the optimal combination of items.
    }

    // Giving our main function the best profit and best weight by reference.
    totP = bestProfit;
    totW = bestWeight;

    // TODO: Work on the output
    // If you want the profit of the most profitable combo, return 'bestProfit' and change the function into an int.
    // If you want the most profitable combo, return 'bestString' and change the function into a string one.
    //      (Keep in mind, if you do this, it will return the binary string. You'll still need to interpret it.)
    // Traditionally, you'd want the former, but for the sake of fitting this in a program, I'm doing the latter.

    return bestString;
}

string dec2bin(int input) {
    // Takes given decimal input and converts it to a 32-bit binary word.
    // bitset size has to be constant, so why not the integer limit?
    // This becomes a problem if n > 32
    return bitset<32>(input).to_string();
}

void interpreter(string binCombo, int totalP, int totalW, int w) {
    // Finding out which items were used
    vector<int> usedItemPlaces;
    for(int i=0; i<binCombo.size(); i++) {
        switch(binCombo[i]) {       // switch statement used for less comparisons
            case '1':               // no default case since it does nothing regardless if it isn't '1'
                usedItemPlaces.push_back(i);
                break;
        }
    }

    // Outputting our final answers
    cout << "<><><><> * OPTIMAL SOLUTION * <><><><>" << endl;
    cout << "A total of " << usedItemPlaces.size() << " items were used for a net profit of " << totalP << "." << endl;
    cout << "They are items: ";
    for(int i=0; i<usedItemPlaces.size()-1; i++) {
        cout << usedItemPlaces[i] + 1 << ", ";
    }
    cout << "and " << usedItemPlaces[usedItemPlaces.size()-1] + 1 << "." << endl;
    cout << totalW << "/" << w << " knapsack slots were used." << endl;
    
    return;
}
