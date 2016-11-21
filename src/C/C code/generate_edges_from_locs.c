#include "sort_array.h"

char* edges_locs(char* peaks, int numof_pks)
// this function takes a vector of peaks (x-values) and
// returns a new vector with edges. currently, it generates edges
// as the midpoint between two peaks.

int pkindex = 1;
sort_array(peaks);
int edge_locs[numof_pks];

while (pkindex < totalpks)
{
    int edgeof_currentpk = (peaks[pkindex] + peaks[pkindex + 1]) / 2 ;
    edge_locs[pkindex] = edgeof_currentpk;
    pkindex = pkindex + 1;
}
