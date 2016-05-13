close all;
clear;
clc;
%% SETUP
display('Welcome to NeuroPass Version 1.0');
display('What would you like to do:');
display('a) Set a new password.');
display('b) Authenticate against the existing password.');
str = input('Type either "a" or "b".\n','s');
if str == 'a'
    [filename,pathname] = uigetfile('.csv','Please enter the path to your file.');
    fullpath = strcat(pathname,filename);
    % str = input('Please enter the path to your file.','s');
    result = result_generator(fullpath);

    Opt.Method = 'SHA-1';
    password = DataHash(result, Opt);
    display('You have saved a new password:');
    display(password);
    clear;
elseif str == 'b'
    display('Please enter the path to your file.');
    % write some code
    display('Your file matches the current password!');
    display('Your file does not match the current password!');
    clear;
end