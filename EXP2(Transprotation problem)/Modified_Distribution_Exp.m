function Modified_Distribution()        %运费最小
clc
clear
format short

 price=[0 1 3 2 1 4 3 3 11 3 10
        1 0 1000 3 5 1000 2 1 9 2 8
        3 1000 0 1 1000 2 3 7 4 10 5
        2 3 1 0 1 3 2 2 8 4 6
        1 5 1000 1 0 1 1 4 5 2 7
        4 1000 2 3 1 0 2 1 8 2 4
        3 2 3 2 1 2 0 1 1000 2 6
        3 1 7 2 4 1 1 0 1 4 2
        11 9 4 8 5 8 1000 1 0 2 1
        3 2 10 4 2 2 2 4 2 0 3
        10 8 5 6 7 4 6 2 1 3 0];
 prod=[27 24 29 20 20 20 20 20 20 20 20]';
 sell=[20 20 20 20 20 20 20 23 26 25 26];
%M=10000;

%price =[4 12 4 11;
%        2 10 3 9;
%        8 5 11 6];
%prod=[16 10 22]';
%sell=[8 14 12 14];
    
%price =[-4 5 3 2 M;
%         5 -1 2 M 4;
%         3 2 -2 5 5;
%         2 M 5 -3 6;
%         M 4 5 6 -5];
%prod = [40 80 50 50 50]';
%sell = [30 40 50 80 70];

%price =[-1 M 3 8 M;
%         M -1 2 M 9;
%         3 3 -1 2 5;
%         8 M 3 -1 M;
%         M 9 5 M -1];
%prod = [80 70 50 50 50];
%sell = [50 50 50 70 80];

[m,n]=size(price);
A=init(length(prod),length(sell));
A=Vogel_method(A,price,prod,sell,m,n);

pos=Dual_Variable(A,price)
judge=Check_Sigma(pos,price)
[min1,row1]=min(judge);        %每列中的judge的最小值
[min2,col1]=min(min1);

times=1;
 while min2<0
     fprintf('%s%d%s\n','第',times,'次迭代')
    i=row1(col1);j=col1;
    [result,point1,point2]=Find_Close_Path(A,i,j);     
    A=Adjust_Distribution(A,point1,point2)
    pos=Dual_Variable(A,price)
    judge=Check_Sigma(pos,price)
    [min1,row1]=min(judge);        %每列中的judge的最小值
    [min2,col1]=min(min1);

    times=times+1;
    if times>100
        break;
    end
 end
 A
 total_cost=Cal_Cost(A,price)
        
        
                
function A=init(m,n)                %初始化
    for i=1:m
        for j=1:n
            A(i,j)=nan;
        end
    end
    
function total_cost=Cal_Cost(A,price)
    [m,n]=size(A);
    for i=1:m
        for j=1:n
            if isnan(A(i,j))
                A(i,j)=0;
            end
        end
    end
    temp=A.*price;
    total_cost=sum(temp(:));

function A=Adjust_Distribution(A,point1,point2)
    [p_min,index]=min(point1(:,3));
    point1(:,3)=point1(:,3)-p_min;
    point2(:,3)=point2(:,3)+p_min;

    for k=1:length(point1(:,1))
        A(point1(k,1),point1(k,2))=point1(k,3);
    end

    for k=1:length(point2(:,1))
        A(point2(k,1),point2(k,2))=point2(k,3);
    end
    A(point1(index,1),point1(index,2))=nan;
    
