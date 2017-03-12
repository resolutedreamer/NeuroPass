function AC_EEG_data = convert_csv_to_mat(input)
% convert_csv_to_mat Take a CSV file as input, and export the result as AC_EEG_data.mat
%   Also applies the IIR HPF (Low Pass Filter)

%% STEP 1) Load the input file
display('Importing CSV file.')
M = csvread(input,1);
EEG_data = M(:,3:16);
clear M;
display('CSV file successfully imported.')
%% STEP 2) Perform IIR Filtering (HPF)
% Necessary to remove the DC offset; code provided by Emotiv
IIR_TC = 256;
[rows, columns]= size(EEG_data); 
AC_EEG_data = zeros(rows, columns); 
back = EEG_data(1,:);
for r = 2 : rows
    back = (back*( IIR_TC- 1 ) + EEG_data( r,:)) / IIR_TC; 
    AC_EEG_data( r,:) = EEG_data( r,:)- back;
end
figure;
hold all;
title('Original signal and Low Pass Filtered data (@.178 Hz)');
plot(EEG_data(:,2));
plot(AC_EEG_data(:,2));

%% STEP 3) Reintroduce Timing Data
time = linspace(1, length(AC_EEG_data(:,1)), length(AC_EEG_data(:,1)));
time = time';
AC_EEG_data(:,15) = time;
%% OPTIONAL STEP 4) Save the resulting file
%save('AC_EEG_data.mat', 'AC_EEG_data')
%display('AC_EEG_data.mat successfully created.')
end