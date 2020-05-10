function judge = Check_Sigma(pos,price)
    [m,n] = size(price);
    [nI,nJ] = find(pos ~= 0); %找到非基变量位置
    judge = zeros(m,n);
    for i = 1:length(nI)
        judge(nI(i),nJ(i)) = price(nI(i),nJ(i)) - pos(nI(i),nJ(i));
    end