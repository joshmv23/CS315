#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
unordered_set<string> dict; // Global dictionary set
bool if_word_in_dict(const string& word) {
    return dict.count(word) > 0;
}
bool split(const string& str) {
    int n = str.length();
    vector<bool> dp(n + 1, false); //dp array
    dp[n] = true; // Base case
    for (int i = n - 1; i >= 0; i--) {//recursively loop
        string word;
        for (int j = i; j < n; j++) {
            word += str[j];
            if (if_word_in_dict(word) && dp[j + 1]) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[0];
}
//form sentence for output
void printStr(const string& str) {
    int n = str.length();
    vector<string> retStr;//return string holder
    string word;
    for (int i = 0; i < n; i++) {
        word += str[i];
        if (if_word_in_dict(word) && split(str.substr(i + 1))) {
            retStr.push_back(word);
            word.clear();
        }
    }
    for (const string& inStr : retStr) {
        cout << inStr << " ";
    }
    cout << endl;
}
int main() {
    ifstream dictionaryFile("diction10k.txt");//open dict file
    if (!dictionaryFile) { //error checking
        cerr << "Error: Could not open dictionary file." << endl;
        return 1;
    }
    // Load dictionary words into the set
    string word;
    while (dictionaryFile >> word) {
        dict.insert(word); //store words into set
    }
    dictionaryFile.close();//close file
    int num;
    cin >> num;
    for (int i = 1; i <= num; i++) {
        string sentence;
        cin >> sentence;
        cout << "phrase " << i << endl;
        cout << sentence << endl;
        cout << "output " << i << endl;
        if (split(sentence)) {
            cout << "YES, can split." << endl;
            printStr(sentence);
        } else {
            cout << "NO, cannot split." << endl;
        }
        cout << endl;
    }
    return 0;
}
