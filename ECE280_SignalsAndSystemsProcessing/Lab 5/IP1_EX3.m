tc = linspace(0, 1, 101);
xc = humps(tc);
td = linspace(0, 1, 11);
xd = humps(td);

h = [0.5 0.5];
y2 = conv(xd, h, 'same');

h5= [0.2 0.2 0.2 0.2 0.2];
y5 = conv(xd, h5, 'same');

figure (1); clf
plot(tc, xc, 'b-')
hold on

plot(td, xd, 'bo')
hold on

plot(td, y2, 'r-o')
hold on

plot(td, y5, 'g-o')
hold off

