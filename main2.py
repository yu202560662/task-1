# 2. 成员函数
# 编写类 MyClass，定义成员函数 fun，实现查找数组最小值，并将最小值与数组末尾元素互换位置。主函数中录入数组长度与数组数据，实例化类对象调用该成员函数，最终分别打印输出交换前后的数组。
class Menber:
    def __init__(self):
        self.s=[5, 34, 1, 2, 56, 4]
        self.len=len(self.s)
        
    def fun(self):
        s_min=min(self.s)
        s_last=self.s[5]
        a=self.s.index(s_min)
        b=self.s.index(s_last)
        self.s[a],self.s[b]=self.s[b],self.s[a]
        print(self.s)
menber=Menber()
menber.fun()
