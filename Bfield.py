#!/usr/bin/python

fo = open("Dipole_field_mm_Tesla.txt","r")

#lines=fo.readlines()

result=[]

print "Name of the file: ", fo.name
print "Closed or not : ", fo.closed
print "Opening mode : ", fo.mode
print "Softspace flag : ", fo.softspace

data = [line.split() for line in fo.readlines()[1:]]
out = [(float(k), float(v)) for k, v in data]
    
#for i in out:
#print i

fo.close()
