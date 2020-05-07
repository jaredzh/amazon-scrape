#include "csvstream.h"
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

static pair<string, int> findEntryWithLargestValue( 
    map<string, int> sampleMap);
static void remove_common_words(map<string, int> &map_in);


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
        remove_common_words(one_star_reviews);
        while(!one_star_reviews.empty())
        {
            pair<string, int> temp = findEntryWithLargestValue(one_star_reviews);
            pairs.push_back(temp);
            one_star_reviews.erase(temp.first);
        }
    }

    void two_star_report()
    {
        vector<pair<string, int>> pairs;
        remove_common_words(two_star_reviews);
        while(!two_star_reviews.empty())
        {
            pair<string, int> temp = findEntryWithLargestValue(two_star_reviews);
            pairs.push_back(temp);
            two_star_reviews.erase(temp.first);
        }
    }

    void three_star_report()
    {
        vector<pair<string, int>> pairs;
        remove_common_words(three_star_reviews);
        while(!three_star_reviews.empty())
        {
            pair<string, int> temp = findEntryWithLargestValue(three_star_reviews);
            pairs.push_back(temp);
            three_star_reviews.erase(temp.first);
        }
    }

    void four_star_report()
    {
        vector<pair<string, int>> pairs;
        remove_common_words(four_star_reviews);
        while(!four_star_reviews.empty())
        {
            pair<string, int> temp = findEntryWithLargestValue(four_star_reviews);
            pairs.push_back(temp);
            four_star_reviews.erase(temp.first);
        }
    }

    void five_star_report()
    {
        vector<pair<string, int>> pairs;
        remove_common_words(five_star_reviews);
        while(!five_star_reviews.empty())
        {
            pair<string, int> temp = findEntryWithLargestValue(five_star_reviews);
            pairs.push_back(temp);
            five_star_reviews.erase(temp.first);
        }
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

// Function tp find the Entry 
// with largest Value in a Map 
static pair<string, int> findEntryWithLargestValue( 
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

static void remove_common_words(map<string, int> &map_in) 
{
    ifstream in_file("common_words.txt");
    if(!in_file.is_open())
        cout << "Error opening common words text file" << endl;
    string word;
    while(in_file >> word)
        map_in.erase(word);
}

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
    cout << "Enter 0 for overview of data" << endl;
    cout << "Enter 1 for one star review reports" << endl;
    cout << "Enter 2 for two star review reports" << endl;
    cout << "Enter 3 for three star review reports" << endl;
    cout << "Enter 4 for four star review reports" << endl;
    cout << "Enter 5 for five star review reports" << endl;
    cout << "Enter -1 to quit program" << endl;
    int choice;
    cin >> choice;

    if(choice == 0)
    {
        classifier.print_misc_info();
    }
    else if(choice == 1)
    {
        classifier.one_star_report();
    }
    else if(choice == 2)
    {
        classifier.one_star_report();
    }
    else if(choice == 3)
    {
        classifier.one_star_report();
    }
    else if(choice == 4)
    {
        classifier.one_star_report();
    }
    else if(choice == 5)
    {
        classifier.one_star_report();
    }
    else
    {
        cout << "Invalid Input" << endl;
    }
    

    return 0;
}