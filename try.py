#Product(catalogno 10,description 40, price 10, count 10)
#Customer(id 10, name 30, emailid 40, postaladd 60)
#Orders(custid 10, catalogno 10, quantity 10, amount 10)

#print "Entering details into Product table"
#n = int(raw_input("Enter no. of entries:"))

#f = open("product.data", "w")
#for i in xrange(n):
#    print "Enter catno, description, price, count"
#    s = raw_input()
#    catno, desc, price, count = s.split()
#    catno += "$"*(10 - len(catno))
#    desc += "$"*(40 - len(desc))
#    price += "$"*(10 - len(price))
#    count += "$"*(10 - len(count))
#    f.write(catno + desc + price + count)
#    f.write('\n')

#print "Entering details into Product table"
#n = int(raw_input("Enter no. of entries:"))

#f = open("customer.data", "w")
#for i in xrange(n):
#    print "Enter cid, name, email, add"
#    s = raw_input()
#    cid, name, eid, add = s.split()
#    cid += "$"*(10 - len(cid))
#    name += "$"*(30 - len(name))
#    eid += "$"*(40 - len(eid))
#    add += "$"*(60 - len(add))
#    f.write(cid + name + eid + add)
#    f.write('\n')

print "Entering details into orders table"
n = int(raw_input("Enter no. of entries:"))

f = open("orders.data", "w")
for i in xrange(n):
    print "Enter custid, catalogno, quantity, amt"
    s = raw_input()
    cid, catno, quant, amt = s.split()
    cid += "$"*(10 - len(cid))
    catno += "$"*(10 - len(catno))
    quant += "$"*(10 - len(quant))
    amt += "$"*(10 - len(amt))
    f.write(cid + catno + quant + amt)
    f.write('\n')
