masked_array = masked_peaks;
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
