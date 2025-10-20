#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Table {
    int rows, cols;
    vector<vector<string>> data;

public:
    Table() : rows(0), cols(0) {}
    Table(int r, int c) : rows(r), cols(c), data(r, vector<string>(c)) {}

    void input() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                cin >> data[i][j];
    }

    void print() const {
        for (auto& row : data) {
            for (auto& val : row)
                cout << val << " ";
            cout << "\n";
        }
    }

    Table sortMerge(const Table& second) const {
        Table merged = *this;

        merged.data.insert(merged.data.end(), second.data.begin(), second.data.end());

        sort(merged.data.begin(), merged.data.end(),
             [](const vector<string>& a, const vector<string>& b) {
                 return a[0] < b[0];
             });

        merged.rows = merged.data.size();
        merged.cols = (merged.rows > 0) ? merged.data[0].size() : 0;
        return merged;
    }
};

int main() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1;
    Table t1(r1, c1);
    t1.input();

    cin >> r2 >> c2;
    Table t2(r2, c2);
    t2.input();

    Table result = t1.sortMerge(t2);
    result.print();

    return 0;
}

