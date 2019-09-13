import bindings from 'rrbindings'

//Create RRTCP object and connect to the renderfarm via its IP
const rrtcp = bindings._rrTCP()

const rrServerIP: string = '111.11.11.1'    // CHANGE THIS VALUE TO YOUR rrServerIP
const rrServerPORT: number = 1234           // CHANGE THIS VALUE TO YOUR rrServerPORT

rrtcp.setServer(rrServerIP, rrServerPORT)

//Get all the clients from the connected Renderfarm
rrtcp.clientGetList()

//Get the number of Clients
const nbClients = rrtcp.clients.count()

//Print out every client and its properties
for(let i = 0; i < nbClients; i++){
    console.log(rrtcp.clients.at(i))
}
