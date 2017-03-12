function [edges_locs] = generate_edges_from_locs(peaks)
% this function takes a vector of peaks (x-values) and
% returns a new vector with edges. currently, it generates edges
% as the midpoint between two peaks.

i=1;

st=1;

sort(peaks);

while i<length(peaks)
    %nd=peaks(i);
	%edge = int32( (nd+st)/2 );
    
    %if (i==1)
    %    edge = i;
    %    edge_locs(i) = edge;
    %elseif (i==length(peaks)-1)
    %    edge = i;
    %    edge_locs(i) = i;
    %else
        edge = int32( (peaks(i)+peaks(i+1)) /2 );
        edges_locs(i) = edge;
    %end
    
	st = edge +1;   
    i =i+1; 
end

%length(edge)
%length(peaks)