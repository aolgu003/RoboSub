function [ thrust ] = T100_thruster_dynamics( pwm_in )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%data found by fitting the thruster data on blue robotics website
a=-51.348085781063;
b=0.10072267395657193;
c=-0.00006784574094879734;
d=1.5694002475642106e-8;

thrust = a + b*pwm_in + c*pwm_in.^2 + d*pwm_in.^3;

end