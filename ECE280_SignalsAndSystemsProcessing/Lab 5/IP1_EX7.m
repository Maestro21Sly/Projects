x = imread('coins.png');

h = 1/256.*[1, 4, 6, 4, 1; 4, 16, 24, 16, 4; 6, 24, 36, 24, 6; 4, 16, 24, 16, 4; 1, 4, 6, 4,1];
h_x = [-1 0 1; -1 0 1; -1 0 1];
h_y =[-1 -1 -1; 0 0 0; 1 1 1];
h_new =[-1 -1 -1; -1 8 -1; -1 -1 -1];

CoinsEdgeY = conv2(x,h_y, 'valid');
CoinsEdgeX = conv2(x,h_x, 'valid');
Coin_New = conv2(x, h_new, 'valid');

t = sqrt((CoinsEdgeY).^2 + (CoinsEdgeX).^2);
figure (1); clf
image(x)
axis equal; colormap gray; colorbar
title('Original')
figure (2); clf
imagesc(Coin_New)
axis equal; colormap gray; colorbar
title('Alternate Coin Edges (sna31)')