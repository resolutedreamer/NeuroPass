function [segment] = segment_by_edge(time,signal,edges)
% this function takes a vector of edges (x-values) and
% segments an input signal at the edges.
% Output is an array of signal vectors between the edges. 

i=1;
st=1;
sort(edges);

while i<length(edges)
    nd=int32(edges(i));    
    segment{i} = [time(st:nd), signal(st:nd)]; 
    i =i+1;
    st = nd;    
end