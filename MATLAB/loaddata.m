function loaddata(input, mode)
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
%% if mode == 2, then we want to run the filter i made previously on the data too
if mode==2
    %% prepare the DC removing filter for use
    display('Preparing Anthonys Filter.')
    d = fdesign.highpass('Fst,Fp,Ast,Ap',0.1,0.16,60,1, 128);
    Hd = design(d,'butter');
    fvtool(Hd)
    %% normalize the data 
%     simple normalizing
%     for i=1:14 
%         to_normalize = AC_EEG_data(:,i);
%         normalized = ( to_normalize - (.5*(max(to_normalize)+min(to_normalize))) ) / (.5*( max(to_normalize) - min(to_normalize) )); %normalize between -1 and 1
%         AC_EEG_data(:,i) = normalized;
%     end
%     clear to_normalize;
%     clear normalized;
%     display('Data succesfully normalized')
    %% run the filter on the normalized data
    display('Running Anthonys Filter.')
    for i=1:14
        to_filter = AC_EEG_data(:,i);
        filtered = filter(Hd,to_filter);
        AC_EEG_data(:,i) = filtered;
    end
end
%% add time back in
for i=1:length(AC_EEG_data(:,1))
	time(i) = i;
end
time = time';
AC_EEG_data(:,15) = time;
%% output the resulting file
save('AC_EEG_data.mat', 'AC_EEG_data')
display('AC_EEG_data.mat sucessfully created.')
end