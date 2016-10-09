J = imread('../../image_data_set/Competition/lastRunFirstDayCompetition/_Recordings_/Front/Image143.png');

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
t_R = 1-Jdark./double(atmosphere_R);
t_B = 1-Jdark./double(atmosphere_B);
t_G = 1-Jdark./double(atmosphere_G);
t = min([t_R t_B t_G]);


% subplot(1,2,2);
% imshow(t);
% 
Jdehz(:,:,1) = (mat2gray(I(:,:,1)) - double(atmosphere_R))./mat2gray(t_R)...
    + double(atmosphere_R);
Jdehz(:,:,2) = (mat2gray(I(:,:,2)) - double(atmosphere_G))./mat2gray(t_B)...
    + double(atmosphere_G);
Jdehz(:,:,3) = (mat2gray(I(:,:,3)) - double(atmosphere_B))./mat2gray(t_G)...
    + double(atmosphere_B);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
figure(1)
subplot(1,2,1)
imshow(I)

subplot(1,2,2)
imshow(Jdehz)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2)
%subplot(1,3,1)
%mshow(mat2gray(Jdark));

subplot(1,3,1)
imshow(mat2gray(t_R));

subplot(1,3,2)
imshow(mat2gray(t_G));

subplot(1,3,3)
imshow(mat2gray(t_B));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(3)
subplot(2,3,4)
imshow(Jdehz(:,:,1))

subplot(2,3,5)
imshow(Jdehz(:,:,2))

subplot(2,3,6)
imshow(Jdehz(:,:,3))


subplot(2,3,1)
imshow(I(:,:,1))

subplot(2,3,2)
imshow(I(:,:,2))

subplot(2,3,3)
imshow(I(:,:,3))
