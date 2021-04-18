#include <bits/stdc++.h>
using namespace std;

int main(){
    string line;
    int upper;
    int lower;
    int digit;

    upper = 0;
    lower = 0;
    digit = 0;

    getline(cin, line);

    for (int i = 0; i < line.size(); i++) {
        if(isupper(line[i]))
            upper++;
        if(islower(line[i]))
            lower++;
        if(isdigit(line[i]))
            digit++;
    }

    cout << lower << " " << upper << " " << digit;
    return 0;
}