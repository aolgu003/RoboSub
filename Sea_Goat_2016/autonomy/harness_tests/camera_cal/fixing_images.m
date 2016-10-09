files = dir;

for i = 3:length(files)-1
    file_name = files(i).name;
    
    if i == 3
        I = imread(file_name);
        prev = I;
    else
        I = imread(file_name);
    end
    
    if size(I,1) ~= size(prev,1)
        prev(:,:,1) = I(:,:,1)';
        prev(:,:,2) = I(:,:,2)';
        prev(:,:,3) = I(:,:,3)';
    end
    
    imwrite(prev,file_name)
    size(prev)
end