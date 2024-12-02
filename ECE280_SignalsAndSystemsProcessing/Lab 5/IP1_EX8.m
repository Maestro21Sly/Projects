x = imread('TestCard.png');

h_box_blur = ones(21, 21)/441;

h_gauss = 1/256.*[1, 4, 6, 4, 1; 4, 16, 24, 16, 4; 6, 24, 36, 24, 6; 4, 16, 24, 16, 4; 1, 4, 6, 4,1];
h_sobel_x = [1 0 -1; 2 0 -2; 1 0 -1];
h_sobel_y =[1 2 1; 0 0 0; -1 -2 -1];
figure (1); clf
imagesc(x)
axis equal; 
title(' Original Test Card (sna31)')

y1(:,:,1)= conv2(x(:,:,1), h_sobel_y, 'valid');
y1(:,:,2)= conv2(x(:,:,2), h_sobel_y, 'valid');
y1(:,:,3)= conv2(x(:,:,3), h_sobel_y, 'valid');

y2(:,:,1)= conv2(x(:,:,1), h_sobel_x, 'valid');
y2(:,:,2)= conv2(x(:,:,2), h_sobel_x, 'valid');
y2(:,:,3)= conv2(x(:,:,3), h_sobel_x, 'valid');
t = sqrt((y1).^2 + (y2).^2);

figure (2); clf
imagesc(uint8(t))
axis equal; 
title(' Sobel Edges Test Card (sna31)')