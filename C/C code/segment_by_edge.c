char* completed_segment(char* time, char* signal, int signal_length, char* edges, int numof_edges)
// this function takes a vector of edges (x-values) and
// segments an input signal at the edges.
// Output is an array of signal vectors between the edges. 

int i = 0, seg_start = 0, seg_end = 0;
sort_array(edges);
double segment[size_time][size_signal] = (double*)malloc(sizeof(double)*size_time*size_signal);



while (i < numof_edges)
{
    seg_end = edges[i];
	
	segment[i] = [time(seg_start:seg_end), signal(seg_start:seg_end)]; 
    
	seg_start = seg_end;
	i++;
}

return segment;
