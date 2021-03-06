%AXXB - Batch Method Noise

clear; clc; close all;


%Editable Variables
%------------------------------------------------------

num=210;	%Number of steps

gmean=[0;0;0;0;0;0];	%Gaussian Noise Mean

noise=(0:0.1:0.1);	%Gaussian Noise standard deviation Range

shift=0; %step shift

model=1;        %noise model

ElipseParam=[10, 10, 10];

trials=3;

%------------------------------------------------------







x=randn(6,1); X=expm(se3_vec(x));   %Generate a Random X


%Computation Loops
%---------------------------------------------------------------------------------------------------------

RoterrorKL=[];
TranerrorKL=[];
RoterrorBS=[];
TranerrorBS=[];
RoterrorED=[];
TranerrorED=[];
RoterrorKron=[];
TranerrorKron=[];

h = waitbar(0,'Computing...');

for i=1:size(noise)
    
    for k=1:trials
        
        A=[];
        B=[];
        
        trajParam=[.5, .5, .5, 0, 0];
        [A1, B1]=AB_genTraj(X, ElipseParam, trajParam, num/3);
        
        trajParam=[.5, .5, .5, 0, 0.5*pi];
        [A2, B2]=AB_genTraj(X, ElipseParam, trajParam, num/3);
        
        trajParam=[.5, .5, .5, 0, pi];
        [A3, B3]=AB_genTraj(X, ElipseParam, trajParam, num/3);
        
        A=cat(3, A1, A2, A3);
        B=cat(3, B1, B2, B3);
        
        
        A=sensorNoise(A,[0;0;0;0;0;0],noise(i),1);
        
        
        [X_solved(:,:,1), MA, MB, SigA, SigB]=batchEDSolve(A,B);
        
        SigX(:,:,1)=SigXcalc(SigA, MB, SigB, X_solved(:,:,1));
        
        
        C=norm(SigX(:,:,1))^2;
        C_old=inf;
        ind=1;
        
        diff=0.0000000001; eps=0.001;
        E(:,:,1)=[0 0 0 0; 0 0 -1 0; 0 1 0 0; 0 0 0 0]; E(:,:,2)=[0 0 1 0; 0 0 0 0; -1 0 0 0; 0 0 0 0]; E(:,:,3)=[0 -1 0 0; 1 0 0 0; 0 0 0 0; 0 0 0 0];
        E(:,:,4)=[0 0 0 1; 0 0 0 0; 0 0 0 0; 0 0 0 0]; E(:,:,5)=[0 0 0 0; 0 0 0 1; 0 0 0 0; 0 0 0 0]; E(:,:,6)=[0 0 0 0; 0 0 0 0; 0 0 0 1; 0 0 0 0];
        E(:,:,7:12) = -E(:,:,1:6);
        
        
        while(abs(C(ind)-C_old)>diff)
            C_old=C(ind);
            ind=ind+1;
            Cset=zeros(12,1);
            
            for j=1:12
                
                Xnew(:,:,j)=X_solved(:,:,ind-1)*expm(eps*E(:,:,j));
                
                SigX_set(:,:,j)=SigXcalc(SigA, MB, SigB, Xnew(:,:,j));
                
                Cset(j)=norm(SigX_set(:,:,j))^2;
                
            end
            
            [C_temp, indx]=min(Cset);
            C(ind)=C_temp;
            
            if C(ind)<C_old
                X_solved(:,:,ind)=Xnew(:,:,indx);
                SigX(:,:,ind)=SigX_set(:,:,indx);
            else
                break;
            end
            
            X_roterror(k,ind-1)=roterror(X_solved(:,:,ind),X);
            X_tranerror(k,ind-1)=tranerror(X_solved(:,:,ind),X);
            
        end
        
        X_meanroterror=mean(X_roterror,1);
        X_meantranerror=mean(X_tranerror,1);
        
        waitbar(k / trials)
        
    end
    
end
close(h);

% roterror(X_solved(:,:,1),X)
% roterror(X_solved(:,:,ind-1),X)
% tranerror(X_solved(:,:,1),X)
% tranerror(X_solved(:,:,ind-1),X)

figure(1);
plot(X_meanroterror)
figure(2);
plot(X_meantranerror)

figure(3);
hold on
plot(X_roterror(1,:),'k')
% plot(X_roterror(2,:), 'b')
% plot(X_roterror(3,:), 'r')
% plot(X_roterror(4,:), 'g')
% plot(X_roterror(5,:), 'y')
hold off
figure(4);
hold on
plot(X_tranerror(1,:))
% plot(X_tranerror(2,:))
% plot(X_tranerror(3,:))
% plot(X_tranerror(4,:))
% plot(X_tranerror(5,:))

figure(5);
plot(C)




%---------------------------------------------------------------------------------------------------------


