function [ D ] = calc_D( vel, P )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
u = vel(1,1);
v = vel(2,1);
w = vel(3,1);
p = vel(4,1);
q = vel(5,1);
r = vel(6,1);

a = P.Xu + P.Xuu*abs(u);
b = P.Yv + P.Yvv*abs(v);
c = P.Zww*abs(w);
d = P.Kp + P.Kpp*abs(p);
e = P.Mq + P.Mqq*abs(q);
f = P.Nr + P.Nrr*abs(r);

D = -diag([a b c d e f]);
end

