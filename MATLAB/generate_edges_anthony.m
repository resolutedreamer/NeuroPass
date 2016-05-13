function [edges_locs] = generate_edges_anthony(peaks)
% this function takes a vector of peaks (x-values) and
% returns a new vector with edges. currently, it generates edges
% as the midpoint between two peaks.

numof_pks = length(peaks);
pkindex = 1;
sort(peaks);
edge_locs = zeros(numof_pks);

while (pkindex < numof_pks)
    edgeof_currentpk = int32( (peaks(pkindex) + peaks(pkindex + 1)) /2 );
    edge_locs(pkindex) = edgeof_currentpk;
    pkindex = pkindex + 1; 
end
