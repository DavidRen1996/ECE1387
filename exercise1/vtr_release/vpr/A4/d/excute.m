infile=importdata('d4.txt');

bbcost=infile(:,3);
temp=infile(:,1);
endfile=find(temp==0);
endfile=[0;endfile];
s=size(endfile);
o=endfile(2);
value=0;
deviation=0;
for i=1:1:s(1)-1
   % mean_value=mean(bbcost(endfile(i):endfile(i+1),3));
   mean_value=mean(bbcost(endfile(i)+1:endfile(i+1)));
   dvalue=std(bbcost(endfile(i)+1:endfile(i+1)));
   value=[value,mean_value];
   
   deviation=[deviation,dvalue];
end
fid=fopen('mean.txt','wt');
fprintf(fid,'%f/n',value);
fclose(fid);
fid=fopen('deviation.txt','wt');
fprintf(fid,'%f/n',deviation);
fclose(fid);