import re
import numpy as np
import heapq


# 读入数据
pattern = re.compile(r'[-]?\d+')
#pattern = re.compile(r'^-?[1-9]\d*$')
with open('C:/Users/mi/Desktop/test1.txt') as f:
    max_bool = int(f.readline()) #{max:1, min:0}
    c = [int(x) for x in pattern.findall(f.readline())]#目标函数系数
    dims = [int(x) for x in pattern.findall(f.readline())] #约束矩阵维数
    constrain_rows = dims[0]  #约束条件个数
    constrain_cols = dims[1] #约束变量个数 
    inequity_index = dims[1] #b所在位置
    A = [] #系数矩阵
    b = [] #约束右端
    equal = [] #约束条件符号
    for i in range(constrain_rows):
        line = [int(x) for x in pattern.findall(f.readline())]
        A.append(line[0:constrain_cols])
        b.append(line[dims[1]])
        equal.append(line[-1])
    A = np.array(A)

# 返回矩阵的第j列
def column(A, j):
   return [row[j] for row in A]

# 转置
def transpose(A):
   return [column(A, j) for j in range(len(A[0]))]


# 判断此列对应的变量是否是基变量 [0,0,0,.....,1]
def isPivotCol(col):
   return (len([c for c in col if c == 0]) == len(col) - 1) and sum(col) == 1


# 根据列找到此列对应的基变量对应的值b
def variableValueForPivotColumn(tableau, column):
   pivotRow = [i for (i, x) in enumerate(column) if x == 1][0]
   return tableau[pivotRow][-1]


# 初始解生成
def primalSolution(tableau):
   # the pivot columns denote which variables are used
   columns = transpose(tableau)
   # 找到可以作为初始可行解的变量
   indices = [j for j, col in enumerate(columns[:-1]) if isPivotCol(col)]
   return [(colIndex, variableValueForPivotColumn(tableau, columns[colIndex])) for colIndex in indices]
   # 返回初始解
   # 形式为 [(3, 1200), (4, 3000), (5, 1500)] (变量编号， 值)

def objectiveValue(tableau):
   return -(tableau[-1][-1])


def canImprove(tableau):
   lastRow = tableau[-1]
   return any(x > 0 for x in lastRow[:-1])



# this can be slightly faster
# 判断检验数是否有两个及以上的最小值
def moreThanOneMin(L):
   if len(L) <= 1:
      return False
   x,y = heapq.nsmallest(2, L, key=lambda x: x[1])
   return x == y



# 找到换基组合
def findPivotIndex(tableau):
   # pick minimum positive index of the last row
   column_choices = [(i,x) for (i,x) in enumerate(tableau[-1][:-1]) if x > 0]
   # 找到最大检验数对应的下标
   column = max(column_choices, key=lambda a: a[1])[0]
   # check if unbounded
   # 如果系数非正而检验数大于0
   if all(row[column] <= 0 for row in tableau[1:-1]):
      raise Exception('\nThe optimal solution of the problem is unbounded.\n x* is unbounded.\n z* is unbounded.\n ')
      
   # 无界
   # check for degeneracy: more than one minimizer of the quotient
   #bi/aij
   quotients = [(i, r[-1] / r[column])
      for i,r in enumerate(tableau[1:-1]) if r[column] > 0]
    #bi/aij 有两个
   if moreThanOneMin(quotients):
      print('The number of optimal solution is unlimited.')
      # 退化
   # pick row index minimizing the quotient
   row = min(quotients, key=lambda x: x[1])[0]
   return row, column

# 返回换出变量与换入变量
# 将换入变量所在列的其他系数化为0
def pivotAbout(tableau, pivot):
    i,j = pivot #(1, 0)            
    pivotDenom = tableau[i + 1][j]
    tableau[i + 1] = [x / pivotDenom for x in tableau[i + 1]]
    for k,row in enumerate(tableau[1:-1]):
       if k != i:
          pivotRowMultiple = [y * tableau[1 + k][j] for y in tableau[i + 1]]
          tableau[1 + k] = [x - y for x,y in zip(tableau[1 + k], pivotRowMultiple)]
         

