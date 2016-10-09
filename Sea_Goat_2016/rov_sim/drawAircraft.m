function drawAircraft(u)
pn = u(1);
pe = u(2);
pd = u(3);
ux = u(4);
vx = u(5);
wx = u(6);
phi = u(7);
theta = u(8);
psi = u(9);
p = u(10);
q = u(11);
r = u(12);

t = u(13);

persistent aircraftHandle

field_width = 10;

if isempty()
    [V, F, patchcolors] = spacecraftVFC;
    
    XYZ = rotate(V', phi, theta, psi);
    
    %XYZ = translate(V, pn, pe, pd);
    
    R = [...
        0, 1, 0;...
        1, 0, 0;...
        0, 0, -1;...
        ];
    
    V = R*XYZ;
    
    aircraftHandle = patch('Vertices', V', 'Faces', F, ...
        'FaceVertexCData', patchcolors,...
        'FaceColor', 'flat',...
        'EraseMode', mode);
end

if t==0
            figure(1), clf
            aircraftHandle = drawSpacecraftBody(pn, pe, pd, ...
                phi, theta, psi, [],'normal');
    
else
    aircraftHandle = drawSpacecraftBody(pn, pe, pd, ...
        phi, theta, psi, aircraftHandle,'normal');
end

function XYZ = rotate(XYZ,  phi, theta, psi)
R_roll = [...
    1, 0, 0; ...
    0, cos(phi), -sin(phi);...
    0, sin(phi), cos(phi)];
R_pitch = [...
    cos(theta), 0, sin(theta); ...
    0, 1, 0;...
    -sin(theta), 0, cos(theta)];

R_yaw = [...
    cos(psi), -sin(psi), 0; ...
    sin(psi), cos(psi), 0;...
    0, 0, 1];

R = R_roll * R_pitch * R_yaw;

XYZ = R * XYZ;
    