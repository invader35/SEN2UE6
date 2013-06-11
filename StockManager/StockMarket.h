///////////////////////////////////////
// Workfile    : StockMarket.h
// Author      : Matthias Schett
// Date        : 27-04-2013
// Description : Stock management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#ifndef STOCKMARKET_H
#define STOCKMARKET_H


#include "Stock.h"
#include <vector>
#include <string>
#include <istream>
#include <ostream>


size_t const colWidthNum = 10;
size_t const precision = 2;
size_t const colSpacing = 4;

// Defines two new types to quickly change implementations
typedef Stock StockEntry;
typedef std::vector<StockEntry> StockCollection;

class StockMarket{

private:
    StockCollection mStocks;
    std::string mMarketName;

    void addStock(Stock newStock);
    
    //************************************
    // Method:    findLongestString
    // FullName:  StockMarket::findLongestString
    // Access:    private 
    // Returns:   size_t
    // Qualifier:
    // Finds the longest string inside stocks
    //************************************
    size_t findLongestString();
public:
    StockMarket(std::string const &marketName);
    ~StockMarket();

    //************************************
    // Method:    getStocks
    // FullName:  StockMarket::getStocks
    // Access:    public 
    // Returns:   StockCollection
    // Qualifier: const
    // Returns the stocks inside the stock market
    //************************************
    StockCollection &getStocks();

    //************************************
    // Method:    readStocks
    // FullName:  StockMarket::readStocks
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::istream & istream
    // Read stocks from a stream and saves them to stocks
    //************************************
    void readStocks(std::istream &istream);

    //************************************
    // Method:    printStockTable
    // FullName:  StockMarket::printStockTable
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::ostream & os
    // Parameter: int sorting
    // Prints a table with information to the stocks
    // 1 - sort alphabet
    // 2 - sort for highest value
    // 3 - sort for lowest value
    // 4 - sort for highest diff
    //************************************
    void printStockTable(std::ostream &os, int sorting);

    //************************************
    // Method:    Extract
    // FullName:  StockMarket::Extract
    // Access:    public 
    // Returns:   StockCollection
    // Qualifier:
    // Parameter: StockCollection::iterator begin
    // Parameter: StockCollection::iterator end
    // Extracts all values from stocks which are greater than the start value
    //************************************
    StockCollection Extract(StockCollection::iterator begin, StockCollection::iterator end);

    //************************************
    // Method:    printExtracted
    // FullName:  StockMarket::printExtracted
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: StockCollection extractedValues
    // Parameter: std::ostream & os
    // Prints the result of extract
    //************************************
    void printExtracted(StockCollection extractedValues, std::ostream &os);

    //************************************
    // Method:    extractAndPrint
    // FullName:  StockMarket::extractAndPrint
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::ostream & os
    // Extracts and prints with one function call
    //************************************
    void extractAndPrint(std::ostream &os);
};

//************************************
// Method:    simulateStockMarket
// FullName:  simulateStockMarket
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: StockMarket market
// Parameter: size_t numOfDaysToSimulate
// Simulates the stock market for the given number of days
//************************************
void simulateStockMarket(StockMarket &market, size_t numOfDaysToSimulate);

#endif