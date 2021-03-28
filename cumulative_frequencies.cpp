#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

//vector <pair<string, int>>
void cumulative_word_frequency(vector <pair<string, int>> wf, vector <pair<string, string>> syn)
{

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
    vector <pair<string, int>> wf;
    vector <pair<string, string>> syn;

    // assign list of pairs into wf
    while (getline(infile, line))
    {
        istringstream ss(line);
        string str, num;
        getline(ss >> std::ws, str, ',');
        getline(ss >> std::ws, num, ',');

        wf.push_back(std::make_pair(str, atoi(num.c_str())));
    }
    infile.close();

    // assign list of pairs into syn
    while (getline(infile2, line))
    {
        stringstream ss(line);
        string str1, str2;
        getline(ss >> std::ws, str1, ',');
        getline(ss >> std::ws, str2, ',');

        syn.push_back(std::make_pair(str1, str2));
    }
    infile2.close();

    for (int i = 0; i < syn.size(); i++)
    {
        cout << syn[i].first << ", " << syn[i].second << endl;
    }
    // print list of cumulative frequencies
    // cout << cumulative_word_frequency(wf, syn) << endl;
}