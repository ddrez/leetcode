class Solution {
  public:
    int maxIncreasingGroups(vector<int> &usageLimits) {

        long ln = usageLimits.size();
        long ul;
        vector<long> spec(ln);

        for (long i = 0; i < ln; i++) {
            ul = usageLimits[i];
            if ( ul < ln )
                spec[ul]++;
        }

        long c = 0;
        long num = 0;
        long trhld = 0;
        long n;

        for (long i = 1; i < ln; i++) {
            if ( spec[i] == 0 )
                continue;

            n = spec[i];
            num += n;
            c += i*n;
            
            trhld += std::max(0L, num - (int)((sqrt(1+8*c)-1)/2) - trhld);

        }

        return ln - trhld;

    }
};
