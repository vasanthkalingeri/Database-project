import os

while True:
    print "Enter your query"
    query = raw_input()
    words = query.split()
    words = words[1:]
    #look = {'product':{'catalogno':0, 'description':10, 'price':50, 'count':60}, 'customer':{'id':0, 'name':10, 'catalogno':10, 'emailid':40, 'postaladd':80}, 'orders':{'custid':0, 'catalogno':10, 'quantity':20, 'amount':30}}
    look = {'product':{'catno':0, 'desc':1, 'price':2, 'count':3}, 'customer':{'id':0, 'name':1, 'emailid':2, 'postaladd':3}, 'orders':{'custid':0, 'catno':1, 'quantity':2, 'amt':3}}

    column = []
    for i in range(len(words)):
        if words[i] == 'from':
            tablename = words[i + 1]
            break
        column.append(words[i])

    f = open('output', 'w')
    f.write(tablename + ".data\n")


    keys = []
    for key in look[tablename].keys():
        keys.append(look[tablename][key])
    f.write(str(len(keys) * 40 - 1) + "\n")

    keys.sort()
    for key in keys:
        f.write(str(key * 40) + "\n")
    f.write("-1\n")

    if len(column) == 1 and column[0] == '*':
        for key in keys:
            f.write(str(key * 40) + "\n")
        f.write("-1\n")         
    else:
        for col in column:
            f.write(str(look[tablename][col] * 40) + "\n")
        f.write("-1\n")

    operators = {'<':3, '<=':5, '>':4, '>=':6, '=':1, '!=':2}
    i += 3

    numconditions = str(len(words[i:]) / 3)
        
    words = words[i:]
    if int(numconditions) > 0:
        f.write(numconditions + "\n")
        
        relations = {'and':0, 'or':1}
        i = 3
        rel = []
        while( i < len(words)):
            rel.append(relations[words[i]])
            words.remove(words[i])
            i += 4
        i = 0
        leftside = []
        rightside = []
        oper = []

        while i <= (len(words) - 3):
            op = operators[words[i + 1]]
            try:    
                right = look[tablename][words[i + 2]]
                op += 10
                
            except:
                right = words[i + 2]
            left = look[tablename][words[i]] * 40
            leftside.append(left)
            rightside.append(right)
            oper.append(op)   
        #    print left, op, right 
            i += 3

        for i in range(int(numconditions)):
            f.write(str(oper[i]) + "\n" + str(leftside[i]) + "\n" + str(rightside[i]) + "\n")
            if i > 0:
                f.write(str(rel[0]))
                
    else:
        f.write("1\n")
        f.write("2\n")
        f.write("0\n")
        f.write("gibberishasdfadsf\n")
    f.close()
    os.system("./a.out < output")
    print
    print
    choice = int(raw_input("Enter 0 to exit 1 to continue:"))
    if choice == 0:
        break
