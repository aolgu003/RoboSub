function [ Jdehz ] = dehazing_func( J )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
I = (padarray(J,[8 8],255,'both'));
Igray = rgb2gray(I);

Jdark = zeros(size(I(:,:,1)));
Jdark = im2double(Jdark);

for i=8:size(I(:,:,1),1)-8
    for j=8:size(I(:,:,1),2)-8
        val = min(min(min(I(i-7:i+7, j-7:j+7, :))));
        if val > 0
            Jdark(i,j) = val;
        end
    end
end

Jdark = mat2gray(Jdark);
sortedJdark = sort(Jdark(:), 'descend');

numPix = round(.001 * size(Jdark,1) * size(Jdark,2));
thresh = sortedJdark(numPix);
mask = im2bw(mat2gray(Jdark), thresh);

atmosphere_R =  double(max(max(uint8(mask) .* I(:,:,1))))/255;
atmosphere_G =  double(max(max(uint8(mask) .* I(:,:,2))))/255;
atmosphere_B =  double(max(max(uint8(mask) .* I(:,:,3))))/255;



% t = 1 - Jdark;
t_tilde(:,:,1) = Jdark./double(atmosphere_R);
t_tilde(:,:,2) = Jdark./double(atmosphere_B);
t_tilde(:,:,3) = Jdark./double(atmosphere_G);
t = 1-min(t_tilde,[],3);


% subplot(1,2,2);
% imshow(t);
% 
Jdehz(:,:,1) = (mat2gray(I(:,:,1)) - double(atmosphere_R))./mat2gray(t)...
    + double(atmosphere_R);
Jdehz(:,:,2) = (mat2gray(I(:,:,2)) - double(atmosphere_G))./mat2gray(t)...
    + double(atmosphere_G);
Jdehz(:,:,3) = (mat2gray(I(:,:,3)) - double(atmosphere_B))./mat2gray(t)...
    + double(atmosphere_B);

end

