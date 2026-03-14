__kernel void bitonic_step(__global int* data, uint j, uint k) {
    uint i = (uint)get_global_id(0);
    uint ixj = i ^ j;

    if (ixj > i) {
        int a = data[i];
        int b = data[ixj];

        int ascending = ((i & k) == 0);

        if ((ascending && a > b) || (!ascending && a < b)) {
            data[i] = b;
            data[ixj] = a;
        }
    }
}
