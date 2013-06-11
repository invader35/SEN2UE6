///////////////////////////////////////
// Workfile    : Stock.cpp
// Author      : Matthias Schett
// Date        : 27-04-2013
// Description : Stock management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include "Stock.h"


Stock::Stock(std::string const &stockName, double actualPrice) : mStockName(stockName), mAcutalSharePrice(actualPrice), mDayBeforeSharePrice(0), 
    mHighestSharePrice(0), mLowestSharePrice(0), mStockChangeRate(0), mSharePriceCollection(1, mAcutalSharePrice) {
}


Stock::Stock(std::string const &stockName, std::vector<double> sharePriceCollection) : mStockName(stockName), mAcutalSharePrice(sharePriceCollection.front()), mDayBeforeSharePrice(0), 
    mHighestSharePrice(0), mLowestSharePrice(0), mStockChangeRate(0), mSharePriceCollection(sharePriceCollection){

}

Stock::~Stock(void)
{
}

// Getters
std::string const &Stock::getStockName() const{
    return mStockName;
}

double Stock::getActualSharePrice() const{
    return mAcutalSharePrice;
}

double Stock::getDayBeforeSharePrice() const{
    return mDayBeforeSharePrice;
}

double Stock::getHighestSharePrice() const{
    return mHighestSharePrice; 
}

double Stock::getLowestSharePrice() const{
    return mLowestSharePrice;
}

double Stock::getStockChangeRate() const{
    return mStockChangeRate;
}

// Setters

void Stock::setStockName(std::string const &stockName){
    mStockName = stockName;
}

void Stock::setActualSharePrice(double actualSharePrice){
    mAcutalSharePrice = actualSharePrice;
}

void Stock::setDayBeforeSharePrice(double dayBeforeSharePrice){
    mDayBeforeSharePrice = dayBeforeSharePrice;
}

void Stock::setHighestSharePrice(double highestSharePrice){
    mHighestSharePrice = highestSharePrice;
}

void Stock::setLowestSharePrice(double lowestSharePrice){
    mLowestSharePrice = lowestSharePrice;
}

void Stock::setStockChangeRate(double stockChangeRate){
    mStockChangeRate = stockChangeRate;
}

void Stock::calcNewValuesOnChangeRate( double changeRate ) {

    setDayBeforeSharePrice(getActualSharePrice());
    setActualSharePrice(getActualSharePrice() + (getActualSharePrice() * changeRate));

    mSharePriceCollection.push_back(getActualSharePrice());

    if(getHighestSharePrice() < getActualSharePrice()){
        setHighestSharePrice(getActualSharePrice());
    }

    if(getLowestSharePrice() > getActualSharePrice() || getLowestSharePrice() == 0){
        setLowestSharePrice(getActualSharePrice());
    }

    setStockChangeRate(getDayBeforeSharePrice() / getActualSharePrice());

}

std::vector<double> Stock::getSharePriceCollection() const {
    return mSharePriceCollection;
}
