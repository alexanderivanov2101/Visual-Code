#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Spreadsheet {
public:
    int R = 0, C = 0;
    vector<double> data; // row-major, size = R*C

    void load(istream& in) {
        in >> R >> C;
        data.resize(R * C);
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                in >> data[r * C + c];
            }
        }
    }

    double at(int r, int c) const {
        return data[r * C + c];
    }
};

class SpreadsheetView {
public:
    const Spreadsheet* s = nullptr;
    vector<int> rows; // indices into s->rows

    SpreadsheetView(const Spreadsheet& S) {
        s = &S;
        rows.resize(s->R);
        for (int i = 0; i < s->R; ++i) {
            rows[i] = i; // identity mapping initially
        }
    }

    void sortBy(int col) {
        std::stable_sort(rows.begin(), rows.end(),
            [&](int a, int b) {
                return s->at(a, col) < s->at(b, col);
            });
    }

    void filter(int col, std::string op, double val) {
        vector<int> filtered;
        for (int r : rows) {
            double cell = s->at(r, col);
            bool keep = false;
            if (op == "EQ")  keep = (cell == val);
            else if (op == "GEQ") keep = (cell >= val);
            else if (op == "LEQ") keep = (cell <= val);
            else if (op == "G")   keep = (cell > val);
            else if (op == "L")   keep = (cell < val);
            if (keep) filtered.push_back(r);
        }
        rows.swap(filtered);
    }

    void print() {
        for (int r : rows) {
            for (int c = 0; c < s->C; ++c) {
                if (c) cout << ' ';
                cout << s->at(r, c);
            }
            cout << '\n';
        }
    }
};

int main() {
    Spreadsheet S;
    S.load(cin);
    int K;
    cin >> K;
    SpreadsheetView V(S);
    for (int i = 0; i < K; ++i) {
        char op;
        cin >> op;
        if (op == 'S') {
            int col; cin >> col;
            V.sortBy(col);
        } else if (op == 'F') {
            int col; string cmp; double val;
            cin >> col >> cmp >> val;
            V.filter(col, cmp, val);
        } else {
            throw runtime_error(string("Unknown op: ") + op);
        }
    }
    V.print(); // only final output
    return 0;
}