# 排列基变量顺序
def arange_basis(tableau):
    neo_basis = []
    for row in tableau[1:-1]:
        a = [i for (i, x) in enumerate(row) if x == 1 and i + 1 > len(tableau[1:-1])][0]
        neo_basis.append(a)
        
    return neo_basis



class Simplex_table(object):
    
    def __init__(self, A, b, c, equal, max_bool):
        # 初始化
        self.A = A
        self.b = b
        self.c = c
        self.equal = equal
        self.max_bool = max_bool
        self.row, self.col = A.shape
        self.slack_num = 0
        self.slack_coeff = []
        self.standard_matrix = np.zeros((self.row,self.col))
        self.basis = []
        self.solution_1 = []
        
        self.A_2 = A
        self.c_2 = 0
        self.row_2, self.col_2 = A.shape
        self.manual_num = 0
        self.two_stage_matrix = np.zeros((self.row,self.col))
        self.basis_2 = []
        self.solution_2 = []
        
        
    def standardize(self):
        # 标准化
        for i in equal:

            if i == 2:
                self.slack_num += 1                
                self.slack_coeff.append(-1)
            elif i == 1:
                self.slack_num += 1
                self.slack_coeff.append(1)
            else:
                self.slack_coeff.append(0)
        
        self.row +=2 #添加目标函数行与检验数行
        self.col = self.col + self.slack_num + 2 #添加b，等号
        self.standard_matrix = np.zeros((self.row, self.col)) 
        
        for i in range(self.row):
            if i > 0 and i < self.row - 1:
                self.standard_matrix[i, 0:self.A.shape[1]] = A[i - 1]
                self.standard_matrix[i, self.A.shape[1] + i - 1] =  self.slack_coeff[i - 1]
                self.standard_matrix[i, self.col - 1] = self.b[i - 1]
        

        # 目标函数系数项        
        self.standard_matrix[0, 0:len(self.c)] = self.c
        
        #计算检验数
        #for j in range(self.col - 2):
            #self.standard_matrix[-1,j] = self.standard_matrix[0, j] - np.array(self.b).dot(self.standard_matrix.T[j][1:-1])
                 
        # 将最小化问题转化为最大化问题
        if self.max_bool == 0:
            self.standard_matrix[0][0:len(self.c)] = -self.standard_matrix[0][0:len(self.c)]
            
        
        # 判断是否存在组成单位对角阵的列向量
        self.A = self.standard_matrix[1:-1, 0: self.col - 2]
        col_sum = self.A.sum(axis = 0)
        # 记录所有列和为1的下标
        index = [i for i,j in enumerate(col_sum) if j == 1 and i > self.A_2.shape[1] - 1]
        
          
        if len(index) >= self.A.shape[0]:
            self.basis = index[0:self.A.shape[0]]
            print('Find a basis in existing columns.\n')
            
            #self.basis = arange_basis(self.standard_matrix)
            for j in range(self.col - 2):
                self.standard_matrix[-1,j] = self.standard_matrix[0, j] - np.array(self.standard_matrix[0][self.basis]).dot(self.standard_matrix.T[j][1:-1])            
            return self
        
        else:
            print('Cannot find a basis in existing columns, we use two-stage method.')
            #待添加人工变量数量
            self.manual_num = self.A.shape[0] - len(index)
            print('%d new variables are introduced.' %(self.manual_num))       
            #确定人工变量添加位置
            
            fill = np.ones((1, self.A.shape[0]))
            for i in index:
                # 人工变量向量
                fill -= self.A[:, i]
                
            self.row_2 += 2 #添加目标函数行与检验数行
            self.col_2 = self.col + self.manual_num #添加b，基向量下标，等号
            self.two_stage_matrix = np.zeros((self.row_2, self.col_2)) 
            count = 1
            for i in range(self.row_2):
                if i > 0 and i < self.row - 1:
                    self.two_stage_matrix[i, 0:self.A.shape[1]] = self.A[i - 1]
                    if fill[0][i - 1] == 1:
                    # 记录添加人工变量的数量(!!!!)
                        self.two_stage_matrix[i, self.A.shape[1] + count - 1] = fill[0][i - 1]
                        count += 1
                    self.two_stage_matrix[i, self.col_2 - 1] = self.b[i - 1]
                
            # 目标函数系数项        
            self.two_stage_matrix[0, self.A.shape[1]:self.col_2 - 2] = [-1]*self.manual_num          
            self.basis_2 = index + list(range(self.A.shape[1], self.col_2 - 2))
        
            # 调整基的顺序
            self.basis_2 = arange_basis(self.two_stage_matrix)

            #计算检验数
            for j in range(self.col_2 - 2):
                self.two_stage_matrix[-1,j] = self.two_stage_matrix[0, j] - np.array(self.two_stage_matrix[0][self.basis_2]).dot(self.two_stage_matrix.T[j][1:-1])     
            return self
            
        
    def two_stage_method(self):
        tableau = self.two_stage_matrix
        while canImprove(tableau):
            pivot = findPivotIndex(tableau)
            pivotAbout(tableau, pivot)
            # 调整基的顺序
            i, j = pivot
            self.basis_2[i] = j
            #计算检验数
            for j in range(self.col_2 - 2):
                self.two_stage_matrix[-1,j] = self.two_stage_matrix[0, j] - np.array(self.two_stage_matrix[0][self.basis_2]).dot(self.two_stage_matrix.T[j][1:-1])     
            
        print('Result of Stage 1:\n')
            
        manus = []
        # 若基变量中含有人工变量， 则线性规划问题无可行解
        for _ in range(self.A.shape[1], self.A.shape[1] + self.manual_num):
            manus.append(_)
            if _ in self.basis_2:
                raise Exception('The problem doesn’t has a feasible solution.\n')
                
                  
        print('x* = ')
        print(primalSolution(self.two_stage_matrix[1:-1])[0:len(self.c)])
        print('z* = 0')
        print('The problem has feasible solution.\n')
        # 重新构造单纯形表
        self.two_stage_matrix = np.delete(self.two_stage_matrix, manus, 1)
        self.two_stage_matrix[0, 0:len(self.c)] = self.c
        # 计算检验数
        for j in range(self.col_2 - 2 - self.manual_num):
            self.two_stage_matrix[-1,j] = self.two_stage_matrix[0, j] - np.array(self.two_stage_matrix[0][self.basis_2]).dot(self.two_stage_matrix.T[j][1:-1]) 
        
            
    def simplex(self):
        if self.manual_num == 0:
            tableau = self.standard_matrix
            
            while canImprove(tableau):
                pivot = findPivotIndex(tableau)
                pivotAbout(tableau, pivot)
                i, j = pivot
                self.basis[i] = j
                for j in range(self.col - 2):
                    self.standard_matrix[-1,j] = self.standard_matrix[0, j] - np.array(self.standard_matrix[0][self.basis]).dot(self.standard_matrix.T[j][1:-1])              
              
        else:
            tableau = self.two_stage_matrix

            while canImprove(tableau):
                pivot = findPivotIndex(tableau)
                pivotAbout(tableau, pivot)
                #print("")
                i, j = pivot
                self.basis_2[i] = j
                for j in range(self.col_2 - 2- self.manual_num):
                    self.two_stage_matrix[-1,j] = self.two_stage_matrix[0, j] - np.array(self.two_stage_matrix[0][self.basis_2]).dot(self.two_stage_matrix.T[j][1:-1])              
            
        xs = [x[1] for x in primalSolution(tableau[1:-1])][0:len(self.c)]
        
        
        
        
        self.solution_1 = xs + [0] * self.slack_num

        print('The optimal solution of the problem is\n')
        print('x* =')
        print(primalSolution(tableau[1:-1])[0:len(self.c)])
        print('z*  =')
        print(np.array(self.standard_matrix[0][0:len(self.c)]).dot(np.array(xs)))
  

if __name__ == "__main__":
    a = Simplex_table(A, b, c, equal, max_bool)
    a.standardize()

    if a.manual_num == 0:
        a.simplex()
    else:
        a.two_stage_method()
        a.simplex()



