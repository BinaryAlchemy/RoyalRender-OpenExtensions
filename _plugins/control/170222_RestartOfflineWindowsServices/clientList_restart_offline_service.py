text_file = open("C:\\offline_clients.bat", "w")
nrClients= rr.clientAll_count()

for i in range(0,rr.clientAll_count()):
    client=rr.clientAll_get(i)
    if (client.jobThread(0).clientStatus==0):
        text_file.write("sc \\\\"+client.name()+" stop RoyalRenderService \n")
        
for i in range(0,rr.clientAll_count()):
    client=rr.clientAll_get(i)
    if (client.jobThread(0).clientStatus==0):
        text_file.write("sc \\\\"+client.name()+" start RoyalRenderService \n")



text_file.write("pause \n")
        
text_file.close()





