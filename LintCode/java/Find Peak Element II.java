class Solution {
    /**
     * @param A: An integer matrix
     * @return: The index of the peak
     */
    final static int INF = 0x3f3f3f3f;
    
    public List<Integer> findPeakII(int[][] A) {
        int n = A.length;
        if (n == 0) {
            return new ArrayList<Integer>();
        }
        int m = A[0].length;
        if (m == 0) {
            return new ArrayList<Integer>();
        }
        int y0 = 0;
        int y1 = n - 1;
        int x0 = 0;
        int x1 = m - 1;
        
        while (true) {
            int my = (y0 + y1) / 2;
            int mx = (x0 + x1) / 2;
            
            int max_y = 0;
            int max_x = 0;
            int maxi = -INF;
            
            for (int i = 0; i < n; i++) {
                if (A[i][mx] > maxi) {
                    maxi = A[i][mx];
                    max_x = mx;
                    max_y = i;
                }
            }
            
            for (int i = 0; i < m; i++) {
                if (A[my][i] > maxi) {
                    maxi = A[my][i];
                    max_x = i;
                    max_y = my;
                }
            }
            
            int next = 0;
            if (max_x != mx) {
                if (A[max_y][max_x] < A[max_y - 1][max_x]) {
                    next = max_x < mx? 1: 2;
                } else if (A[max_y][max_x] < A[max_y + 1][max_x]) {
                    next = max_x < mx? 3: 4;
                }
            }
            if (max_y != my) {
                if (A[max_y][max_x] < A[max_y][max_x - 1]) {
                    next = max_y < my? 1: 3;
                } else if (A[max_y][max_x] < A[max_y][max_x + 1]) {
                    next = max_y < my? 2: 4;
                }
            }
            
            switch (next) {
                case 0: {
                    return Arrays.asList(max_y, max_x);
                }
                case 1: {
                    x1 = mx;
                    y1 = my;
                }; break;
                case 2: {
                    x0 = mx;
                    y1 = my;
                }; break;
                case 3: {
                    x1 = mx;
                    y0 = my;
                }; break;
                case 4: {
                    x0 = mx;
                    y0 = my;
                }; break;
            }
        }
    }
}

