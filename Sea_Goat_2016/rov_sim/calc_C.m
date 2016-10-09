function [ C ] = calc_C( vel,P )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

u = vel(1,1);
v = vel(2,1);
w = vel(3,1);
p = vel(4,1);
q = vel(5,1);
r = vel(6,1);

a = zeros([3 3]);

b = [0                  w*(P.m + P.Zdotw)        v*(-P.m + P.Ydotv);...
     w*(-P.m + P.Zdotw) 0                        u*(P.m + P.Xdotu) ;...
     v*(P.m + P.Ydotv)  u*(-P.m + P.Xdotu)       0                ];

c = [0                  w*(P.m - P.Zdotw)        v*(-P.m + P.Ydotv);...
     w*(-P.m + P.Zdotw) 0                        u*(P.m + P.Xdotu) ;...
     v*(P.m + P.Ydotv)  u*(-P.m + P.Xdotu)       0                ];
 
d = [0                    u*(-P.m + P.Xdotu)        q*(P.Iyy - P.Mdotq);...
     r*(-P.Izz + P.Ndotr) 0                         q*(P.Iyy + P.Mdotq);...
     q*(P.Iyy + P.Mdotq)  p*(-P.Ixx + P.Kdotp)      0                ];

C = [a b; c d];

end

