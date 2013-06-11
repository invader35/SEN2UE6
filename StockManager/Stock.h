///////////////////////////////////////
// Workfile    : Stock.h
// Author      : Matthias Schett
// Date        : 27-04-2013
// Description : Stock management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#ifndef STOCK_H
#define STOCK_H


#include <string>
#include <vector>
class Stock {

private:
    std::string mStockName;
    double mAcutalSharePrice;
    double mDayBeforeSharePrice;
    double mHighestSharePrice;
    double mLowestSharePrice;
    double mStockChangeRate;
    std::vector<double> mSharePriceCollection;

public:
    // Ctr
    Stock(std::string const &stockName, double actualPrice);
    // Ctr for Extract Method
    Stock(std::string const &stockName, std::vector<double> sharePriceCollection);
    // Dtr
    ~Stock();

    // Getters
    std::string const &getStockName() const;
    double getActualSharePrice() const;
    double getDayBeforeSharePrice() const;
    double getHighestSharePrice() const;
    double getLowestSharePrice() const;
    double getStockChangeRate() const;
    std::vector<double> getSharePriceCollection() const;

    // Setters
    void setStockName(std::string const &stockName);
    void setActualSharePrice(double actualSharePrice);
    void setDayBeforeSharePrice(double dayBeforeSharePrice);
    void setHighestSharePrice(double highestSharePrice);
    void setLowestSharePrice(double lowestSharePrice);
    void setStockChangeRate(double stockChangeRate);
    
    //************************************
    // Method:    calcNewValuesOnChangeRate
    // FullName:  Stock::calcNewValuesOnChangeRate
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: double changeRate
    // Calculates the new stock values based on the given change rate
    //************************************
    void calcNewValuesOnChangeRate(double changeRate);

};

#endif