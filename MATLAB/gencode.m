POS_VAL = 2;	% POS peaks have value 2
NEG_VAL = 3;	% NEG peaks have value 3

POS = [locs_p',POS_VAL*ones(length(locs_p),1)];
NEG = [locs_n',NEG_VAL*ones(length(locs_n),1)];
all_peaks = [POS;NEG];
all_peaks = sortrows(all_peaks,1);

% now we have all the peaks that were thresholded (sorted in time), STORED IN all_peaks


min_peak_distance = 200;
k=1;
for i=1:length(all_peaks)
	if i==1
		masked_peaks(k,1) = all_peaks(i,1);
		masked_peaks(k,2) = all_peaks(i,2);
		k=k+1;
		continue
	end
	
	if all_peaks(i,2) == masked_peaks(k-1, 2) && all_peaks(i,1) < masked_peaks(k-1,1)+min_peak_distance
		continue
	else
		masked_peaks(k,1) = all_peaks(i,1);
		masked_peaks(k,2) = all_peaks(i,2);
		k=k+1;
	end
end

% now we have peaks, where same type of peak (e.g. ++) must be separated by min_peak_distance, STORED IN masked_peaks

% CODES: POS-NEG-POS-NEG = LRL,	any deviation = BLINK

% k=1;
% previous = [0, 0, 0, 0];
% for i=1:length(masked_peaks)
	% if masked_peaks(i) == POS_VAL && 
		% previous(