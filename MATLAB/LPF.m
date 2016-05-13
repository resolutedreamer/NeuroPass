function [ filtered_signal ] = LPF( original_signal, cutoff )
%Performs a "low-pass" filter function.
%   - orignal_signal must be a N*1 function
%   - cutoff must be > 0
%   - length(orignal_signal) must be > cutoff


% if (length(original_signal) < cutoff)
    % error('invalid signal/cutoff specified. check dimensions.')
% end

for i=1:length(original_signal)
    if i >= cutoff
        filtered_signal(i) = 0;
    else
        filtered_signal(i) = original_signal(i);
    end
end