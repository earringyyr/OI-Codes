#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
long long n, m = 370, ans, a[371] = {1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 128, 160, 200, 250, 256, 320, 400, 500, 512, 625, 640, 800, 1000, 1024, 1250, 1280, 1600, 2000, 2048, 2500, 2560, 3125, 3200, 4000, 4096, 5000, 5120, 6250, 6400, 8000, 8192, 10000, 10240, 12500, 12800, 15625, 16000, 16384, 20000, 20480, 25000, 25600, 31250, 32000, 32768, 40000, 40960, 50000, 51200, 62500, 64000, 65536, 78125, 80000, 81920, 100000, 102400, 125000, 128000, 131072, 156250, 160000, 163840, 200000, 204800, 250000, 256000, 262144, 312500, 320000, 327680, 390625, 400000, 409600, 500000, 512000, 524288, 625000, 640000, 655360, 781250, 800000, 819200, 1000000, 1024000, 1048576, 1250000, 1280000, 1310720, 1562500, 1600000, 1638400, 1953125, 2000000, 2048000, 2097152, 2500000, 2560000, 2621440, 3125000, 3200000, 3276800, 3906250, 4000000, 4096000, 4194304, 5000000, 5120000, 5242880, 6250000, 6400000, 6553600, 7812500, 8000000, 8192000, 8388608, 9765625, 10000000, 10240000, 10485760, 12500000, 12800000, 13107200, 15625000, 16000000, 16384000, 16777216, 19531250, 20000000, 20480000, 20971520, 25000000, 25600000, 26214400, 31250000, 32000000, 32768000, 33554432, 39062500, 40000000, 40960000, 41943040, 48828125, 50000000, 51200000, 52428800, 62500000, 64000000, 65536000, 67108864, 78125000, 80000000, 81920000, 83886080, 97656250, 100000000, 102400000, 104857600, 125000000, 128000000, 131072000, 134217728, 156250000, 160000000, 163840000, 167772160, 195312500, 200000000, 204800000, 209715200, 244140625, 250000000, 256000000, 262144000, 268435456, 312500000, 320000000, 327680000, 335544320, 390625000, 400000000, 409600000, 419430400, 488281250, 500000000, 512000000, 524288000, 536870912, 625000000, 640000000, 655360000, 671088640, 781250000, 800000000, 819200000, 838860800, 976562500, 1000000000, 1024000000, 1048576000, 1073741824, 1220703125, 1250000000, 1280000000, 1310720000, 1342177280, 1562500000, 1600000000, 1638400000, 1677721600, 1953125000, 2000000000, 2048000000, 2097152000, 2147483648, 2441406250, 2500000000, 2560000000, 2621440000, 2684354560, 3125000000, 3200000000, 3276800000, 3355443200, 3906250000, 4000000000, 4096000000, 4194304000, 4294967296, 4882812500, 5000000000, 5120000000, 5242880000, 5368709120, 6103515625, 6250000000, 6400000000, 6553600000, 6710886400, 7812500000, 8000000000, 8192000000, 8388608000, 8589934592, 9765625000, 10000000000, 10240000000, 10485760000, 10737418240, 12207031250, 12500000000, 12800000000, 13107200000, 13421772800, 15625000000, 16000000000, 16384000000, 16777216000, 17179869184, 19531250000, 20000000000, 20480000000, 20971520000, 21474836480, 24414062500, 25000000000, 25600000000, 26214400000, 26843545600, 30517578125, 31250000000, 32000000000, 32768000000, 33554432000, 34359738368, 39062500000, 40000000000, 40960000000, 41943040000, 42949672960, 48828125000, 50000000000, 51200000000, 52428800000, 53687091200, 61035156250, 62500000000, 64000000000, 65536000000, 67108864000, 68719476736, 78125000000, 80000000000, 81920000000, 83886080000, 85899345920, 97656250000, 100000000000, 102400000000, 104857600000, 107374182400, 122070312500, 125000000000, 128000000000, 131072000000, 134217728000, 137438953472, 152587890625, 156250000000, 160000000000, 163840000000, 167772160000, 171798691840, 195312500000, 200000000000, 204800000000, 209715200000, 214748364800, 244140625000, 250000000000, 256000000000, 262144000000, 268435456000, 274877906944, 305175781250, 312500000000, 320000000000, 327680000000, 335544320000, 343597383680, 390625000000, 400000000000, 409600000000, 419430400000, 429496729600, 488281250000, 500000000000, 512000000000, 524288000000, 536870912000, 549755813888, 610351562500, 625000000000, 640000000000, 655360000000, 671088640000, 687194767360, 762939453125, 781250000000, 800000000000, 819200000000, 838860800000, 858993459200, 976562500000, 1000000000000};
int main()
{
    ll n, ans = 0;
    scanf("%lld", &n);
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        while (m > 0 && a[m] > n / l)
            --m;
        ans += (ll)((r - r / 2 - r / 5 + r / 10) - ((l - 1) - (l - 1) / 2 - (l - 1) / 5 + (l - 1) / 10)) * (m + 1) * (n / l);
    }
    printf("%lld", ans);
    return 0;
}