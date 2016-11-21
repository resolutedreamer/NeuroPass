function loaddata(input)
%% get the input file
display('Importing CSV file.')
M = csvread(input,1);
EEG_data = M(:,3:16);
clear M;
display('CSV file successfully imported.')
%% remove the DC offset, code provided by Emotiv
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
title('Orignial signal and Low Pass Filtered data (@.178 Hz)');
plot(EEG_data(:,2));
plot(AC_EEG_data(:,2));

% AC_EEG_data = EEG_data;
%% add time column back in
for i=1:length(AC_EEG_data(:,1))
	time(i) = i;
end
time = time';
AC_EEG_data(:,15) = time;
%% output the resulting file
save('AC_EEG_data.mat', 'AC_EEG_data')
display('AC_EEG_data.mat successfully created.')
end