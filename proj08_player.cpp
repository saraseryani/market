#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::copy; using std::find;
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

#include"proj08_player.h"

bool Player::buy(Market &m, string stock, long date, long quantity){
    bool return_value = false;
    auto market_price = m.get_price(stock, date); //calculates price
    auto finder = find(m.symbol_list.begin(), m.symbol_list.end(), stock); 
    
    if(cash >= (quantity * market_price)){
        //checks if player has enough money
        if(finder != m.symbol_list.end()){
            //checks if the symbol is valid
            if(m.stocks.count(date) > 0){
                //checks if date is valid
                stocks.insert({stock, quantity});
                cash = cash - (quantity * market_price); //updates account balance
                return return_value = true;
            }
        }
    }
    return return_value;
}

bool Player::sell(Market &m, string stock, long date, long quantity){
    bool return_value = false;
    auto market_price = m.get_price(stock, date);
    auto finder = find(m.symbol_list.begin(), m.symbol_list.end(), stock); 
    auto stock_find = stocks.find(stock);
    
    if(market_price == -1){
        return_value = false;
        return return_value;
    }
    
    if(finder != m.symbol_list.end()){
        //checks if stock is in symbol_list
        if(stock_find != stocks.end()){
            //if player has it
            if(stocks.at(stock) >= quantity){
                //checks if stock is valid
                cash = cash + (quantity * market_price); //updates account balance
                return_value = true;               
            }
        }
    }
    return return_value;      
}


string Player::to_str(){
    ostringstream word;
    setprecision(2);
    word << setprecision(2)<< fixed << cash; //makes it to only 2 decimal places
    
    for(auto i = stocks.begin(); i != stocks.end(); i++){
            word << ",";
            word << i -> first;
            word << ":";
            word << i -> second;
        }
        return word.str();  
  
}


Player Player::combine(Player& b){
    Player p1x;    
    p1x.cash = b.cash + cash; //combies the two accounts
    
    for(auto i: b.stocks){
       p1x.stocks[i.first] = i.second;
    }   
    
    for(auto j: stocks){
       p1x.stocks[j.first] = j.second;
    }
    b.stocks.clear(); //resets players stocks
    stocks.clear();
    b.cash = 0; //resets players cash
    cash =0;

    return p1x;
}
