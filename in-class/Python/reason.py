import copy

class Statement:
    def __init__(self, s=None):
        self.pos = []
        self.neg = []
        if s == None:
            return
        _s = s.split(" or ")
        
        for st in _s:
            if "not" in st:
                self.neg.append(st[4:])
            else:
                self.pos.append(st)
        #按照字典序排序
        self.pos.sort()
        self.neg.sort()
        
    def __eq__(self, other):
        #类型不同直接false
        if type(self) != type(other):
            return False
        if self.pos == other.pos and self.neg == other.neg:
            return True
        return False
    
    def show(self):
        print("pos: ", self.pos)
        print("neg: ", self.neg)
    
    def digest(sta1, sta2):
        sta1_copy = copy.deepcopy(sta1)
        sta2_copy = copy.deepcopy(sta2)
        
        tag = False
        ns = Statement()
        for p in sta1_copy.pos:
            if not(p in sta2_copy.neg):
                ns.pos.append(p)
            else:
                sta2_copy.neg.remove(p)
                tag = True
    
        for n in sta1_copy.neg:
            if not(n in sta2_copy.pos):
                ns.neg.append(n)
            else:
                sta2_copy.pos.remove(n)
                tag = True
    
        for p in sta2_copy.pos:
            ns.pos.append(p)
        
        for n in sta2_copy.neg:
            ns.neg.append(n)
    
        ns.pos.sort()
        ns.neg.sort()
        
        if not tag:
            return False
        
        return ns

def input_statements():
    pre = [] 
    res = []
    while True:
        s = input("Enter a statement: ")
        if s == "":
            break
        pre.append(s)
    
    s = input("Enter the result: ")
    res.append(s)
    return pre, res

def main():
    pre, res = input_statements()
    #创建推理队列
    queue: list[Statement] = []
    for st in pre:
        queue.append(Statement(st))
    #开始推理
    for sta1 in queue:
        for sta2 in queue:
            ns = Statement.digest(sta1, sta2)
            if ns == False:
                continue
            
            if ns.pos == res and ns.neg == []:
                print("Yes")
                return
            
            if not ns in queue:
                queue.append(ns)
    
    print("No")
    return       
    
if __name__ == "__main__":
    main()