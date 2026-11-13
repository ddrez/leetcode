class Solution {
public:

    typedef unsigned long long ull;
    ull MOD = (1e9+7);

    void sample(vector<pair<int,int>> &bag, int a, int m, int s, int p1,
                int p2, int group, int k = 3) {
        if (m == s) {
            bag.push_back({a, group});
        } else {
            for (int i = 0; i < k; i++) {
                if (i != p1) {
                    int new_a = a | (1 << (k*s+i) );
                    if ( s > 1 )
                        if (i == p2)
                            group = group | (1 << (s-2));
                        else if (i != p2)
                            group = group & ~(1 << (s-2));
                    sample(bag, new_a, m, s + 1, i, p1, group, k);
                }
            }
        }
    }

    int colorTheGrid(int m, int n) {
        int k = 3;

        vector<pair<int,int>> bag;


        for (int i=0; i<k; i++) {
            int a = 1<<i;
            sample(bag, a, m, 1, i, -1, 0);
        }

        if ( n == 1) {
            return bag.size() % MOD;
        }

        int groups_count = max(1,int(pow(2,m-2)));

        vector<vector<ull>> state(groups_count, vector<ull>(groups_count));
        vector<vector<int>> transitions(groups_count, vector<int>(groups_count));
        int bag_size = bag.size();

        for (int i=0; i<bag_size; i++) {
            for (int j=0; j<bag_size; j++) {
                if ( (bag[i].first & bag[j].first) == 0 )
                    state[bag[i].second][bag[j].second] += 1;
            }
        }

        int delim = bag_size/groups_count;
        for (int i=0; i<groups_count; i++) {
            for (int j=0; j<groups_count; j++) {
                transitions[i][j] = state[i][j] / delim;
            }
        }


        vector<ull> state_new(groups_count);
        for (int s=2; s<n; s++) {
            for (int i=0; i<groups_count; i++) {
                for (int j=0; j<groups_count; j++) {
                    ull val = 0;
                    for (int k=0; k<groups_count; k++) {
                        val += (state[i][k] * transitions[k][j]);
                    }
                    state_new[j] = val % MOD;
                }
                for (int j=0; j<groups_count; j++) {
                    state[i][j] = state_new[j];
                }
            }
        }

        ull result = 0;
        for (int i=0; i<groups_count; i++) {
            for (int j=0; j<groups_count; j++) {
                result += state[i][j];
                result %= MOD;
            }
        }
        
        return result;
    }
};
