rad = 100;
del = 10;
[x, y] = meshgrid((-3*rad-del):(3*rad+del));
[rows, cols] = size(x);
dist = @(x, y, xc, yc) sqrt((x-xc).^2+(y-yc).^2);

p=0.005;


venn_img = zeros(rows, cols, 3);
venn_img(:,:,1) = 1 ./(1+(p.*(dist(x, y, rad.*cos(0), rad.*sin(0)))));
venn_img(:,:,2) = 1 ./(1+(p.*(dist(x, y, rad.*cos(2*pi/3), rad.*sin(2*pi/3)))));
venn_img(:,:,3) = 1 ./(1+(p.*(dist(x, y, rad.*cos(4*pi/3), rad.*sin(4*pi/3)))));

figure(1); clf
image(venn_img)
axis equal