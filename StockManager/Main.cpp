///////////////////////////////////////
// Workfile    : Main.cpp
// Author      : Matthias Schett
// Date        : 27-04-2013
// Description : Stock management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include <vld.h>
#include <iostream>
#include <fstream>
#include "StockMarket.h"
#include <exception>

using namespace std;

int main(){

    size_t const numOfDaysToSimulate = 365;

    ofstream oFile("OutputA1.txt");
    ofstream oFile2("OutputA2.txt");
    try{
        StockMarket market("Wiener Boerse");

        ifstream file("Input.txt");
        market.readStocks(file);

        simulateStockMarket(market, numOfDaysToSimulate);
        oFile << "Table name sorted" << endl;
        market.printStockTable(oFile, 1);
        oFile << endl << endl << endl << "Table highest value sorted" << endl;
        market.printStockTable(oFile, 2);
        oFile << endl << endl << endl << "Table lowest value sorted" << endl;
        market.printStockTable(oFile, 3);
        oFile << endl << endl << endl << "Table highest diff value sorted" << endl;
        market.printStockTable(oFile, 4);

        market.extractAndPrint(oFile2);

        file.close();
    } catch(exception e){
        oFile << e.what();
    }
    oFile.close();
    oFile2.close();

    cin.get();
    return 0;
}