function A=Vogel_method(A,price,prod,sell,m,n)
%用矩阵A返回初始运输方案，空格处数值为0
    H = ones(1, m+n);%标记此[行，列]是否已满足分配条件
    while any(H) 
        C = col_row_Difference(price,m,n);
        temp = -inf;
        %找到所有行列中最大的差额
        for i = 1:m+n
            if temp < C(i) && C(i) ~= -inf
                temp = C(i);
                v = i; %记录最大差额的位置
            end
        end
        %若v是最大行差额
        if v <= m
            price(price == -inf) = inf;
            [~,index] = min(price(v,:)); %找到最小运价和下标
            price(price == inf) = -inf;
            A(v,index) = min(sell(index),prod(v)); %确定运量
            prod(v) = prod(v) - A(v,index); %更新产量
            sell(index) = sell(index) - A(v,index);%更新销量
            % 判断否可以划掉一行（产量耗尽）
            if prod(v) == 0
                H(v) = 0;%此行已满足分配条件
                price(v,:) = [-inf];
            end
            % 判断是否可以划掉一列（销量耗尽）
            if sell(index) == 0
                H(m + index) = 0;%此行已满足分配条件
                price(:,index) = [-inf];
            end
        end
        %若v是最大列差额
        if v > m
            price(price == -inf) = inf;
            [~,index] = min(price(:,v - m)'); %最小值不能为-inf
            price(price == inf) = -inf;
            A(index, v - m) = min(prod(index),sell(v - m));
            prod(index) = prod(index) - A(index, v-m);
            sell(v - m) = sell(v - m) - A(index, v-m);
            if prod(index) == 0
                H(index) = 0;
                price(index,:) = [-inf];
            end
            if sell(v - m) == 0
                H(v) = 0;
                price(:,v - m) = [-inf];
            end
        end
        %矩阵同行或同列只有一个元素
        [I,J] = find(~isnan(A));
        if C == -inf
            %基变量数目不足时添加0
            if size(I) ~= m+n-1
                [x,y] = finding(A);
                A(x,y) = min(prod(x),sell(y));
                H = zeros(1,m + n);
            end
        end
        
    end
        
function B = col_row_Difference(A,m,n) 
%计算[行差额,列差额]
%对于m*n的矩阵，返回1行m+n列的矩阵记录行差额与列差额
    
    %计算行差额
    %先找到最小的两个运价
    for i = 1:m
        temp1 = inf;
        temp2 = inf;
        h = i;
        for j = 1:n
            if temp1 > A(i,j) && A(i,j) ~= -inf
                temp1 = A(i,j)
                h = j;%记录列位置
            end
        end
        flag = 0 %判断是否结束寻找
        for j = 1:n
            if temp2 > A(i,j) && (j ~= h) && A(i,j) ~= -inf
                temp2 = A(i,j);
                flag = 1
            end
        end
        if flag == 1
            B(i) = temp2 - temp1;
        else
            B(i) = -inf;% 当只有一个元素时差额为-inf
        end
    end
    
    %再计算列差额
    for i = 1:n
        temp1 = inf;
        temp2 = inf;
        k = i;
        for j = 1:m
            %k = 0; %初始化k值
            if temp1 > A(j,i) && A(j,i) ~= -inf
                temp1 = A(j,i);
                k = j;%记录行位置
            end
        end
        flag =0;
        for j = 1:m
            if temp2 > A(j,i) && (j ~= k) && A(j,i) ~= -inf
                temp2 = A(j,i);
                flag = 1;
            end
        end
        if flag ==1
            B(m+i)=temp2-temp1;
        else
            B(m+i)=-inf;% 当只有一个元素时差额为-inf
        end
    end        
        
        
function [x,y] = finding(A)
%当一行或一列剩下最后一个元素时，找到矩阵中的非负元素并返回下标
    [m,n] = size(A);
    for i = 1:m
        for j = 1:n
            if A(i,j)~=-inf
                x = i;
                y = j;
                break
            end
        end
    end        
        
        
            