function [ J ] = calc_J( n )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
phi = n(4);
theta = n(5);
psi =  n(6);

cphi = cos(phi);
sphi = sin(phi);

ctheta = cos(theta);
stheta = sin(theta);
ttheta = tan(theta);

cpsi = cos(psi);
spsi = sin(psi);

R = [ cpsi*ctheta -spsi*cphi+cpsi*stheta*sphi -spsi*sphi+cpsi*cphi*stheta;... 
      spsi*ctheta cpsi*cphi+sphi*stheta*spsi  -cpsi*sphi+stheta*spsi*cphi;...
      -stheta     ctheta*sphi                 ctheta*cphi               ];
T = [ 1     sphi*ttheta     cphi*ttheta; ...
      0     cphi            -sphi; ...
      0     sphi/ctheta     cphi/ctheta ];

J = [R zeros([3 3]); zeros([3 3]) T];

end

