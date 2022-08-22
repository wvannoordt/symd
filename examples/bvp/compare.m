clear
clc
close all

n = 100;
x = linspace(0,2*pi,n+2);
data = csvread('out.csv');
plot(x, sin(x))
hold on
plot(x, data);
legend('sol', 'data')