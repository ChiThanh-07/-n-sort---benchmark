#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
mt19937 ran_dom(random_device{}());


void merge_A(vector<int>& arr, int left, int mid, int right, bool ascending) { // Logic merge sort cho bài A    
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool condition = ascending ? (L[i] <= R[j]) : (L[i] >= R[j]);
        if (condition) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort_A(vector<int>& arr, int left, int right, bool ascending) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_A(arr, left, mid, ascending);
    merge_sort_A(arr, mid + 1, right, ascending);
    merge_A(arr, left, mid, right, ascending);
}

void sort_A(vector<int>& arr, bool ascending) {
    if (arr.empty()) return;
    merge_sort_A(arr, 0, arr.size() - 1, ascending);
}


void merge_B(vector<string>& arr, int left, int mid, int right, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<string> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool condition = ascending ? (L[i] <= R[j]) : (L[i] >= R[j]);
        if (condition) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort_B(vector<string>& arr, int left, int right, bool ascending) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_B(arr, left, mid, ascending);
    merge_sort_B(arr, mid + 1, right, ascending);
    merge_B(arr, left, mid, right, ascending);
}

void sort_B(vector<string>& arr, bool ascending) {
    if (arr.empty()) return;
    merge_sort_B(arr, 0, arr.size() - 1, ascending);
}

bool compare_C(const string& a, const string& b, bool ascending) {
    if (ascending) {
        if (a.length() != b.length()) return a.length() < b.length();
        return a < b;
    }
    else {
        if (a.length() != b.length()) return a.length() > b.length();
        return a > b;
    }
}

void merge_C(vector<string>& arr, int left, int mid, int right, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<string> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare_C(L[i], R[j], ascending)) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort_C(vector<string>& arr, int left, int right, bool ascending) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_C(arr, left, mid, ascending);
    merge_sort_C(arr, mid + 1, right, ascending);
    merge_C(arr, left, mid, right, ascending);
}

void sort_C(vector<string>& arr, bool ascending) {
    if (arr.empty()) return;
    merge_sort_C(arr, 0, arr.size() - 1, ascending);
}

void generate_int_test_problem_A(int test_number) {
    int n = 100000;
    vector<int> data;
    data.reserve(n);
    uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    if (test_number == 1) {
        for (int i = 0; i < n; ++i) data.push_back(dist(ran_dom));
    }
    else if (test_number == 2) {
        for (int i = 0; i < 5; ++i) {
            int random_val = dist(ran_dom);
            for (int j = 0; j < 5000; ++j) data.push_back(random_val);
        }
        int remaining = n - data.size();
        for (int i = 0; i < remaining; ++i) data.push_back(dist(ran_dom));
        shuffle(data.begin(), data.end(), ran_dom);
    }
    else if (test_number == 3) {
        vector<int> edge_cases = { INT_MIN, INT_MAX, 0, -1, 1, INT_MAX - 1, INT_MIN + 1 };
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
        sort_A(data, true); 
    }
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) data.push_back(dist(ran_dom));
        sort_A(data, false); 
    }

    cout << n << "\n";
    for (int i = 0; i < n; ++i) cout << data[i] << "\n";
}

void generate_string_test_problem_B(int test_number) {
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
        for (int i = 0; i < 5; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            pool.push_back(s);
        }
        for (int i = 0; i < n; ++i) data.push_back(pool[i % 5]);
        shuffle(data.begin(), data.end(), ran_dom);
    }
    else if (test_number == 3) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, 'a');
            for (int j = max(0, len - 3); j < len; ++j) s[j] = (char)char_dist(ran_dom);
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
        sort_B(data, true); //sort từ điển tăng dần
    }
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort_B(data, false); // sort từ điển giảm dần
    }

    cout << n << "\n";
    for (int i = 0; i < n; ++i) cout << data[i] << "\n";
}

void generate_string_test_problem_C(int test_number) {
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
        for (int i = 0; i < 5; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            pool.push_back(s);
        }
        for (int i = 0; i < n; ++i) data.push_back(pool[i % 5]);
        shuffle(data.begin(), data.end(), ran_dom);
    }
    else if (test_number == 3) {
        for (int i = 0; i < n; ++i) {
            string s(100, 'a');
            for (int j = 97; j < 100; ++j) s[j] = (char)char_dist(ran_dom);
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
        sort_C(data, true); 
    }
    else if (test_number == 5) {
        for (int i = 0; i < n; ++i) {
            int len = len_dist(ran_dom);
            string s(len, ' ');
            for (int j = 0; j < len; ++j) s[j] = (char)char_dist(ran_dom);
            data.push_back(s);
        }
        sort_C(data, false); 
    }

    cout << n << "\n";
    for (int i = 0; i < n; ++i) cout << data[i] << "\n";
}

int main(int argc, char* argv[]) {
    fastio;
    if (argc != 3) {
        cerr << "Loi : argc khong hop le \n";
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
