%code from http://www2.cs.siu.edu/~qcheng/Teaching%20Software/Matlab%20Tutorials.pdf

% data from wireless step 9 tutorial 
data_csv = csvread('/home/heisenberg/Documents/EngTelecom/9-Fase/ADS/wireless_udp_app.csv');
data = data_csv';

% samples length/number 
n = length(data); % *Line 1*
% degrees of freedom
nu = n - 1;

figure;  hold on;  % start an empty figure *Line 3*

# mean from csv data
mx_data=mean(data); % *Line 7*

# variância amostral
s_data = data-mx_data;
sem = sqrt(sum((s_data).^2)/(n-1));

#zcr=norminv(0.975,0,1);  % *Line 8 modificado codigo original*
zcr = tinv(0.975,nu); % *Line 8 modificado codigo original - T-Student*

me=zcr*sem; % margin of error,  *Line 10*

CI1= mx_data-me;    % lower CI bound *Line 11*
CI2= mx_data+me;   % upper CI bound *Line 12*

plot(i*ones(1,n), data, 'k.','markersize',10); % show points *Line 13*
plot(i*ones(1,2),[CI1, CI2],'r*','markersize',20) % show CI * Line 14*

xlabel('experiment number')  % *Line 20*
ylabel('observations ')  % *Line 21*
title(['95% CI:',num2str(mx_data,3),'\pm',num2str(me,3)]), shg % *Line 22*