close all;
clear;
clc;
%% STEP 1) CHOOSE USAGE MODE
display('Welcome to NeuroPass Version 1.0');
display('What would you like to do:');
display('a) Set a new password.');
display('b) Authenticate against the existing password.');
str = input('Type either "a" or "b".\n','s');

%% STEP 2) LOAD THE FILE
[filename,pathname] = uigetfile('.csv','Please enter the path to your file.');
fullpath = strcat(pathname,filename);

%% STEP 3) PROCESS THE FILE
event_sequence = process_raw_data(fullpath);

%% GET FILE HASH
% SHA-1 broken
Opt.Method = 'SHA-256';
% DataHash https://www.mathworks.com/matlabcentral/fileexchange/31272-datahash?requestedDomain=www.mathworks.com
password = DataHash(event_sequence, Opt);

%% STEP 4) RUN EXPECTED USAGE MODE
if str == 'a'
    % Save the hash of the password, i.e. the golden keys. Never lose this.
    save('password.mat', password)
    display('You have saved a new password:');
    display(password);
    display('You should delete the input file immediately to preserve security.');
    clear;
elseif str == 'b'
    % load the stored password
    storedpassword = load('password.mat')    
    % verify the match
    if (password == storedpassword)
    end
    % display the result
    if (match)
        display('Your file matches the current password!');
    else
        display('Your file does not match the current password!');
    end
    clear;
end