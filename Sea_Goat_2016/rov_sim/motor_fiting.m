filename = 'T100_motor_data.xlsx';

data = xlsread(filename);
[curve, goodness, output] = fit(data(:,1), data(:,2), 'smoothingspline');

plot(curve, data(:,1), data(:,2))