function Hd = untitled
%UNTITLED Returns a discrete-time filter System object.

% MATLAB Code
% Generated by MATLAB(R) 8.1 and the Signal Processing Toolbox 6.19.
% Generated on: 13-Nov-2013 12:44:24

N    = 1;     % Order
F3dB = 0.16;  % 3-dB Frequency
Fs   = 128;   % Sampling Frequency

h = fdesign.highpass('n,f3db', N, F3dB, Fs);

Hd = design(h, 'butter', ...
    'SystemObject', true);



