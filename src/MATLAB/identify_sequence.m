function [result] = identify_sequence(ch1,ch2,time,verbosity)
% % % % Blink-Clench Identification

% % For the blink-clench identification algorithm, we will be using two
% % datastreams, F7 and T7. Essentially, F7 shows spikes for blinking and clenching,
% % while T7 only shows spikes for clenching. This means: given a spike on F7, we need
% % to determine whether it is for blinking or clenching.

% % How do we do this? Let T7 be a reference channel. Using mean+std we determine the
% % thresholding value necessary to detect peaks on this channel. Because our data
% % has been filtered to remove the DC offset, these values are directly usable to
% % threshold the dataset. Basically, ch2 = ref = T7 --> determines thresholding value.

% % Then, let look at the two possible outcomes dataset=ch1 and dataset=ch2.
% % ref=ch2, dataset=ch1 will find all peaks in ch1 (blinks and clenches)
% % ref=ch2, dataset=ch2 will find all peaks in ch2 (clenches)
% % ref=ch1, dataset=ch1 will find clenches in ch1 due to large amplitude difference (good but not robust for other signals / >2 events on a single channel)

% % Finally, generate the code corresponding to the sequence.

%% Step 1) Find all peaks
ref = ch2;
dataset = ch1;

thresholding_percentage = 1;
thresholding = mean(ref) + std(ref);

%% Step 2) Find peaks with thresholding
to_threshold = dataset;
[pks,locs]=findpeaks(to_threshold,'MINPEAKDISTANCE',50,'MINPEAKHEIGHT',(thresholding_percentage*thresholding));

if verbosity == 1
	figure;
	newFiltered=zeros(length(to_threshold),1);
	plot(to_threshold)
	hold all;
	plot(locs, pks, 'o')
	title('Blinking and Clenching Activity Peaks', 'FontWeight','bold')
end

%% Step 3) segment beats based on peak loc data
edges_locs = generate_edges_from_locs(locs);
segmented = segment_by_edge(time, dataset, edges_locs);

if verbosity == 1
    figure;
    plot(time,dataset)
    for j=1:length(segmented)
        hold all;
        plot(segmented{j}(:,1),segmented{j}(:,2))
    end
    title('Segmented activities', 'FontWeight','bold')
end

mixed_pks = pks;
mixed_locs = locs;
%%%% end
% %%%% Find clenching
% ref = ch2;
% dataset = ch2;

% thresholding_percentage = 1;
% thresholding = mean(ref) + std(ref);

% % % find peaks with thresholding
% to_threshold =dataset;
% [pks,locs]=findpeaks(to_threshold,'MINPEAKDISTANCE',50,'MINPEAKHEIGHT',(thresholding_percentage*thresholding));

% if verbosity == 1
	% figure;
	% newFiltered=zeros(length(to_threshold),1);
	% plot(to_threshold)
	% hold all;
	% plot(locs, pks, 'o')
	% title('Clench Peaks', 'FontWeight','bold')

% end

% % % segment beats based on peak loc data
% edges_locs = generate_edges_from_locs(locs);
% segmented = segment_by_edge(time, dataset, edges_locs);

% if verbosity == 1
    % figure;
    % plot(time,dataset)
    % for j=1:length(segmented)
        % hold all;
        % plot(segmented{j}(:,1),segmented{j}(:,2))
    % end
    % title('Segmented Clenches', 'FontWeight','bold')
% end
% clenching_locs = locs;
% clenching_pks = pks;
% %%%% end

%% Step 4) Find clenching (improved for specific F7 and T7 with no other movement)
ref = ch1;
dataset = ch1;

thresholding_percentage = 1;
thresholding = mean(ref) + std(ref);

%% Step 5 find peaks with thresholding
to_threshold =dataset;
[pks,locs]=findpeaks(to_threshold,'MINPEAKDISTANCE',50,'MINPEAKHEIGHT',(thresholding_percentage*thresholding));

if verbosity == 1
	figure;
	newFiltered=zeros(length(to_threshold),1);
	plot(to_threshold)
	hold all;
	plot(locs, pks, 'o')
	title('Clench Peaks', 'FontWeight','bold')

end

%% Step 6segment beats based on peak loc data
edges_locs = generate_edges_from_locs(locs);
segmented = segment_by_edge(time, dataset, edges_locs);

if verbosity == 1
    figure;
    plot(time,dataset)
    for j=1:length(segmented)
        hold all;
        plot(segmented{j}(:,1),segmented{j}(:,2))
    end
    title('Segmented Clenches', 'FontWeight','bold')
end
clenching_locs = locs;
clenching_pks = pks;
%%%% end

%% Final Step) Determine sequence
%using improved clenching locs algorithm
% logic 0 = blinking
% logic 1 = clenching
result = [];
for i=1:length(mixed_locs)
	clench = 0;
	for j=1:length(clenching_locs)
		if mixed_locs(i)==clenching_locs(j)
			clench = 1;
			break
		end
	end
	result(i) = clench;
end

% variable array 'result' is returned