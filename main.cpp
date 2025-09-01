#include <bits/stdc++.h>
using namespace std;

// Convert string of given base to decimal
long long toDecimal(const string &val, int base) {
    long long res = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = 10 + (tolower(c) - 'a');
        res = res * base + digit;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int n = 0, k = 0;
    vector<long long> roots;

    // Read whole JSON input
    while (getline(cin, line)) {
        // Remove spaces and commas
        line.erase(remove_if(line.begin(), line.end(), [](char c) {
            return c == ' ' || c == ','; 
        }), line.end());

        // Find n
        if (line.find("\"n\":") != string::npos) {
            n = stoi(line.substr(line.find(":") + 1));
        }

        // Find k
        else if (line.find("\"k\":") != string::npos) {
            k = stoi(line.substr(line.find(":") + 1));
        }

        // Find base
        else if (line.find("\"base\"") != string::npos) {
            int base = stoi(line.substr(line.find(":") + 2, line.size() - 3));

            // Read next line for value
            string valLine;
            getline(cin, valLine);
            valLine.erase(remove_if(valLine.begin(), valLine.end(), [](char c) {
                return c == ' ' || c == ','; 
            }), valLine.end());

            string value = valLine.substr(valLine.find(":") + 2);
            if (!value.empty() && value.back() == '"') value.pop_back();
            if (!value.empty() && value.front() == '"') value.erase(value.begin());

            long long root = toDecimal(value, base);
            roots.push_back(root);
        }
    }

    // Use only first k roots
    if ((int)roots.size() > k) roots.resize(k);

    // Construct polynomial coefficients
    vector<long long> coeff = {1}; // P(x) = 1 initially
    for (long long r : roots) {
        vector<long long> newCoeff(coeff.size() + 1, 0);
        for (size_t i = 0; i < coeff.size(); i++) {
            newCoeff[i] += -r * coeff[i];
            newCoeff[i + 1] += coeff[i];
        }
        coeff = newCoeff;
    }

    // Print output
    cout << "Polynomial Coefficients:\n";
    for (long long c : coeff) cout << c << " ";
    cout << "\n";

    return 0;
}