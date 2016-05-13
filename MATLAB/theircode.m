input_data = csvread('C:\Users\Anthony\Desktop\ee13d\10clenches.CSV');

IIR_TC = 256;
EEG_data = input_data( : ,3:16 );
[rows columns]= size(EEG_data);
AC_EEG_data = zeros(rows, columns);

% back= EEG_data( 1, : );
% for r = 2 : rows
%     %back= (back * ( IIR_TC - 1 ) + EEG_data( r,:)) / IIR_TC;
%     AC_EEG_data( r,:) = EEG_data( r,:)- back;
%     
% end
for r = 1 : rows
    AC_EEG_data( r,:) = EEG_data( r,:)- 4000;    
end