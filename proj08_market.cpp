#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<algorithm>
using std::find;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream; using std::stringstream;
#include<iomanip>
using std::boolalpha; using std::fixed; using std::setprecision;
#include<cassert>
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<string>
using std::string; using std::to_string; using std::getline;
#include<utility>
using std::pair;
#include<fstream> 
using std::ifstream;

#include"proj08_market.h"
//constructor
Market::Market(string file_name){
    string line = "";
    ifstream file(file_name);
    
    while(getline(file, line)){
        vector<double> v;
        stringstream fdata(line);
        long date = 0;
        
        fdata >> date; //the first item in the line is the date

        //loop below adds the market_price to the stocks map
        for(unsigned int i = 0; i < symbol_list.size(); i++){
            double market_price = 0;
            
            fdata >> market_price;
            v.push_back(market_price);
        }
        stocks[date] = v;
    }
}

double Market::get_price(string stock, long date) const{
    double market_price = -1.0;

    //checks to see if the date is valid
    if(stocks.count(date) > 0){
        vector <double> prices = stocks.at(date); //gets vector from date
        auto symbol_index = find(symbol_list.begin(), symbol_list.end(), stock); //finds the symbol
        if(symbol_index != symbol_list.end()){
            market_price = prices[distance(symbol_list.begin(), symbol_index)];
        }
    }
    return market_price;

}


pair<double, double> Market::high_low_year(long year, string symbol){
    bool year_finder = false; //double checks on the year
    pair<double, double> pairs {-1.0, -1.0}; //auto return this
    
    auto finder = find(symbol_list.begin(), symbol_list.end(), symbol); 

    if(finder != symbol_list.end()){
        double max = 0.0;
        double min = 1000.0; //theres no value greater than this
        
        vector<double> prices;
        
        for(auto i=stocks.begin(); i != stocks.end(); ++i){
            if( (i -> first) / 10000 == year){
                //dividing by 10000 gives you the yar
                year_finder = true;
                auto price = i -> second[distance(symbol_list.begin(), finder)];
                prices.push_back(price); //add prices to vector
            }
        }
            
        for(auto &j: prices){
            if(j > max ){
                max = j;
            }
            
            else if(j < min){
                min = j;
            }
        }
        pairs.first = max;
        pairs.second = min;

    }
        
    if(!(year_finder)){
        //if year isnt found then return -1, -1
        pairs.first = -1;
        pairs.second = -1;
    }
    return pairs;
}