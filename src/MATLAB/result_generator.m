function result = result_generator(input_path)
%result_generator Summary of this function goes here
%   Detailed explanation goes here

% loaddata('data/anthony-1minclenches-19.11.13.17.25.47.csv')
% loaddata('data/anthony-1minlniks-19.11.13.17.23.35.csv')
% loaddata('data/anthony-1minmixed-19.11.13.19.12.03.csv')
loaddata(input_path);
load('AC_EEG_data.mat');

%% extract the processed datasets
AF3 = AC_EEG_data(:,1);
F7 = AC_EEG_data(:,2);
F3 = AC_EEG_data(:,3);
FC5 = AC_EEG_data(:,4);
T7 = AC_EEG_data(:,5);
P7 = AC_EEG_data(:,6);
O1 = AC_EEG_data(:,7);
O2 = AC_EEG_data(:,8);
P8 = AC_EEG_data(:,9);
T8 = AC_EEG_data(:,10);
FC6 = AC_EEG_data(:,11);
F4 = AC_EEG_data(:,12);
F8 = AC_EEG_data(:,13);
AF4 = AC_EEG_data(:,14);
time = AC_EEG_data(:,15);
display('Done.')

verbosity = 1;

ch1 = F7;	%blink and clench
ch2 = T7;	%clench only

result = blink_clench(ch1,ch2,time,verbosity);
display(result');

end

