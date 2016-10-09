function [ g ] = calc_g( N, P )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

phi = N(4);
theta = N(5);
psi = N(6);

BGx = P.xg - P.xb;
BGy = P.yg - P.yb;
BGz = P.zg - P.zg;

W = P.m*P.g;

a = -BGy*W*cos(theta)*cos(phi) + BGz*W*cos(theta)*sin(phi);
b = BGz*W*sin(theta) + BGz*W*cos(theta)*cos(phi);
c = -BGx*W*cos(theta)*sin(phi) - BGy*W*sin(theta);

g = [ 0; 0; 0; a; b; c];
end

