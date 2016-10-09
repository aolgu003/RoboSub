function [ thrust ] = T200_thruster_dynamics( pwm_in )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%data found by fitting the thruster data on blue robotics website
a=-222.53779238641638;
b=0.4201917846987441;
c=-0.0002746228555423721;
d=6.228984820829549e-8;

thrust = a + b*pwm_in + c*pwm_in.^2 + d*pwm_in.^3;

end

