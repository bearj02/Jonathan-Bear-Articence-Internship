#include <fstream>
#include <iostream> 
#include <cstdlib> 
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//REQUIRES: A vector of float values
//EFFECTS: returns the median of the vector passed in as a floating point value
float median(vector<float> values){
    size_t size = values.size();
    if (size == 0){
        return 0;  // catch for an undefined vector.
    }
    else{
        sort(values.begin(), values.end());
        if (size % 2 == 0){
            return (values[size / 2 - 1] + values[size / 2]) / 2;
        }
        else {
            return values[size / 2];
        }
    }
}

//REQUIRES: A 2-dimensional vector of strings. This vector stores all the data passed in from the .csv file
//EFFECTS: Iterates through the 2d vector of strings and determines all the types of items that are sold,
// and creates a vector to store each type. Makes a new 2d vector to sort each entry's "Profit as %" and organize it
// by type to correspond to the index of the type in the type vector. Stores the types and the median of each type in 
// a vector of string,float pairs and prints out each pair in a list. Then it finds the item type with the largest median
// profit as % of cost and prints out that item type
void byType(vector<vector<string>> table){
    vector<string> types;
    for(int i = 1; i < (int)table.size(); i++){
        if(find(types.begin(),types.end(),table[i][2]) == types.end()){
            types.push_back(table[i][2]);
        }
    }
    cout << endl;

    vector<vector<float>> sorted_profits;
    sorted_profits.resize(types.size());
    for(int i = 1; i < (int)table.size(); ++i){
        auto it = find(types.begin(),types.end(),table[i][2]);
        int index = (it - types.begin());
        float temp = stof(table[i][15]);
        sorted_profits[index].push_back(temp);
    }
    vector<pair<string,float>> medians;
    vector<string>::iterator it = types.begin();
    while(it != types.end()){
        medians.push_back({*it,median(sorted_profits[it-types.begin()])});
        it++;
    }
    vector<pair<string,float>>::iterator iter = medians.begin();
    while(iter != medians.end()){
        cout << (*iter).first << ": " << (*iter).second * 100 << "%" << endl;
        iter++;
    }

    iter = medians.begin();
    string maxtype = (*iter).first;
    float max = (*iter).second;
    while(iter != medians.end()){
        if((*iter).second > max){
            max = (*iter).second;
            maxtype = (*iter).first;
        }
        iter++;
    }

    cout << endl << "The item type with the largest profitability is " << maxtype << 
        " with a profit of " << max * 100 << "%" << endl;
    
}

//REQUIRES: A 2-dimensional vector of strings. This vector stores all the data passed in from the .csv file
//EFFECTS: Iterates through the 2d vector of strings and determines all the regions where items are sold,
// and creates a vector to store each region. Makes a new 2d vector to sort each entry's "Profit as %" and organize it
// by region to correspond to the index of the region in the regions vector. Stores the regions and the median of each region in 
// a vector of string,float pairs and prints out each pair in a list. Then it finds the region with the largest median
// profit as % of cost and prints out that region
void byRegion(vector<vector<string>> table){
    vector<string> regions;
    for(int i = 1; i < (int)table.size(); i++){
        if(find(regions.begin(),regions.end(),table[i][0]) == regions.end()){
            regions.push_back(table[i][0]);
        }
    }
    cout << endl;

    vector<vector<float>> sorted_profits;
    sorted_profits.resize(regions.size());
    for(int i = 1; i < (int)table.size(); ++i){
        auto it = find(regions.begin(),regions.end(),table[i][0]);
        int index = (it - regions.begin());
        float temp = stof(table[i][15]);
        sorted_profits[index].push_back(temp);
    }
    vector<pair<string,float>> medians;
    vector<string>::iterator it = regions.begin();
    while(it != regions.end()){
        medians.push_back({*it,median(sorted_profits[it-regions.begin()])});
        it++;
    }
    vector<pair<string,float>>::iterator iter = medians.begin();
    while(iter != medians.end()){
        cout << (*iter).first << ": " << (*iter).second * 100 << "%" << endl;
        iter++;
    }

    iter = medians.begin();
    string maxregion = (*iter).first;
    float max = (*iter).second;
    while(iter != medians.end()){
        if((*iter).second > max){
            max = (*iter).second;
            maxregion = (*iter).first;
        }
        iter++;
    }

    cout << endl << "The region with the largest profitability is " << maxregion << 
        " with a profit of " << max * 100 << "%" << endl;
}

int main(int argc, char *argv[]){
    ifstream fin;
    fin.open("Data Science Evaluation.csv", ios::in);
    vector<vector<string>> table;
    vector<string> row;
    string line, word;
  
    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        table.push_back(row);
    }
    
    cout << "Median profit as % of cost by type: " << endl;
    byType(table);
    cout << endl << "Median profit as % of cost by region: " << endl;
    byRegion(table);

}



