function [yn] = HPF(signal, cutoff, fs, verbosity)
% % 2nd order HPF filter

% filtering coefficients a, b
RC = 1/(2*pi*cutoff);
T = 1/fs;
a = [0, 0, 0];		% coeffs on numerator: so 0, y(n-1), y(n-2)		a(0)==0 for some reason
b = [0, 0, 0];		% coeffs on denominator: so x(0), x(n-1), x(n-2)
b(1) = 1* ( 1 / (1 + T/(2*RC)) ) ;
b(2) = -1* ( 1 / (1 + T/(2*RC)) ) ;
a(2) = -1*(1 - (2*RC)/T ) / (1 + (2*RC)/T ) ;

% YuYu's original coeffs
% b = [0.0, 0.48255, 0.0];
% a = [-0.71624, 0.387913, 0];


if verbosity >= 1
	a
	b
end

data = signal;
w = [0, 0, 0];
for i=1:length(data)
	input = data(i);
	
	wn = input - a(1)*w(1) - a(2)*w(2);
	yn(i) = b(1)*wn + b(2)*w(1) + b(3)*w(2);
	w(2) = w(1);
	w(1) = wn;
end

if verbosity >= 1
	figure;
	title('filtered data');
	hold all;
	plot(data);
	plot(yn);
end