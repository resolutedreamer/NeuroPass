function [ch1, ch2, time] = process_raw_data(input_path)
% process_raw_data Loads raw data from Emotiv CSV files into MATLAB

%% STEP 1) Convert the data
AC_EEG_data = convert_csv_to_mat(input_path);

%% Alt STEP 1) Load the data from saved file
%AC_EEG_data = load('AC_EEG_data.mat');

%% STEP 2) Seperate each channel
AF3  = AC_EEG_data(:,1);
F7   = AC_EEG_data(:,2);
F3   = AC_EEG_data(:,3);
FC5  = AC_EEG_data(:,4);
T7   = AC_EEG_data(:,5);
P7   = AC_EEG_data(:,6);
O1   = AC_EEG_data(:,7);
O2   = AC_EEG_data(:,8);
P8   = AC_EEG_data(:,9);
T8   = AC_EEG_data(:,10);
FC6  = AC_EEG_data(:,11);
F4   = AC_EEG_data(:,12);
F8   = AC_EEG_data(:,13);
AF4  = AC_EEG_data(:,14);
time = AC_EEG_data(:,15);
display('Done.')

%% STEP 3) Select channels of interest
ch1 = F7;	%blink and clench
ch2 = T7;	%clench only
end