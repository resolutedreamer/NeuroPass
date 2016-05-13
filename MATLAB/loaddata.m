%% LOAD DATA
close all;
clc;
M = csvread('10clenches.csv');
EEG_data = M(:,3:16);

for i=1:length(M(:,1))
	time(i) = i;
end


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

% IIR_TC = 256;
% [rows columns]= size(EEG_data);
% AC_EEG_data = zeros(rows, columns);

clear M;
clear i;