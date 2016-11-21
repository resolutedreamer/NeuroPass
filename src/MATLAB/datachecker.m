%% get the input file
display('Importing CSV file.')
M = csvread('data\anthony-mixedtrial1-20.11.13.12.27.34.CSV',1);
EEG_data = M(:,3:16);
clear M;


M = csvread('data\anthony-mixedtrial2-20.11.13.12.32.34.CSV',1);
EEG_data_2 = M(:,3:16);
clear M;

figure;
plot(EEG_data(:,2));
figure;
plot(EEG_data_2(:,2));

%% remove the DC offset, code provided by Emotiv
IIR_TC = 256;
[rows, columns]= size(EEG_data); 
AC_EEG_data = zeros(rows, columns); 
back = EEG_data(1,:);
for r = 2 : rows
    back = (back*( IIR_TC- 1 ) + EEG_data( r,:)) / IIR_TC; 
    AC_EEG_data( r,:) = EEG_data( r,:)- back;
end

%% remove the DC offset, code provided by Emotiv
IIR_TC = 256;
[rows, columns]= size(EEG_data_2); 
AC_EEG_data_2 = zeros(rows, columns); 
back = EEG_data_2(1,:);
for r = 2 : rows
    back = (back*( IIR_TC- 1 ) + EEG_data_2( r,:)) / IIR_TC; 
    AC_EEG_data_2( r,:) = EEG_data_2( r,:)- back;
end

figure;
plot(AC_EEG_data(:,2));
figure;
plot(AC_EEG_data_2(:,2));
