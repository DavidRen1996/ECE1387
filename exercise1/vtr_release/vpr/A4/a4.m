infile=importdata('A4result.txt');
bbcost=infile(:,2);
mvalue=0;
deviation=0;
for i=1:5:20
    mean_value=mean(bbcost(i:i+4));
    mvalue=[mvalue,mean_value];
    dvalue=std(bbcost(i:i+4));
    deviation=[deviation,dvalue];
end

fid=fopen('mean.txt','wt');
fprintf(fid,'%f/n',mvalue);
fclose(fid);
fid=fopen('deviation.txt','wt');
fprintf(fid,'%f/n',deviation);
fclose(fid);