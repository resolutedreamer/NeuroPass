pks_p;
window = 3*Fs;
k=1;
i=1;
while i<length(signal)
	limit = i+window;
	number = 0;
	for j=1:length(locs_p)
		if locs_p(j) < limit && locs_p(j) > i
			number = number+1;
		end
	end
	i= i+window;
	period(k) = number;
	k=k+1;
end

k
k=1;
for i=1:length(period)
	if period(i) > 5
		code(k) = '3';
		k=k+1;
	elseif period(i)>0
		code(k) = '2';
		k=k+1;
	end
end

code
