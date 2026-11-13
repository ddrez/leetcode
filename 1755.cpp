class Solution {
public:
    long long best;
    int n;
    long long * remNegative;
    long long * remPositive;
    int * nums;
    long long target;
    bool exact_solution_found = false;

    void dfs(int idx, long long curSum) {
        long long low = curSum - remNegative[idx];
        long long high = curSum + remPositive[idx];

        long long minPossible;
        if (target >= low && target <= high) minPossible = 0;
        else minPossible = min(std::llabs(target - low), std::llabs(target - high));

        if (minPossible >= best) return;

        if (idx == n) {
            best = min(best, std::llabs(curSum - target));
            return;
        }

        dfs(idx + 1, curSum + nums[idx]);
        dfs(idx + 1, curSum);
    }

    int surface_minval() {
        int minval = llabs(target);
        long long sm = 0;
    
        for (int i = 0; i < n; i++) {
            int diff = nums[i];
            if (llabs(sm + diff - target) < llabs(sm - target)) {
                sm += diff;
            }
        }
    
        return min(minval, (int)llabs(sm - target));
    }

    int minAbsDifference(vector<int>& nums, int goal) {

        std::sort(nums.begin(), nums.end(),
                  [](int a, int b) { return abs(a) > abs(b); });

        this->n = nums.size();
        this->target = goal;
        this->nums = nums.data();

        best = surface_minval();
        if ( best == 0) return 0;

        vector<long long> remNegative, remPositive;
        remNegative.assign(n + 1, 0);
        remPositive.assign(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            auto val = nums[i];
            remNegative[i] = remNegative[i+1];
            remPositive[i] = remPositive[i+1];
            if (val >= 0) remPositive[i] += val;
            else remNegative[i] -= val;
        }

        this->remPositive = remPositive.data();
        this->remNegative = remNegative.data();

        dfs(0, 0LL);

        return (int)best;
    }
};
