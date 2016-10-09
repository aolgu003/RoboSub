I = imread('/home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/image_data_set/Competition/CompetitionRuns2/_Recordings_/Front/Image377.png');
    
Jdehz = dehazing_func(I);

figure(1)
subplot(1,2,1)
imshow(I)

subplot(1,2,2)
imshow(Jdehz)
drawnow