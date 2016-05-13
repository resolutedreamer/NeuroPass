close all
clear all
clc

% load('AC_EEG_data.mat');
% result_generator
% signal = T8;

% % SETUP
% loaddata('data/anthony-1minclenches-19.11.13.17.25.47.csv')
% loaddata('data/anthony-1minlniks-19.11.13.17.23.35.csv')
% loaddata('data/anthony-1minmixed-19.11.13.19.12.03.csv')
input_path = 'data/s1-24eyeslrl-27.11.13.01.57.01.csv';
% input_path = 'data/s1-password-27.11.13.01.59.53.csv';
% input_path = 'data/s4-30clenches-26.11.13.23.16.05.csv';

input_path = 'data/s1-1-09.12.13.12.17.47.csv';

% % LOAD DATA
loaddata(input_path);
load('AC_EEG_data.mat');
Fs = 128;

AF3 = AC_EEG_data(:,1);
F7 = AC_EEG_data(:,2);		%eyeroll
F3 = AC_EEG_data(:,3);
FC5 = AC_EEG_data(:,4);
T7 = AC_EEG_data(:,5);
P7 = AC_EEG_data(:,6);
O1 = AC_EEG_data(:,7);
O2 = AC_EEG_data(:,8);
P8 = AC_EEG_data(:,9);
T8 = AC_EEG_data(:,10);		%eyeroll
FC6 = AC_EEG_data(:,11);	%eyeroll
F4 = AC_EEG_data(:,12);		%eyeroll
F8 = AC_EEG_data(:,13);		%eyeroll
AF4 = AC_EEG_data(:,14);
time = AC_EEG_data(:,15);

% Filters
display('Applying filters ...');
signal = FC5;%end-200);
verbosity = 1;
filtered = HPF(signal, 1000, Fs, 1);
% filtered = filtered(400:end)
% filtered = LPF(filtered, 20, Fs, 1);

% Peaks
display('Finding peaks ...');
signal = filtered;%(1:4480);%(200:end);
threshold = mean(signal)+std(signal)*1;
min_distance = 200;
verbosity = 1;
[pks_p, locs_p] = fpeaks(signal, threshold, min_distance, verbosity);
[pks_n, locs_n] = fpeaks(-1*signal, threshold, min_distance, verbosity);

% POS = [locs_p',2*ones(length(locs_p),1)];
% NEG = [locs_n',3*ones(length(locs_n),1)];
% POS_NEG = [POS;NEG];
% POS_NEG = sortrows(POS_NEG,1);

gencode


% for i=1:14
	% signal = AC_EEG_data(:,i);
	% threshold = mean(signal)+std(signal)*1.5;
	% min_distance = 200;
	% verbosity = 1;
	% [pks, locs] = fpeaks(signal, threshold, min_distance, verbosity);
% end