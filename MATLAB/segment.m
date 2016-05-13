function [segmented] = segment(time, ekg, algorithm, Fs)

%options
if ~isstr(algorithm)
    disp (' nah dude, provide a algorithm as a string. choose from nQRS, h1QRS, h2QRS, or onset')
elseif strcmp(algorithm,'nQRS')
    nQRS = nqrsdetect(ekg,Fs);
    peaks = nQRS;
elseif strcmp(algorithm,'h1QRS')
    HDR1 = qrsdetect(ekg,Fs,1);
    h1QRS = HDR1.EVENT.POS;
    peaks = h1QRS;
elseif strcmp(algorithm,'h2QRS')
    HDR2 = qrsdetect(ekg,Fs,2);
    h2QRS = HDR2.EVENT.POS;
    peaks = h2QRS;
elseif strcmp(algorithm,'onset')
    onset = DetectPulseOnset(ekg, Fs, 120);
    peaks = onset;
else
    disp (' nah dude, provide a algorithm as a string. choose from nQRS, h1QRS, h2QRS, or onset')
    disp (' e.g. returned_segmented = segment(time, ekg1, "nQRS", 1000); ')
end

edges_locs = generate_edges_from_locs(peaks);
segmented = segment_by_edge(time, ekg, edges_locs);