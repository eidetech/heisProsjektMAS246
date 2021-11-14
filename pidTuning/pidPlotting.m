clc; clear all; close all;

fileID = fopen('pidTuning2.txt','r');

formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA)
A = A'

x = 1:length(A(:,1));

plot([0, length(A)],[400 400])
hold on
plot(x, A(:,2))
ylim([350 500])