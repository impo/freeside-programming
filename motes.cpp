#include <iostream>
#include <list>

using namespace std;

int main() {
    int T; // number of test cases
    cin >> T;

    for (int t = 0; t < T; t++) {
        int A; // size of Armin's mote
        int N; // number of motes
        int moves = 0;
        cin >> A >> N;

        list<int> motes(N);
        int mote;
        for (int i = 0; i < N; i++) {
            cin >> mote;
            motes.push_back(mote);
        }

        motes.sort();

        while (motes.size() > 0) {
            if (motes.front() < A) {  // current smallest mote is smaller
                A += motes.front();
                motes.pop_front();
            }
            else if (motes.front() == A) { // csm is same as Armin
                ++moves;
                if (A == 1)
                    motes.pop_front();
                else
                    A += (A - 1); // add mote of size A - 1
            }
            else { // current smallest mote bigger than Armin's
                ++moves;
                if (A == 1 || motes.size() == 1) {
                    motes.pop_front();
                }
                else {
                    A += (A - 1);
                }
            }
        }
        cout << "Case #" << t + 1 << ": " << moves << endl;
    }
    return 0;
}
