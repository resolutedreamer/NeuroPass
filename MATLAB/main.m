close all;
clc;
%% SETUP
% corresponds to step 0
% -getting the data into the program
loaddata;
verbosity = 1;
% Fs = 128+1;
% look_ahead_percentage = .75;
thresholding_percentage = .5;
% min_samples_to_next_peak = int32(look_ahead_percentage*Fs);
% min_samples_to_next_peak = 1;

%% Find the peaks of the thresholded signal and plot them
% corresponds to step 1


to_threshold = F8;
[pks,locs]=findpeaks(to_threshold,'MINPEAKDISTANCE',50,'MINPEAKHEIGHT',(thresholding_percentage*1*max(to_threshold)));
% adjust this section some more

if verbosity == 1
	figure;
	newFiltered=zeros(length(to_threshold),1);
	plot(to_threshold)
	hold all;
	plot(locs, pks, 'o')
	title('Clench Peaks', 'FontWeight','bold')
end

%% Segment the data and plot it
% corresponds to step 2
edges_locs = generate_edges_from_locs(locs);
segmented = segment_by_edge(time, filtered, edges_locs);

if verbosity == 1
    figure;
    plot(time,filtered)
    for j=1:length(segmented)
        hold all;
        plot(segmented{j}(:,1),segmented{j}(:,2))
    end
    title('Segmented Clenches', 'FontWeight','bold')
end