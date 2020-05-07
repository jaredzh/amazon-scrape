#include "csvstream.h"
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

class Classifier
{
    public:
    Classifier(string filename_in)
    :filename(filename_in), num_reviews(0){ };

    void process()
    {
        csvstream csv(filename);
        map<string, string> row;
        while(csv >> row)
        {
            string star;
            istringstream source(row["rating"]);
            source >> star;
            if(star == "1.0")
            {
                istringstream content(row["content"] + row["title"]);
                string word;
                while(content >> word)
                {
                    ++one_star_reviews[word];
                }
            }
            if(star == "2.0")
            {
                istringstream content(row["content"] + row["title"]);
                string word;
                while(content >> word)
                {
                    ++two_star_reviews[word];
                }
            }
            if(star == "3.0")
            {
                istringstream content(row["content"] + row["title"]);
                string word;
                while(content >> word)
                {
                    ++three_star_reviews[word];
                }
            }
            if(star == "4.0")
            {
                istringstream content(row["content"] + row["title"]);
                string word;
                while(content >> word)
                {
                    ++four_star_reviews[word];
                }
            }
            if(star == "5.0")
            {
                istringstream content(row["content"] + row["title"]);
                string word;
                while(content >> word)
                {
                    ++five_star_reviews[word];
                }
            }
            ++num_reviews;
        }
    }

    void print_misc_info()
    {

    }

    void one_star_report()
    {
        vector<pair<string, int>> pairs;
    }

    void two_star_report()
    {
        vector<pair<string, int>> pairs;
    }

    void three_star_report()
    {
        vector<pair<string, int>> pairs;
    }

    void four_star_report()
    {
        vector<pair<string, int>> pairs;
    }

    void five_star_report()
    {
        vector<pair<string, int>> pairs;
    }

    // Function tp find the Entry 
    // with largest Value in a Map 
    pair<string, int> findEntryWithLargestValue( 
        map<string, int> sampleMap) 
    { 
  
        // Reference variable to help find 
        // the entry with the highest value 
        pair<string, int> entryWithMaxValue 
            = make_pair("", 0); 
  
        // Iterate in the map to find the required entry 
        map<string, int>::iterator currentEntry; 
        for (currentEntry = sampleMap.begin(); 
            currentEntry != sampleMap.end(); 
            ++currentEntry) { 
  
            // If this entry's value is more 
            // than the max value 
            // Set this entry as the max 
            if (currentEntry->second 
                > entryWithMaxValue.second) { 
  
                entryWithMaxValue 
                    = make_pair( 
                        currentEntry->first, 
                        currentEntry->second); 
            } 
        } 
  
        return entryWithMaxValue;
    } 

    private:
    map<string, int> one_star_reviews;
    map<string, int> two_star_reviews;
    map<string, int> three_star_reviews;
    map<string, int> four_star_reviews;
    map<string, int> five_star_reviews;
    string filename;
    int num_reviews;
};

int main()
{
    cout << "Please enter the name of the Amazon reviews csv spreadsheet that you wish to process: " << endl;
    string filename;
    cin >> filename;
    ifstream file(filename);

    if(!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
    }
    
    Classifier classifier(filename);
    cout << "Processing..." << endl;
    classifier.process();
    cout << "Review reports ready!" << endl;
    return 0;
}