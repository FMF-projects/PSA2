// Naloga:
// https://putka-upm.acm.si/tasks/2013/2013_finale/safety

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class node {
  
    public:

    int a;
    int b;
    int D = 0;
    node* left;
    node* right;
};

class BST {
    
    node* root = NULL;

    node* insert(node* t, int x, int y) {
        if (x == y) {
            t = new node;
            t->a = t->b = x;
            t->left = t->right = NULL;
        } else {
            int s = (x + y) / 2;
            t = new node;
            t->a = x;
            t->b = y;
            t->left = insert(t->left, x, s);
            t->right = insert(t->right, s+1, y);
        }
        return t;
    }

    void print_tree(node* t) {
        if (t == NULL) {
            return;
        }
        print_tree(t->left);
        cout << t->a << " " << t->b << " " << t->D << " ";
        print_tree(t->right);
    }

    int delavci(node* t, int x, int vsota) {
        if (t->a == t->b && t->a == x) {
           vsota = vsota + t->D;
           return vsota; 
        } else {
            vsota = vsota + t->D;
            node* levo = t->left;
            node* desno = t->right;
            if (levo->b >= x && levo != 0) {
                vsota = delavci(levo, x, vsota);
            } else if (desno->a <= x && desno != 0) {
                vsota = delavci(desno, x, vsota);
            }
        }
    }

    void popravi(node* t, int x, int y, int sprememba) {
        if (t->b < x || t->a > y) {

        } else if (t->a >= x && t->b <= y) {
            int d = t->D;
            t->D = d + sprememba;
        } else {
            if (t->right != 0) {
                popravi(t->right, x, y, sprememba);
            }
            if (t->left != 0) {
                popravi(t->left, x, y, sprememba);
            }
        }
    }

    public:

    void print_tree() {
        print_tree(root);
        cout << endl;
    }

    void insert(int x, int y) {
        root = insert(root, x, y);
    }

    void delavci(int x) {
        int vsota = delavci(root, x, 0);
        cout << vsota << endl;
    }

    void izmena(int x, int y, int sprememba) {
        popravi(root->left, x, y, sprememba);
        popravi(root->right, x, y, sprememba);
    }
};

int main() {

    int D, P;
    cin >> D >> P;
    vector< vector<int> > operacije(2*D + P);
    set<int> krajisca;
    vector<int> delavci(P,0);

    // preberemo zacetke in konce izmen
    for(int i=0; i < D; i++) {
        int Z, K, A, B;
        cin >> Z >> K >> A >> B;
        int k = 2*i;
        operacije[k] = vector<int> {Z, 0, A, B};
        operacije[k+1] = vector<int> {K, 2, A, B};
        krajisca.insert(A);
        krajisca.insert(B);
    }   


    // preberemo preglede inspektorjev
    for(int i=0; i < P; i++) {
        int T, X;
        cin >> T >> X;
        int k = 2*D + i;
        operacije[k] = vector<int> {T, 1, i, X};
        krajisca.insert(X);
    }

    int N = krajisca.size();
    map<int, int> kraj;
    int i = 0;
    for (const int &number : krajisca) {
        kraj.insert({number,i});
        i++;
    }

    // uredimo po casu narascajoce
    sort(operacije.begin(), operacije.end()); 

    // zgradimo drevo
    BST t;
    t.insert(0, N);

    // povecamo, zmanjsamo ali izpisemo st delavcev na odsekih
    for (int i=0; i < 2*D + P; i++) {
        vector<int> op = operacije[i];
        if (op[1] == 0) {
            int x = kraj[op[2]];
            int y = kraj[op[3]];
            t.izmena(x, y, 1);
        } else if (op[1] == 1) {
            int x = kraj[op[3]];
            t.delavci(x);
        } else {
            int x = kraj[op[2]];
            int y = kraj[op[3]];
            t.izmena(x, y, -1);
        }
    }
}
