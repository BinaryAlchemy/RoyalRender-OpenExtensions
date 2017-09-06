import sys
import inspect



print ("list sys.path:")
for p in sys.path: print(p)
print("_______________________________")
print("")

print("--------------------SSL (shotgun httplib2 prerequisite) -------------------")
print("import _ssl...")
import _ssl             
print("import ssl...")
import ssl 


print("--------------------shotgun_api3-------------------")
print("import shotgun_api3...")
import shotgun_api3
print("ismodule:   "+str(inspect.ismodule(shotgun_api3)))
print("getsourcefile:  "+str(inspect.getsourcefile(shotgun_api3)))

print("--------------------shotgun_api3.shotgun-------------------")
print("import shotgun_api3.shotgun...")
from shotgun_api3 import shotgun
print("ismodule:   "+str(inspect.ismodule(shotgun_api3.shotgun)))
print("getsourcefile:  "+str(inspect.getsourcefile(shotgun_api3.shotgun)))
print("getsourcelines:  ")
#print("##############################################################################################")
#print(inspect.getsource(shotgun_api3.shotgun))
#print("##############################################################################################")
#print("##############################################################################################")


print("--------------------shotgun_api3 RR rifleConnect--------------------")
sg=rrSG.rifleConnect()
print("rrSG object: "+str(sg))

        