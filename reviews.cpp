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

void to_lower(string &x);

void remove_special_char(string &s);


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
            istringstream content(row["content"] + row["title"]);
            string word;
            if(star == "1.0")
            {
                while(content >> word)
                {
                    to_lower(word);
                    remove_special_char(word);
                    ++one_star_reviews[word];
                }
                
                total_stars+=1;
            }
            if(star == "2.0")
            {
                while(content >> word)
                {
                    to_lower(word);
                    remove_special_char(word);
                    ++two_star_reviews[word];
                }
                total_stars+=2;
            }
            if(star == "3.0")
            {
                while(content >> word)
                {
                    to_lower(word);
                    remove_special_char(word);
                    ++three_star_reviews[word];
                }
                total_stars+=3;
            }
            if(star == "4.0")
            {
                while(content >> word)
                {
                    to_lower(word);
                    remove_special_char(word);
                    ++four_star_reviews[word];
                }
                total_stars+=4;
            }
            if(star == "5.0")
            {
                while(content >> word)
                {
                    to_lower(word);
                    remove_special_char(word);
                    ++five_star_reviews[word];
                }
                total_stars+=5;
            }
            ++num_reviews;

            istringstream review_date(row["date"]);
            string date;
            string junk;
            string year;
            for(int i = 0; i < 6; ++i)
            {
                review_date >> junk;
            }
            review_date >> date;
            review_date >> junk;
            review_date >> year;
            date = date + " " + year;
            try
            {
                avg_stars_by_date[date].first += stod(star);
            }
            catch(const std::invalid_argument e)
            {
            }
            avg_stars_by_date[date].second += 1;
        }
        for(auto &pair : avg_stars_by_date)
        {
            (pair.second).first /= (pair.second).second;
        }
    }

    void print_misc_info()
    {
        cout << num_reviews << " analyzed" << endl;
        cout << "Average stars: " << total_stars / (double) num_reviews << endl;
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
        cout << "*** One Star Reviews Summary ***" << endl;
        for(pair<string, int> pair : pairs)
        {
            cout << "\"" << pair.first << "\"" << " occurred " << pair.second << " times." << endl;
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
        cout << "*** Two Star Reviews Summary ***" << endl;
        for(pair<string, int> pair : pairs)
        {
            cout << "\"" << pair.first << "\"" << " occurred " << pair.second << " times." << endl;
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
        cout << "*** Three Star Reviews Summary ***" << endl;
        for(pair<string, int> pair : pairs)
        {
            cout << "\"" << pair.first << "\"" << " occurred " << pair.second << " times." << endl;
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
        cout << "*** Four Star Reviews Summary ***" << endl;
        for(pair<string, int> pair : pairs)
        {
            cout << "\"" << pair.first << "\"" << " occurred " << pair.second << " times." << endl;
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
        cout << "*** Five Star Reviews Summary ***" << endl;
        for(pair<string, int> pair : pairs)
        {
            cout << "\"" << pair.first << "\"" << " occurred " << pair.second << " times." << endl;
        }
    }

    private:
    map<string, int> one_star_reviews;
    map<string, int> two_star_reviews;
    map<string, int> three_star_reviews;
    map<string, int> four_star_reviews;
    map<string, int> five_star_reviews;
    map<string, int> one_star_phrases;
    map<string, int> two_star_phrases;
    map<string, int> three_star_phrases;
    map<string, int> four_star_phrases;
    map<string, int> five_star_phrases;
    map<string, pair<double, int>> avg_stars_by_date;
    string filename;
    int num_reviews;
    int total_stars;
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

void to_lower(string &x)
{
    for(int i = 0; i < x.length(); i++)
    {
		if (x[i] > 64 && x[i] < 91){
        x[i] = x[i] + 32;
        }
    }
}

void remove_special_char(string &s)
{
    for (int i = 0; i < s.size(); i++) { 
          
        // Finding the character whose  
        // ASCII value fall under this 
        // range 
        if ((s[i] < 'A' || s[i] > 'Z') && 
            (s[i] < 'a' || s[i] > 'z')) 
        {    
            // erase function to erase  
            // the character 
            s.erase(i, 1);  
            i--; 
        } 
    }
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
        return 1;
    }
    
    Classifier classifier(filename);
    cout << '\n' << "Processing..." << endl;
    classifier.process();

    cout << "Review reports ready!" << endl;
    cout << "Enter 1 for one star review reports" << endl;
    cout << "Enter 12 for one and two star review reports" << endl;
    cout << "Enter 145 for one , four, and five star review reports etc..." << endl;
    
    string choice;
    cin >> choice;

    for(const char& c : choice)
    {
        if(c == '1')
        {
            classifier.one_star_report();
        }
        else if (c == '2')
        {
            classifier.two_star_report();
        }
        else if (c == '3')
        {
            classifier.three_star_report();
        }
        else if (c == '4')
        {
            classifier.four_star_report();
        }
        else if (c == '5')
        {
            classifier.five_star_report();
        }
        else
        {
            cout << "Invalid Input!" << endl;
        }
    }

    cout << '\n' << "Thank you for using the review analysis program!" << endl;
    return 0;
}