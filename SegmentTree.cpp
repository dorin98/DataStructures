#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
 public:
    SegmentTree(int N) {
        this->N = N;
        Tree.resize(4*N);
        Lazy.resize(4*N);
    }
    void UpdateElement(int pos, int val) {
        updateElement(1, 1, N, pos, val);
    }
    int Query(int a, int b) {
        return query(1, 1, N, a, b);
    }
    void UpdateRange(int a, int b, int val) {
        updateRange(1, 1, N, a, b, val);
    }

 private:
    int N;
    vector <int> Tree;
    vector <int> Lazy;
    void pushLazyUpdate(int node, int left, int right, int level) {
        if (level == 2)
            return;
        if (Lazy[node]) {
            Tree[node] += Lazy[node];
            if (left != right) {
                Lazy[2 * node] += Lazy[node];
                Lazy[2 * node + 1] += Lazy[node];
            }
            Lazy[node] = 0;
            int mid = (left + right) >> 1;
            if (left != right) {
                pushLazyUpdate(2 * node, left, mid, level + 1);
                pushLazyUpdate(2 * node + 1, mid + 1, right, level + 1);
            }
        }
    }
    void updateElement(int node, int left, int right, int pos, int val) {
        pushLazyUpdate(node, left, right, 0);
        if (left == right) {
            Tree[node] = val;
            return;
        }
        int mid = (left + right) >> 1;
        if (pos <= mid)
            updateElement(2 * node, left, mid, pos, val);
        else
            updateElement(2 * node + 1, mid+1, right, pos, val);
        Tree[node] = max(Tree[2 * node], Tree[2 * node + 1]);
    }
    int query(int node, int left, int right, int a, int b) {
        pushLazyUpdate(node, left, right, 0);
        if (a <= left && right <= b)
            return Tree[node];
        int maxim = 0;
        int mid = (left + right) >> 1;
        if (a <= mid)
            maxim = max(maxim, query(2 * node, left, mid, a, b));
        if (b > mid)
            maxim = max(maxim, query(2 * node + 1, mid + 1, right, a, b));
        return maxim;
    }
    void updateRange(int node, int left, int right, int a, int b, int val) {
        pushLazyUpdate(node, left, right, 0);
        if (a <= left && right <= b) {
            Lazy[node] += val;
            return;
        }
        int mid = (left + right) >> 1;
        if (a <= mid)
            updateRange(2 * node, left, mid, a, b, val);
        if (b > mid)
            updateRange(2 * node + 1, mid + 1, right, a, b, val);
        Tree[node] = max(Tree[2 * node], Tree[2 * node + 1]);
    }
};

int main()
{
    int n, m, a, b, x;
    cin >> n >> m;
    SegmentTree *T = new SegmentTree(n);
    for (int x, i = 1 ; i <= n ; ++i) {
        cin >> x;
        T->UpdateElement(i,x);
    }
    while (m--) {
        int type;
        cin >> type;
        if (type == 2) {
            cin >> a >> b >> x;
            T->UpdateRange(a,b,x);
        }
        else if (type == 1) {
            cin >> a >> b;
            T->UpdateElement(a,b);
        }
        else {
            cin >> a >> b;
            cout << T->Query(a,b) << "\n";
        }
    }
    return 0;
}
