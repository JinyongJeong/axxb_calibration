%AXXB - Batch Method (KL - Information Theoretic)

clear; clc; close all;


%Editable Variables
%------------------------------------------------------

num=500;	%Number of steps

gmean=[0;0;0;0;0;0];	%Gaussian Noise Mean

noise=0;	%Gaussian Noise standard deviation Range

shift=0; %step shift

n=1;      %VP(n)

window=0;    %target correlation area

model=1;        %noise model

ElipseParam=[10, 10, 10];

trials=10;


meanB=0.1*[randn(3,1); 5*randn(3,1)];
sdevB=0.1;


% t2=(0:(2*pi)/((num+shift)):2*pi);
% twist=0.0*sin(16*t2);
%------------------------------------------------------

%Computation Loops
%---------------------------------------------------------------------------------------------------------

A=[];
B=[];

RoterrorKLavg=[];
TranerrorKLavg=[];
RoterrorBSavg=[];
TranerrorBSavg=[];
RoterrorEDavg=[];
TranerrorEDavg=[];
RoterrorKronavg=[];
TranerrorKronavg=[];

% Mean=[0;0;0;0;0;0];
% Cov=0.1*eye(6,6);

% noise=0:(0.05-0)/3:0.05;

for i=1:length(noise)
    
    RoterrorKL=[];
    TranerrorKL=[];
    RoterrorBS=[];
    TranerrorBS=[];
    RoterrorED=[];
    TranerrorED=[];
    RoterrorKron=[];
    TranerrorKron=[];
    
    
    for j=1:trials
        %         [A, B]=AB_genRand(X, Mean, Cov, num);
        
        %         gap_size=1;
        x=[randn(3,1); randn(3,1)]; X=expm(se3_vec(x));   %Generate a Random X
        
        trajParam=[.5, .5, .5, 0, 0];
        [A1, B1]=AB_genTraj(X, ElipseParam, trajParam, num*0.5);
        
        trajParam=[.5, .5, .5, 0, 0.5*pi];
        [A2, B2]=AB_genTraj(X, ElipseParam, trajParam, num*0.5);
        
        A=cat(3,A1,A2);
        B=cat(3,B1,B1);

%         [A, B, X_new]=AB_genRandcov(X, 0, meanB, sdevB, num);
        
        waitbar(((i-1)*trials+(j-1))/(length(noise)*trials))
        
        A_noise=sensorNoise(A,gmean,noise(i),1);
        B_noise=B;
        
        A_noise=A_noise(:,:,1:(end-5));
        B_noise=B_noise(:,:,6:end);
        

        [X_batchKL,~,~,~,~]=batchKLSolve(A_noise, B_noise, X);     
        [X_batchBS,~,~,~,~]=batchBSSolve(A_noise, B_noise, X);
        [X_batchED,~,~,~,~]=batchEDSolve(X, A_noise, B_noise);
        [X_kron]=axb_KronSolve2(A_noise,B_noise);
        
        RoterrorKron=[RoterrorKron roterror(X_kron, X)]
        RoterrorKL=[RoterrorKL roterror(X_batchKL, X)]
        RoterrorBS=[RoterrorBS roterror(X_batchBS, X)]
        RoterrorED=[RoterrorED roterror(X_batchED, X)]
        TranerrorKron=[TranerrorKron tranerror(X_kron, X)]
        TranerrorKL=[TranerrorKL tranerror(X_batchKL, X)]
        TranerrorED=[TranerrorED tranerror(X_batchED, X)]
        TranerrorBS=[TranerrorBS tranerror(X_batchBS, X)]
        
        
        
        
        
    end
    
    RoterrorKLavg=[RoterrorKLavg mean(RoterrorKL)];
    TranerrorKLavg=[TranerrorKLavg mean(TranerrorKL)];
    RoterrorBSavg=[RoterrorBSavg mean(RoterrorBS)];
    TranerrorBSavg=[TranerrorBSavg mean(TranerrorBS)];
    RoterrorEDavg=[RoterrorEDavg mean(RoterrorED)];
    TranerrorEDavg=[TranerrorEDavg mean(TranerrorED)];
    RoterrorKronavg=[RoterrorKronavg mean(RoterrorKron)];
    TranerrorKronavg=[TranerrorKronavg mean(TranerrorKron)];
    
    
    
end

%----------------------------------------------------------------------------------------------------------------



hold on
figure;%(3)
scatter(noise, RoterrorBSavg, '+');
xlabel('Noise on the A and B sets')
ylabel('Rotation error of X')
hold on
scatter(noise, RoterrorKLavg, '.');
scatter(noise, RoterrorEDavg, 'x');
scatter(noise, RoterrorKronavg, 'o');
hold off
legend('BS Batch Method','KL Batch Method', 'ED Batch Method', 'Kronecker Product Method','Location', 'SouthOutside')

figure;%(4)
scatter(noise, TranerrorBSavg, '+');
xlabel('Noise on the A and B sets')
ylabel('Translation error of X')
hold on
scatter(noise,TranerrorKLavg, '.');
scatter(noise,TranerrorEDavg, 'x');
scatter(noise,TranerrorKronavg, 'o');
hold off
legend('BS Batch Method','KL Batch Method', 'ED Batch Method', 'Kronecker Product Method','Location', 'SouthOutside')




