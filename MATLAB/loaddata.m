%% prep
clear;
close all;
clc;
%% get the input file
M = csvread('10clenches.csv');
EEG_data = M(:,3:16);
clear M;
display('Input successfully imported')
%% prepare the time index
for i=1:length(EEG_data(:,1))
	time(i) = i;
end
time = time';
%% prepare the DC removing filter for use
% d = fdesign.highpass('Fst,Fp,Ast,Ap',0.1,0.16,60,1, 128);

N    = 5;     % Order
F3dB = 0.16;  % 3-dB Frequency
Fs   = 128;   % Sampling Frequency

d = fdesign.highpass('n,f3db', N, F3dB, Fs);

Hd = design(d,'butter');
fvtool(Hd)
%clear d;
%% normalize the data so that the filter works properly
% simple normalizing
for i=1:14 
    to_normalize = EEG_data(:,i);
    normalized = ( to_normalize - (.5*(max(to_normalize)+min(to_normalize))) ) / (.5*( max(to_normalize) - min(to_normalize) )); %normalize between -1 and 1
    EEG_data(:,i) = normalized;
end
clear to_normalize;
clear normalized;
display('Data succesfully normalized')
%% run the filter on the normalized data
for i=1:14 
    to_filter = EEG_data(:,i);
    filtered = filter(Hd,to_filter);
    EEG_data_copy(:,i) = filtered;
end
clear to_filter;
% clear filtered;
% clear Hd;
%% extract the processed datasets
AF3 = EEG_data(:,1);
F7 = EEG_data(:,2);
F3 = EEG_data(:,3);
FC5 = EEG_data(:,4);
T7 = EEG_data(:,5);
P7 = EEG_data(:,6);
O1 = EEG_data(:,7);
O2 = EEG_data(:,8);
P8 = EEG_data(:,9);
T8 = EEG_data(:,10);
FC6 = EEG_data(:,11);
F4 = EEG_data(:,12);
F8 = EEG_data(:,13);
AF4 = EEG_data(:,14);
display('Done.')
%% clean up
% clear EEG_data;
clear i;