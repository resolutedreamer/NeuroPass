function [edges_locs] = generate_edges_from_locs(peaks)
% this function takes a vector of peaks (x-values) and
% returns a new vector with edges. currently, it generates edges
% as the midpoint between two peaks.

i=1;
st=1;
sort(peaks);

while i<length(peaks)
	edge = int32( (peaks(i)+peaks(i+1)) /2 );
	edges_locs(i) = edge;
	st = edge +1;   
    i = i+1; 
end
