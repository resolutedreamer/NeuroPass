%% LOAD DATA
close all;
clc;
M = csvread('10clenches.csv');
EEG_data = M(:,3:16);

for i=1:length(M(:,1))
	time(i) = i;
end

time = time';

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


%%
d = fdesign.highpass('Fst,Fp,Ast,Ap',0.1,0.16,60,1, 128);
Hd = design(d,'butter');
F8_2 = filter(Hd,F8);

%%


clear d;
clear Hd;
clear EEG_data;
clear M;
clear i;