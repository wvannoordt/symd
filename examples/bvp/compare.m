clear
clc
close all

n = 800;
lhs = -2*eye(n,n);
lhs(1:n-1,2:n) = lhs(1:n-1,2:n) + eye(n-1,n-1);
lhs(2:n,1:n-1) = lhs(2:n,1:n-1) + eye(n-1,n-1);
rhs = 1+zeros(n,1);
rhs = rhs/(n*n);
sol = lhs\rhs;
m = max(abs(sol));
data = dlmread('out.csv');
figure
plot(sol);
hold on
plot(data);