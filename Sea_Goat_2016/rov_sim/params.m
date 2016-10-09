P.pn0 = 0;
P.pe0 = 0;
P.pd0 = 0;
P.u0 = 0;
P.v0 = 0;
P.w0 = 0;
P.phi0 = 0;
P.theta0 = 0;
P.psi0 = 0;
P.p0 = 0;
P.q0 = 0;
P.r0 = 0;

P.m = 98.5;
P.rho = 1024;
P.g = 9.81;

%Hydro Dynamic Properties
P.Xu = -72;
P.Yv = -77;
P.Zw = -95;

P.Kp = -40;
P.Mq = -30;
P.Nr = -30;

P.Xdotu = -29;
P.Ydotv = -30;
P.Zdotw = -90;

P.Kdotp = -5.2;
P.Mdotq = -7.2;
P.Ndotr = -3.3;

P.Xuu = 0;
P.Yvv = 0;
P.Zww = 0;

P.Kpp = 0;
P.Mqq = 0;
P.Nrr = 0;

%Moments of intertia
P.Ixx = 1.32;
P.Iyy = 2.08;
P.Izz = 2.32;

P.Ixy = 0;
P.Iyx = 0;
P.Izx = 0;

P.Ixz = 0;
P.Izy = 0;
P.Iyz = 0;

%Center of gravity
P.xg = 0;
P.yg = 0;
P.zg = 0;

%center of Buoyancy
P.xb = 0;
P.yb = 0;
P.zb = -.1;

%Thrusters
P.xF1 = 0;
P.yF1 = -.175;
P.zF1 = -.1;

P.xF2 = 0;
P.yF2 = .215;
P.zF2 = -.1;

P.xF3 = .135;
P.yF3 = 0;
P.zF3 = .07;

P.xF4 = -.022;
P.yF4 = 0;
P.zF4 = 0;

P.M = diag([P.m-P.Xdotu  P.m-P.Ydotv  P.m-P.Zdotw  P.Ixx-P.Kdotp ...
    P.Iyy-P.Mdotq  P.Izz-P.Ndotr]);

P.t100_data = fit_data('T100_motor_data.xlsx');

%P.T100_dynamics = 
%P.T200_dynamics

