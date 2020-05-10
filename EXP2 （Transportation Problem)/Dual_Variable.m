function pos = Dual_Variable(A,price)
%以pos矩阵返回各个非基变量所在位置的位势
%A为初始解
    [m,n] = size(price);
    [I,J] = find(~isnan(A)); %找到基变量位置
    b = [0;price(sub2ind([m,n],I,J))]; %位势方程的右端项
    UV = zeros(m+n);
    UV(1,1) = 1; %假定v1等于0
    for i = 1:n+m-1
        UV(i+1, [I(i),J(i) + m]) = 1;
    end
    x = UV \ b; %求解方程组
    u = x(1:m);
    v = x(m + 1:end);
    [nI,nJ] = find(isnan(A)); %找到非基变量位置
    pos = zeros(m,n);
    for i = 1:length(nI)
        pos(nI(i),nJ(i)) = u(nI(i)) + v(nJ(i));
    end
    
    
    
    