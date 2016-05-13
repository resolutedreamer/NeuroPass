function [newQRS] = plotPOS(signal,QRS,newQRS)
% this function takes the locations of points, stored
% in QRS (x-value), and plots the corresponding
% value of signal(point) in newQRS(point).
	j=1;	
	if (length(newQRS) ~= length(signal))
		print "ERROR: newQRS length not equal to signal length";
		return;
	end

	while j<length(QRS)+1
		newQRS(QRS(j)) = signal(QRS(j));
		j = j+1;
	end
end