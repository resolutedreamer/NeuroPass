close all;
clear;
clc;
%% CHOOSE USAGE MODE
display('Welcome to NeuroPass Version 1.0');
display('What would you like to do:');
display('a) Set a new password.');
display('b) Authenticate against the existing password.');
str = input('Type either "a" or "b".\n','s');

%% LOAD THE FILE
[filename,pathname] = uigetfile('.csv','Please enter the path to your file.');
fullpath = strcat(pathname,filename);

%% PROCESS THE FILE
result = result_generator(fullpath);

%% RUN EXPECTED USAGE MODE
if str == 'a'
    Opt.Method = 'SHA-1';
    password = DataHash(result, Opt);
    display('You have saved a new password:');
    display(password);
    save('password.mat',password)
    clear;
elseif str == 'b'
    % load the stored password
    load('password.mat')
    % check the hash of the current file
    Opt.Method = 'SHA-1';
    password = DataHash(result, Opt);
    % verify the match
    if (password == storedpassword)
    end
    %display the result
    if (match)
        display('Your file matches the current password!');
    else
        display('Your file does not match the current password!');
    end
    clear;
end