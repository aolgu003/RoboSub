path = uigetdir('../../image_data_set');
start_img = inputdlg('Enter starting image number i.e. 301 or 5 etc');
files = dir(path);

for k=3:length(files)
    filename = [path '/' files(k).name];
    I = imread(filename);
    
    Jdehz = dehazing_func(I);
    k
    files(k).name
    figure(1)
    subplot(1,2,1)
    imshow(I)
    
    subplot(1,2,2)
    imshow(Jdehz)
    drawnow
end
