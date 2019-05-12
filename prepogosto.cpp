// Naloga:
// https://putka-upm.acm.si/tasks/2016/2016_3kolo/prepogosto

#include <vector>
#include <iostream>
using namespace std;

int main() {
    
    int N, K, X, Y, M, A, B;
    long long S1, S2;
    
    cin >> N >> K >> S1 >> S2 >> X >> Y >> M >> A >> B;
    
    vector<int> stevila(N);
    stevila[0] = S1;
    stevila[1] = S2;
    
    vector<int> ponovitve(M, 0);
    ponovitve[S1]++;
    ponovitve[S2]++;
   
    for (int i=2; i < N; ++i) {
        int S = (S1 * X + S2 * Y) % M;
        S1 = S2;
        S2 = S;
        stevila[i] = S;
        ponovitve[S]++;
    }
    
    int k = 0;
    for (int i=0; i<N; i++) {
        int st = stevila[i];
        if (ponovitve[st] > K) {
            ponovitve[st]--;
        } else {
            if (A-1<= k and k <= B-1) {
                cout << stevila[i] << ' ';
            }
            k++;
        }  
    }
}