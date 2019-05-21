#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <fstream>

using namespace std;

/// (relativno slaba) implementacija Pythonove `set` strukture v C++.
template <typename T>
class HashSet {
    int bucket_count_;
    int num_elements_;
    vector< vector<T> > buckets_;

    hash<T> hash_function;  /// c++-ova hash funkcija, ki T spremeni v število (ponavadi zelo veliko)
  
    int hash_(const T& item) const { // prvi const ne spreminja item, drugi pa zunanjega stanja
        return hash_function(item) % bucket_count_;
    }
  
  public:

    /// Naredi Hash tabelo z danim številom veder
    HashSet(int bucket_count):
    bucket_count_(bucket_count), num_elements_(0),
    buckets_(bucket_count), hash_function() {}


    /// Doda element. Vrne `false` in ne naredi nič, če že obstaja
    bool add(const T& item) {
        int index = hash_(item);
        auto it = std::find(buckets_[index].begin(),buckets_[index].end(),item);
        if (it != buckets_[index].end()) {
            return false;
        } else {
            buckets_[index].push_back(item);
            ++num_elements_;
            return true;
        }
    }

    /// Vrne true ali false, glede na to ali element obstaja
    bool find(const T& item) const {
        int index = hash_(item);
        vector<T> bucket = buckets_[index];
        for (int i=0; i < bucket.size(); i++) {
            if (bucket[i] == item) {
                return true;
            }
        }
        return false;
    }

    /// Če obstaja, odstrani element in vrne true
    bool remove(const T& item) {
        int index = hash_(item);
        vector<T> bucket = buckets_[index];
        for (int i=0; i < bucket.size(); i++) {
            if (bucket[i] == item) {
                bucket.erase(bucket.begin() + i);
                return true;
            }
        }  
    }

    /// Odstrani in vrne nek element iz tabele (predpostavimo, da ni prazna)
    T pop() {
        for (int i=0; i < buckets_.size(); i++) {
            vector<T> bucket = buckets_[i];
            if (bucket.size() > 0) {
                return bucket[0];
            }
        }
    }

    /// Število elementov v množici
    int size() const {
        int counter = 0;
        for (int i=0; i < buckets_.size(); i++) {
            vector<T> bucket = buckets_[i];
            counter = counter + bucket.size();
        }
        return counter;
    }

    /// Ali je prazna?
    bool empty() const {
        return num_elements_ == 0;
    }

    /// Lep izpis
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const HashSet<U>& s) {
        if (s.empty()) {
            return os << "{}";
        } else {
            os << "{";
            bool first = true;        
            for (const vector<U> bucket : s.buckets_) {
                for (const U& e: bucket){
                    if (!first) os << ", ";
                    first = false;
                    os << e;
                }
            }
            return os << "}";
        }
    }
};

int main() {
    cout << boolalpha;

    HashSet<string> s(5);
    cout << s.add("abc") << endl;
    cout << s.add("ab") << endl;
    cout << s.add("abc") << endl;
    cout << s.add("hg") << endl;
    cout << s << endl;
    cout << s.find("abc") << endl;
    cout << s.remove("abc") << endl;
    cout << s.find("abc") << endl;
    cout << s.remove("ab") << endl;
    cout << s.remove("hg") << endl;
    cout << s << endl;

    HashSet<string> words(1e5);
    int cnt = 0;
    string word;

    ifstream file("crap.txt");
    file >> word;
    while (file) {
        words.add(word);
        ++cnt;
        file >> word;
    }
    cout << words.size() << " / " << cnt << endl;

    return 0;
}
