test = F8;
% % HPF
%d = fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2',.5,1,19,20,60,1,60);
d = fdesign.highpass('Fst,Fp,Ast,Ap',0.00125,0.0013,60,1);
Hd = design(d,'equiripple');
% fvtool(Hd);
test = filter(Hd,test);
figure;
plot(test)
hold all;