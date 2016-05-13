close all;
clc;

% %% SETUP
verbosity = 1;
Fs = 128+1;
look_ahead_percentage = .75;
thresholding_percentage = .6;
min_samples_to_next_peak = int32(look_ahead_percentage*Fs);
% min_samples_to_next_peak = 1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % create test data
test = F8;

% % simple denoising
% integral = cumtrapz(test);
% deriv = diff(integral);
% denoised = deriv;
% if verbosity == 1
	% plot(denoised)
% end
% clear integral, deriv;
denoised = test;

% % simple normalizing
to_normalize = denoised;
%normalized = to_normalize./norm(to_normalize);		%normalize with norm
normalized = ( to_normalize - min(to_normalize) ) / (max(to_normalize) - min(to_normalize)); %normalize between 0 and 1
normalized = ( to_normalize - (.5*(max(to_normalize)+min(to_normalize))) ) / (.5*( max(to_normalize) - min(to_normalize) )); %normalize between -1 and 1
if verbosity == 1
	figure;
	plot(normalized)
	title('normalized signal')
end
clear to_normalize;

% % % remove DC
% to_remove_DC = normalized;
% denoised_mean = to_remove_DC - mean(to_remove_DC);
% % denoised_mean = to_remove_DC - test2;
% if verbosity == 1
	% figure;
	% plot(denoised_mean)
	% title('denoised mean')
% end
% clear to_remove_DC;



% % HPF
d = fdesign.highpass('Fst,Fp,Ast,Ap',0.1,0.16,60,1, 128);
Hd = design(d,'butter');
% fvtool(Hd);
filtered = filter(Hd,normalized);
figure;
plot(filtered)
title('aaaaaaaaaaaaaaaaaaaaa');
hold all;



% % thresholded signal
to_threshold = filtered;
% to_threshold = normalized;
% to_threshold = denoised_mean;
[pks,locs]=findpeaks(-1*to_threshold,'MINPEAKDISTANCE',min_samples_to_next_peak,'MINPEAKHEIGHT',(thresholding_percentage*1*max(to_threshold)));
if verbosity == 1
	figure;
	newFiltered=zeros(length(to_threshold),1);
	plot(to_threshold)
	hold all;
	plot(plotPOS(to_threshold,locs, newFiltered), 'o')
	title('locs on normalized')
end

edges_locs = generate_edges_from_locs(locs);
segmented = segment_by_edge(time, filtered, edges_locs);

% plot em
figure;
plot(time,filtered)
for j=1:length(segmented)
    hold all;
    plot(segmented{j}(:,1),segmented{j}(:,2))
end
title('Beats in an EKG', 'FontWeight','bold')
