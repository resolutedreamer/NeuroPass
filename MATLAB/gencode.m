POS_VAL = 2;	% POS peaks have value 2
NEG_VAL = 3;	% NEG peaks have value 3

POS = [locs_p',POS_VAL*ones(length(locs_p),1)];
NEG = [locs_n',NEG_VAL*ones(length(locs_n),1)];
all_peaks = [POS;NEG];
all_peaks = sortrows(all_peaks,1);

plot_all_peaks = zeros(length(signal),1);
plot_all_peaks = plotPOS(signal,all_peaks(:,1),plot_all_peaks);
figure;
title('All peaks');
hold all;
plot(signal)
plot(plot_all_peaks,'o')

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

plot_masked_peaks = zeros(length(signal),1);
plot_masked_peaks = plotPOS(signal,masked_peaks(:,1),plot_masked_peaks);
figure;
title('Masked peaks');
hold all;
plot(signal)
plot(plot_masked_peaks,'o')

% now we have peaks, where same type of peak (e.g. ++) must be separated by min_peak_distance, STORED IN masked_peaks


% CODES: POS-NEG-POS-NEG = LRL,	any deviation = BLINK

% k=1;
% blinks=0;
% lrl = 0;

% lrlposition = zeros(30,1);
% lrlheight = zeros(30,1);
% lrlcount = 0;
% previous = [0, 0, 0, 0];
% for i=1:length(masked_peaks)-3
	% if i==1
		% continue
	% end
	
	% if masked_peaks(i,2) == 2
		% if masked_peaks(i+1,2) == 3
			% if masked_peaks(i+2,2) == 2
				% if masked_peaks(i+3,2) == 3
					% %we increment the count of lrls
					% lrlcount = lrlcount + 1;
					% %we set the position of the lrl event
					% lrlposition(lrlcount) = masked_peaks(i,1);
					% i = i+3;
				% end
			% end
		% end
	% end

	
% end
% lrlcount = lrlcount -1;

lrl = 0;
code = [2, 3, 2, 3];
k=1;
masked_array = masked_peaks;
i=1;
while (i<length(masked_peaks))
	if i<4
		i=i+1;
		continue
	end
	window = [ masked_array(i-3,2), masked_array(i-2,2), masked_array(i-1,2), masked_array(i,2)];
	
	if window == code
		i; window;
		lrl = lrl + 1;
		i = i + 3;
		store(k) = masked_array(i-3,1);
		k=k+1;
	else
		i=i+1;
		continue;
	end
	
end	



plot_code = zeros(length(signal),1);
plot_code = plotPOS(signal,store,plot_code);
figure;
title('Generated code');
hold all;
plot(signal)
plot(plot_code,'o')

