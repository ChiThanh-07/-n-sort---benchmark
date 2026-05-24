#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;
#define fastio  ios_base::sync_with_stdio(false);cin.tie(NULL);
mt19937 ran_dom(random_device{}());

void generate_int_test_problem_A(int test_number) { // Problem A
    int n = 100000; 
    vector<int> data;
    data.reserve(n);
    uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
    if (test_number == 1) {
        for (int i = 0; i < n; ++i) {
            data.push_back(dist(ran_dom));
        }
    } 
    else if (test_number == 2) {
        for (int i = 0; i < 5; ++i) {
            int random_val = dist(ran_dom);
            for (int j = 0; j < 5000; ++j) {
                data.push_back(random_val);
            }
        }
        int remaining = n - data.size();
        for (int i = 0; i < remaining; ++i) data.push_back(dist(ran_dom));
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 3) {
        vector<int> edge_cases = {INT_MIN, INT_MAX, 0, -1, 1, INT_MAX - 1, INT_MIN + 1};
        for (int i = 0; i < 10000; ++i) {
            for (int val : edge_cases) {
                if (data.size() < n) data.push_back(val);
            }
        }
        while (data.size() < n) data.push_back(dist(ran_dom));
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 4) {
        for (int i = 0; i < n; ++i) data.push_back(dist(ran_dom));
        sort(data.begin(), data.end());
    } 
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) data.push_back(dist(ran_dom));
        sort(data.begin(), data.end(), greater<int>());
    }

    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << data[i] << "\n"; 
    }
}


void generate_string_test_problem_B(int test_number) { // ProblemB
    int n = 100000; 
    vector<string> data;
    data.reserve(n);
    uniform_int_distribution<int> len_dist(10, 100);
    uniform_int_distribution<int> char_dist('a', 'z');
    if (test_number == 1) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
    } 
    else if (test_number == 2) {
        vector<string> pool;
        for(int i = 0; i < 5; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            pool.push_back(s);
        }
        for(int i = 0; i < n; ++i) {
            data.push_back(pool[i % 5]);
        }
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 3) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, 'a'); 
            for (int j = max(0, len - 3); j < len; ++j) {
                s[j] = (char)char_dist(ran_dom);
            }
            data.push_back(s);
        }
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 4) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort(data.begin(), data.end());
    } 
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort(data.begin(), data.end(), greater<string>());
    }
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << data[i] << "\n";
    }
}

void generate_string_test_problem_C(int test_number) { // Problem C
    int n = 10000; 
    vector<string> data;
    data.reserve(n);
    uniform_int_distribution<int> len_dist(10, 100);
    uniform_int_distribution<int> char_dist('a', 'z'); 

    if (test_number == 1) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
    } 
    else if (test_number == 2) {
        vector<string> pool;
        for(int i = 0; i < 5; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            pool.push_back(s);
        }
        for(int i = 0; i < n; ++i) {
            data.push_back(pool[i % 5]);
        }
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 3) {
        for (int i = 0; i < n; ++i) {
            string s(100, 'a'); 
            for (int j = 97; j < 100; ++j) {
                s[j] = (char)char_dist(ran_dom);
            }
            data.push_back(s);
        }
        shuffle(data.begin(), data.end(), ran_dom);
    } 
    else if (test_number == 4) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort(data.begin(), data.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) return a.length() < b.length();
            return a < b;
        });
    } 
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort(data.begin(), data.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) return a.length() > b.length();
            return a > b; 
        });
    }
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << data[i] << "\n";
    }
}
int main(int argc, char* argv[]) {
    fastio;
    if (argc != 3) {
        cerr << "Lỗi : Kích thước argc không hợp lệ \n";
        return 1;
    }
    string problem_type = argv[1];
    int test_number = stoi(argv[2]);

    if (problem_type == "int") {
        generate_int_test_problem_A(test_number);
    } 
    else if (problem_type == "strlexi") {
        generate_string_test_problem_B(test_number);
    } 
    else if (problem_type == "strlenlexi") {
        generate_string_test_problem_C(test_number);
    }
    return 0;
}