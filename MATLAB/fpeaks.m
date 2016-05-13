function [pks,locs] = fpeaks(signal, threshold, min_distance, verbosity)

data = signal;

k=1;
for i=1:length(data)
	if i==1
		continue
	end
	
	if (i+1) > length(data)
		continue
	end
	
	if data(i) > data(i-1) && data(i) > data(i+1)
		% good canidate
		pks(k) = data(i);
		locs(k) = i;
		k=k+1;
	end
end

if verbosity >= 2
	length(pks)
	peaks = zeros(length(data),1);
	peaks = plotPOS(data,locs,peaks);
	figure;
	title('Peaks in a signal');
	hold all;
	plot(data)
	plot(peaks,'o')
end

% now we have all peaks

% threshold
% threshold = mean(data)+std(data)*1.5;
k=1;
for i=1:length(locs)
	if pks(i) < threshold
		continue
	else
		pks_th(k) = pks(i);
		locs_th(k) = locs(i);
		k=k+1;
	end
end

if verbosity >= 1
	length(pks_th)
	thresholded = zeros(length(data),1);
	th = plotPOS(data,locs_th,thresholded);
	figure;
	title('Peaks in a signal (threshold)');
	hold all;
	plot(data)
	plot(th,'o')
end

% minpeakdistance
% min_distance = 200;
k=1;
for i=1:length(locs_th)
	if k==1
		pks_mind(k) = pks_th(i);
		locs_mind(k) = locs_th(i);
		k=k+1;
		continue
	end
	
	% if locs_th(i) < locs_th(i-1)+min_distance 
		% continue
	if locs_th(i) < locs_mind(k-1)+min_distance 
		continue
	else
		pks_mind(k) = pks_th(i);
		locs_mind(k) = locs_th(i);
		k=k+1;
	end
end

if verbosity >= 2
	length(pks_mind)
	mindistance = zeros(length(data),1);
	mindistance = plotPOS(data,locs_mind,mindistance);
	figure;
	title('Peaks in a signal (threshold,min-peak-distance)');
	hold all;
	plot(data)
	plot(mindistance,'o')
end


% WHAT TO RETURN
pks = pks_th;
locs = locs_th;
