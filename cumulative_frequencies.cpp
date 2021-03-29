#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <iterator>

using namespace std;

typedef pair<string, int> si_pair;
typedef pair<string, string> str_pair;

// 
struct pair_equal: unary_function<str_pair, bool>
{
    pair_equal(const string &idx): idx_(idx) {}
    
    bool operator() (const str_pair &arg) const 
    {
        return (arg.first == idx_) || (arg.second == idx_);
    }
    
    const string &idx_;
};

set<string> combine_unique_strs(set<str_pair> &syn)
{
    vector<string> str_set;
    str_set.push_back((*(syn.begin())).first);
    str_set.push_back((*(syn.begin())).second);
    
    int idxcount = 2;
    int currentidx = 0;

    set<str_pair>::const_iterator it;
    while (currentidx < idxcount)
    {
        while( (it = find_if(syn.begin(), syn.end(), pair_equal(str_set[currentidx]))) != syn.end() ) 
        {
            // found next string connected to str_set
            string new_str = (str_set[currentidx] == (*it).first ? (*it).second : (*it).first);
            // if string is not already present, insert it into components
            if (find(str_set.begin(), str_set.end(), new_str) == str_set.end())
            {
                str_set.push_back(new_str);
                idxcount++;
            }
            syn.erase(it);
        }
        currentidx++;
    }
    return set<string>(str_set.begin(), str_set.end());
}

set<si_pair> cumulative_word_frequency(map<string, int> wf, set<str_pair> syn)
{
    vector<set<string>> common_words;
    // Merge pairs with common elements together
    while (!syn.empty())
    {
        set<string> words = combine_unique_strs(syn);
        common_words.push_back(words);
    }

    // Create set of cumulative frequency pairs 
    set<si_pair> cf;
    for (set<string> &words : common_words)
    {
        int sum = 0;
        // Calculate sum of frequencies in each set
        for (string s : words)
        {
            sum += wf[s];
        }
        // Push in pair with first element of each set and its calculated sum 
        cf.insert(make_pair((*words.begin()), sum));
    }

    return cf;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " filename_wf.txt filename_syn.txt" << endl;
        return EXIT_FAILURE;
    }

    ifstream infile(argv[1]);   // file containing list of word frequencies
    ifstream infile2(argv[2]);  // file containing list of pair synonyms

    // failed to open file
    if (infile.fail())
    {
        cout << "Unable to open " << argv[1] << endl;
        return 1;
    }
    if (infile2.fail())
    {
        cout << "Unable to open " << argv[2] << endl;
        return 1;
    }

    string line;
    map<string, int> wf;
    // set<si_pair> wf;
    set<str_pair> syn;

    // assign list of pairs into wf
    while (getline(infile, line))
    {
        istringstream ss(line);
        string str, num;
        getline(ss >> std::ws, str, ',');
        getline(ss >> std::ws, num, ',');

        wf.insert(make_pair(str, atoi(num.c_str())));
    }
    infile.close();

    // assign list of pairs into syn
    while (getline(infile2, line))
    {
        stringstream ss(line);
        string str1, str2;
        getline(ss >> std::ws, str1, ',');
        getline(ss >> std::ws, str2, ',');

        syn.insert(make_pair(str1, str2));
    }
    infile2.close();

    // print list of cumulative frequencies
    set<si_pair> cf = cumulative_word_frequency(wf, syn);
    // for ()
}