function [ curve ] = untitled2( filename )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


data = xlsread(filename);
[curve, goodness, output] = fit(data(:,1), data(:,2), 'smoothingspline');
end

