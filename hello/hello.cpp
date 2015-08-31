#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// quick sort with O(1) space
void quickSort(vector<int> &vec) {
    int rangel, ranger, rangem;
    rangel = 0, ranger = vec.size();
    for (; rangel + 1 < vec.size(); ) {
        int m[2] = { rangel, rangel + 1 };
        if (vec[rangel] < vec[rangel + 1]) {
            swap(m[0], m[1]);
        }
        if (ranger - rangel > 2) {
            for (int i = rangel + 2; i < ranger; ++i) {
                if (vec[i] > vec[ m[0] ]) {
                    m[1] = m[0];
                    m[0] = i;
                } else if (vec[i] > vec[m[1]]) {
                    m[1] = i;
                }
            }
            swap(vec[m[0]], vec[ranger - 1]);
            swap(vec[m[1]], vec[ranger - 2]);
            int midVal = vec[ranger - 1] / 2;
            int midIndex = rangel;
            for (int i = rangel; i < ranger - 2; ++i) {
                if (vec[i] < midVal) {
                    swap(vec[i], vec[midIndex]);
                    midIndex++;
                }
            }
            swap(vec[midIndex], vec[ranger - 2]);
            rangel = rangel;
            ranger = midIndex;
        } else {
            if (ranger - rangel == 2 && vec[rangel] > vec[ranger - 1]) {
                swap(vec[rangel], vec[ranger - 1]);
            }
            rangel = ranger;
            for (ranger += 1; ranger < vec.size() && vec[rangel] > vec[ranger]; ++ranger) {}
        }
    }
}

int main(int argc, const char* argv[]) {
    vector<int> vec;
    for (int i = 100; i >= 0; --i) {
        vec.push_back(i % 5);
    }
    quickSort(vec);
    return 0;
}
