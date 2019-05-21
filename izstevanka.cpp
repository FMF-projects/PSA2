// Naloga:
// https://putka-upm.acm.si/tasks/2014/2014_finale/izstevanka

#include <iostream>
#include <vector>

using namespace std;

int visina_prej = 0;

class node {
  
    public:

    int data;
    int height = 1;
    int elements_left = 0;
    int elements_right = 0;
    int dead = 0;
    node* left;
    node* right;
};

class AVL {

    node* root = NULL;

    vector<int> height(node* t) {
        node* left = t->left;
        node* right = t->right;
        int h_left = 0;
        int h_right = 0;
        vector<int> h(2);

        if (left != 0) {
            h_left = left->height;
        }
        if (right != 0) {
            h_right = right->height;
        }
        h[0] = max(h_left, h_right) + 1;

        // potrebna bo rotacija
        if (abs(h_left - h_right) > 1) {
            h[1] = 1;
        }
    
        return h;
    }

    node* rotate_left(node* t) {
        node* s = t->right;
        
        t->elements_right = s->elements_left;
        s->elements_left = s->elements_left + t->elements_left;
        if (t->dead == 0) {
            s->elements_left++;
        }
   
        t->right = s->left;
        s->left = t;
        
        vector<int> h_t = height(t);
        t->height = h_t[0];
        
        vector<int> h_s = height(s);
        s->height = h_s[0];

        return s;
    }   

    node* rotate_right(node* t) {
        node* s = t->left;

        t->elements_left = s->elements_right;
        s->elements_right = s->elements_right + t->elements_right;
        if (t->dead == 0) {
            s->elements_right++;
        }

        t->left = s->right;
        s->right = t;

        vector<int> h_t = height(t);
        t->height = h_t[0];
        
        vector<int> h_s = height(s);
        s->height = h_s[0];

        return s;
    }  

    node* insert(node* t, int x) {
        if (t == NULL) {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        } else {
            if (x < t->data) {
                t->left = insert(t->left, x);
                t->elements_left++;

                vector<int> h = height(t);
                if (h[1]) {
                    t = rotate_right(t);
                } else {
                    t->height = h[0];
                }

            } else if (x >= t->data) {
                t->right = insert(t->right, x);
                t->elements_right++;

                vector<int> h = height(t);
                if (h[1]) {
                    t = rotate_left(t);
                } else {
                    t->height = h[0];
                }
            }
        }
        return t;
    }

    node* remove(node* t, int k) {
        if(t->elements_left == k-1 && t->dead == 0) {
            cout << t->data << endl;
            visina_prej = t->data;
            t->dead = 1;
        } else {
            if (t->elements_left >= k) {
                t->left = remove(t->left, k);
                t->elements_left--;
            } else {
                k = k - t->elements_left;
                if (t->dead == 0) {
                    k--;
                }
                t->right = remove(t->right, k);
                t->elements_right--;
            }
        }
        return t;
    }

    void print_tree(node* t) {
        if (t == NULL) {
            return;
        }
        print_tree(t->left);
        cout << t->data << " dead " << t->dead << " visina " << t->height //<< endl;
        << " " << t->elements_left << " elementi " << t->elements_right << endl;
        print_tree(t->right);
    }
    
    public:

    void insert(int x) {
        root = insert(root, x);
    }

    void print_tree() {
        print_tree(root);
        cout << endl;
    }

    void remove(int k) {
        root = remove(root, k);
    }
};

int main() {
    int N;
    cin >> N;

    char operacija;
    int x;
    int visina;
    int mod = 1000000001;
    AVL t;

    for (int i=0; i < N; i++) {
        cin >> operacija >> x;
        visina = (x + visina_prej) % mod;
        if (operacija == '+') {
            t.insert(visina);
        } else {
            t.remove(visina);
        }
    }
}