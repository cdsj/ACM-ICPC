sg = [0, 1, 2, 4, 8, 16, 32, 64, 128, 255, 256, 512, 1024, 2048, 3855, 4096, 8192, 13107, 16384, 21845, 27306, 32768, 38506, 65536, 71576, 92115, 101470, 131072, 138406, 172589, 240014, 262144, 272069, 380556, 524288, 536169, 679601, 847140, 1048576, 1072054, 1258879, 1397519, 2005450, 2097152, 2121415, 2496892, 2738813, 3993667, 4194304, 4241896, 4617503, 5821704, 7559873, 8388608, 8439273, 8861366, 11119275, 11973252, 13280789, 16777216, 16844349, 17102035, 19984054, 21979742, 23734709]

n = int(raw_input())
ns = map(lambda x: '{:b}'.format(x).count('1'), [int(raw_input()) for i in xrange(n)])
res = reduce(lambda x, y: x ^ y, map(lambda z: sg[z], ns))

if res == 0:
    print 'L'
else:
    print 'B'
