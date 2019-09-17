infile=importdata('newb2.txt');
y1=[0.1 0.5 1 1.5];
y2=[0.5 1 2 10];
y3=[0.5 2 5 8];
y4=[2 5 8 15];
figure(1)
for ii=1:4:16
    plot(y1,infile(ii:ii+3));
    hold on;
end
figure(2)
for ii=17:4:32
    plot(y1,infile(ii:ii+3));
    hold on;
end
figure(3)
for ii=33:4:48
    plot(y1,infile(ii:ii+3));
    hold on;
end
figure(4)
for ii=49:4:64
    plot(y1,infile(ii:ii+3));
    hold on;
end
