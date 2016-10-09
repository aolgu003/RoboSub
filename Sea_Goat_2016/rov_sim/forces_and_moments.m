function [ tau ] = forces_and_moments( m1, m2, m3, m4, P )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

F1 = round(P.t100_data(m1),2);
F2 = round(P.t100_data(m1),2);
F3 = round(P.t100_data(m1),2);
F4 = round(P.t100_data(m1),2);

tau = [1 1 0 0; 0 0 1 0; 0 0 0 1; 0 0 -P.zF3 P.zF4; P.zF1 P.zF2 0 -P.xF4;...
    -P.yF1 -P.yF2 P.xF3 0] *  [F1; F2; F3; F4];

end