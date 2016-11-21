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


min_peak_distance = 175;
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

lrl = 0;
blinking = 0;
code1 = [POS_VAL, NEG_VAL, POS_VAL, NEG_VAL];
code2 = [POS_VAL, POS_VAL, POS_VAL, POS_VAL];
k=1;
i=1;
n=1;
m=1;
masked_array = masked_peaks;
rollz(1) = 1;
blinkz(1) = 1;
while (i<=length(masked_array))
	if i<4
		i=i+1;
		continue;
	end
	window = [ masked_array(i-3,2), masked_array(i-2,2), masked_array(i-1,2), masked_array(i,2)];

	if window == code1
		i;
		window;
		lrl = lrl + 1;
		rollz(n) = masked_array(i-3,1);
		n=n+1;
		code(k, 1) = masked_array(i-3,1);
		code(k, 2) = masked_array(i-3,2);
		i = i + 4;
		k=k+1;
	elseif window == code2
		blinking = blinking+1;
		blinkz(m) = masked_array(i-3,1);
		m=m+1;
		code(k, 1) = masked_array(i-3,1);
		code(k, 2) = masked_array(i-3,2);
		i = i + 4;
		k=k+1;
	else
		i=i+1;
		continue;
	end
end

plot_code = zeros(length(signal),1);
plot_lrl = plotPOS(signal,rollz,plot_code);
plot_blinks = plotPOS(signal,blinkz,plot_code);
figure;
title('Generated code');
hold all;
plot(signal)
plot(plot_lrl,'o')
plot(plot_blinks,'o')