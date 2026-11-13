class Solution {
  public:
    void traverse(int r, vector<int> &res,
                  vector<vector<int>> &transpositions) {
        for (int &i : transpositions[r]) {
            res[abs(i)] = res[r] + (signbit(i) ? -1 : 1);
            traverse(abs(i), res, transpositions);
        }
    }

    vector<int> minEdgeReversals(int n, vector<vector<int>> &edges) {
        vector<int> res(n);
        vector<bool> visited(n);
        vector<bool> visited_edge(edges.size());
        int shifts_count = 0;
        int visited_count = 0;
        vector<vector<int>> transpositions(n);

        int r = 0;
        visited[r] = true;
        visited_count = 1;
        do {
            for (int i = 0; i < edges.size(); i++) {
                if (visited_edge[i])
                    continue;
                int e0 = edges[i][0];
                int e1 = edges[i][1];
                if ((visited[e0] or e0 == r)) {
                    r = e1;
                    visited[r] = true;
                    visited_count++;
                    transpositions[e0].push_back(e1);
                    visited_edge[i] = true;
                } else if ((visited[e1] or e1 == r)) {
                    r = e0;
                    visited[r] = true;
                    shifts_count++;
                    visited_count++;
                    transpositions[e1].push_back(-e0);
                    visited_edge[i] = true;
                }
            }
        } while (visited_count < n);

        res[0] = shifts_count;
        r = 0;

        traverse(r, res, transpositions);
        return res;
    }
};
