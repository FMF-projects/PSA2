#include <iostream>
#include <string>

using namespace std;

string uredi(string x) {
    int n = x.size();
    if (n == 1) {
        return x;
    } else {
        int m = n/3;
        string x1 = x.substr(0,m);
        string x2 = x.substr(m,m);
        string x3 = x.substr(2*m,m);

        x1 = uredi(x1);
        x2 = uredi(x2);
        x3 = uredi(x3);

        string s1 = min(x1 + x2 + x3, x1 + x3 + x2);
        string s2 = min(x2 + x1 + x3, x2 + x3 + x1);
        string s3 = min(x3 + x1 + x2, x3 + x2 + x1);

        return min( min(s1, s2), s3);
    }
}

void enaka(string x, string y) {
    if (uredi(x) == uredi(y)) {
        cout << "enaka" << endl;
    } else {
        cout << "razlicna" << endl;
    }
}

int main() {
    int T;
    string niz1;
    string niz2;
    cin >> T;
    string zblj;
    getline (cin, zblj);
    for (int i=0; i<T; i++) {
        getline (cin, niz1);
        getline (cin, niz2);
        enaka(niz1, niz2);
    }
    return 0;
}