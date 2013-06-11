///////////////////////////////////////
// Workfile    : StockMarket.cpp
// Author      : Matthias Schett
// Date        : 27-04-2013
// Description : Stock management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include "StockMarket.h"
#include "scanner.h"
#include "RandomGen.h"
#include <exception>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

// Used to find the longest string for table formatting
struct length {
    bool operator() ( const StockEntry& a, const StockEntry& b ) {
        return a.getStockName().size() < b.getStockName().size();
    }
};

struct NameDescending{
    bool operator() (const StockEntry &a, const StockEntry &b){
        int compare = strcmp(a.getStockName().c_str(), b.getStockName().c_str());

        if(compare == 0){
            return false;
        } else if(compare < 0){
            return true;
        } else if(compare > 0){
            return false;
        }
    }
};

struct HighestActualSharePrice{
    bool operator() (const StockEntry &a, const StockEntry &b){
        return (a.getActualSharePrice() > b.getActualSharePrice());
    }
};

struct HighestTotalSharePrice{
    bool operator() (const StockEntry &a, const StockEntry &b){
        return (a.getHighestSharePrice() > b.getHighestSharePrice());
    }
};

struct HighestDiffSharePrice{
    bool operator() (const StockEntry &a, const StockEntry &b){
        return ( ( a.getHighestSharePrice() - a.getLowestSharePrice() ) > ( b.getHighestSharePrice() - b.getLowestSharePrice() ) );
    }
};

struct NumOfElements{
    bool operator() (const StockEntry &a, const StockEntry &b){
        return (a.getSharePriceCollection().size() > b.getSharePriceCollection().size());
    }
};

bool isTbColon(scanner &scan){
    return scan.symbol_is_colon();
}

bool isTbReal(scanner &scan){
    return scan.symbol_is_real();
}

bool isTbString(scanner &scan){
    return scan.symbol_is_string();
}

bool isTbEof(scanner &scan){
    return scan.symbol_is_eof();
}

string parseStockName(scanner &scan){
    if(isTbString(scan)){
        return scan.get_string();
    }
    throw std::exception("Unknown format");
}

double parseSharePrice(scanner &scan){
    if(isTbReal(scan)){
        return scan.get_real();
    }
    throw std::exception("Unknown format");
}

StockMarket::StockMarket(std::string const &marketName) : mMarketName(marketName), mStocks(){
}

StockMarket::~StockMarket(){
}

StockCollection &StockMarket::getStocks() {
    return mStocks;
}

void StockMarket::readStocks( std::istream &istream ){

    scanner scan(istream);

    while(!scan.symbol_is_eof()){

        if(isTbString(scan)){
            string stockName = parseStockName(scan);
            scan.next_symbol();
            if (!isTbEof(scan)){
                if(isTbColon(scan)){
                    scan.next_symbol();
                    if (!isTbEof(scan)){
                        if(isTbReal(scan)){
                            double actualPrice = parseSharePrice(scan);
                            scan.next_symbol();
                            StockEntry newStock(stockName, actualPrice);
                            addStock(newStock);
                        }
                    }
                }
            }
        } else {
            throw std::exception("Unknown format");
        }
    }

}

void StockMarket::addStock(StockEntry newStock){
    mStocks.push_back(newStock);
}

ostream& hr(std::ostream& os) {
    return os << "--------------------------------------------------------------------";

}

ostream& colSpace(std::ostream& os) {
    return os << setw(colSpacing) << " ";
}

ostream& colFormatStockValues(std::ostream& os) {
    return os << setw(colWidthNum) << right << setiosflags(ios::fixed) << setprecision(precision);
}

size_t StockMarket::findLongestString(){
    StockCollection::iterator it = max_element(getStocks().begin(), getStocks().end(), length());

    return it->getStockName().length();
}

void printTableHeader(std::ostream &os, size_t longestString){
    os << hr << endl;
    os << left << setw(longestString) << "Aktien" <<  colFormatStockValues << "(+/-) Proz" <<  colFormatStockValues << "Aktuell";
    os <<  colFormatStockValues << "Vortag" <<  colFormatStockValues << "Hoch" <<  colFormatStockValues << "Tief";
    os << endl;
    os << hr << endl;
}

void printDataLine(StockEntry const &stock, size_t stringLength, std::ostream &os){
    os << left << setw(stringLength) << stock.getStockName() <<  colFormatStockValues << stock.getStockChangeRate();
    os <<  colFormatStockValues << stock.getActualSharePrice() <<  colFormatStockValues << stock.getDayBeforeSharePrice();
    os <<  colFormatStockValues << stock.getHighestSharePrice() <<  colFormatStockValues << stock.getLowestSharePrice() << endl;
}

void StockMarket::printStockTable( std::ostream &os, int sorting){
    size_t longestString = findLongestString();
    printTableHeader(os, longestString);

    switch(sorting){
    case 1:
        sort(getStocks().begin(), getStocks().end(), NameDescending());
        break;
    case 2:
        sort(getStocks().begin(), getStocks().end(), HighestActualSharePrice());
        break;
    case 3:
        sort(getStocks().begin(), getStocks().end(), HighestTotalSharePrice());
        break;
    case 4:
        sort(getStocks().begin(), getStocks().end(), HighestDiffSharePrice());
        break;
    }

    

    for(StockCollection::iterator it = getStocks().begin(); it < getStocks().end(); ++it){
        printDataLine(*it, longestString, os);
    }
}

StockCollection StockMarket::Extract( StockCollection::iterator begin, StockCollection::iterator end ) {
    StockCollection newCollection;
    vector<double> values;
    for(StockCollection::iterator it = begin; it < end; ++it){
        double startValue = it->getSharePriceCollection().front();
        vector<double> valuesIterator = it->getSharePriceCollection();
        for(vector<double>::iterator it2 =  valuesIterator.begin(); it2 < valuesIterator.end(); ++it2 ){
            if(startValue < *it2){
                values.push_back(*it2);
            }
        }
        if(!values.empty()){
            StockEntry entry(it->getStockName(), values);
            newCollection.push_back(entry);
        }
        values.clear();
    }

    return newCollection;
}

void StockMarket::printExtracted( StockCollection extractedValues, std::ostream &os ) {

    sort(extractedValues.begin(), extractedValues.end(), NumOfElements());

    for(StockCollection::iterator it = extractedValues.begin(); it < extractedValues.end(); ++it){
        os << it->getStockName() << ":\t" << it->getSharePriceCollection().size();
        os << endl;
    }

}

void StockMarket::extractAndPrint( std::ostream &os ) {
    StockCollection col = Extract(getStocks().begin(), getStocks().end());

    printExtracted(col, os);   
}

void simulateStock(StockEntry &stock, size_t numOfDaysToSimulate){
    // With these values the change rate is between -5 and +5 percent
    int changeRateMax = 500;
    int changeRateMin = -500;
    double changeRateDividend = 10000;

    for(size_t day = 0; day < numOfDaysToSimulate; day++){
        double changeRate = (double)rgen::GetRandVal(changeRateMin, changeRateMax) / changeRateDividend; 
        stock.calcNewValuesOnChangeRate(changeRate);
    }

}

void simulateStockMarket( StockMarket &market, size_t numOfDaysToSimulate ){
    rgen::Init();
    for(size_t i = 0; i < market.getStocks().size(); i++){
        simulateStock(market.getStocks().at(i), numOfDaysToSimulate);
    }
}
