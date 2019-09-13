import bindings from 'rrbindings'

//Create RRTCP object and connect to the renderfarm via its IP
const rrtcp = bindings._rrTCP()
rrtcp.setServer('172.31.18.1', 7773)

//Get all the clients from the connected Renderfarm
rrtcp.clientGetList()

//Get the number of Clients
const nbClients = rrtcp.clients.count()

//Print out every client and its properties
for(let i = 0; i < nbClients; i++){
    console.log(rrtcp.clients.at(i))
}