// Royal Render - nodeJsRR_test.js

// This file tests the native module nodeJsRR.node.


console.log('### BEGIN ###');

var assert = require('assert');

var binding = require("./nodeJsRR.node");

var tcp = binding.createTCP();

var rrGlobal = binding.rrGlobal(); 

function connectToServer() {
		
    tcp.setServer("79.204.82.58", 7773);
    //tcp.setServer("localhost", 7773);
	
    tcp.setLogin("TestUser", "Password")
}



function requestClients() 
{
	

	if (!tcp.clientGetList()) {
		console.log("Error getting clients: " + tcp.errorMessage());
	}

	const nbClients = tcp.clients.count();
	var clientApplyCommandList = [];

    console.log("Number of Clients:", nbClients);
    for (var i = 0; i < nbClients; i++) {
		clientApplyCommandList.push(i);
		client = tcp.clients.at(i);
		maxThreads= client.maxJobThreads;
		console.log(" Number of threads  " + maxThreads);
		for (var jt = 0; jt < maxThreads; jt++) {
			console.log("   " + client.name,
					"\tCPU:", client.CPU_Usage, "\tGPU:", client.GPU_Usage, "\tmemory:", client.availMemoryMB,
					"\tHDDTemp:", client.tempHDD, "\tGPUTemp:", client.gpuTemperature
					);
			var jthread = client.jobThread(jt);
			console.log("   " ,"\tStatus:", jthread.clientStatusAsStringSingle(), "\tCPUJob:", jthread.jobCPU_Usage	);
		}
    }
	
	console.log("Disabling all clients")
    if (!tcp.clientSendCommand(clientApplyCommandList, rrGlobal.ClientCommand.cDisable, "")) {
	    console.log("Error sending command:", tcp.errorMessage());
    } else {
		console.log("command was send");
	}
}





function requestJobs() {
// --------------------------------------------------------------------- JOBS
/*
 IMPORTANT: tcp caches all jobs, if you destroy it, the rrServer has to send all jobs again
 A list request will always be executed, so you have a list of all jobs at the rrServer
 But to reduce traffic, you should set a filter for the jobs you need before you request more data
 There are three levels of job information:
 MinInfo: The list, all jobs with ID, user, software, project
 Basic:   Scene information
 Send:    All job data you can have
*/
    
	console.log("\nCheck jobs");
	/* retrieve only job details of user "renderfarm" to reduce
	network traffic, rrServer workload and memory usage. */
	var jobUserName = "";
	tcp.jobSetFilter(jobUserName, "", "", "", 255); 
	
	var lastJobID=0
	if (!tcp.jobGetInfoSend()) {
	    console.log("Error getting jobs:", tcp.errorMessage());
	} else {
		console.log("------------------------------------------------");
	    var jobs = tcp.jobs;
		var nbJobs = jobs.getMaxJobs()
	    console.log("Number of all jobs: ", jobs.getMaxJobs());
	    for (var i = 0; i < nbJobs; i++) {
    		var job = jobs.getJobMinInfo_queue(i);
	        console.log("   " + job.IDstr(),
					"\tuser:", job.userName, 
					"\tproject:", job.companyProjectName,
					"\tapp:", job.rendererName
					);
		}
		
	    
		console.log("------------------------------------------------");
		nbJobs = jobs.getMaxJobsFiltered();
	    console.log("Number of jobs - filtered by user ", jobUserName + ": ", nbJobs)
	    for (var i = 0; i < nbJobs; i++) {
    		var jID = jobs.getJobMinInfo_filterQueue(i).ID;
			lastJobID =jID
		    var jobDataType = jobs.getJobDataType(jID);  // which kind of data we have for the job
		    var job = jobs.getJobSend(jID);
		    console.log("   " + job.IDstr(),
					"\tuser:", job.userName, 
					"\tproject:", job.companyProjectName, "\tapp:", job.renderApp.name,
					"\tseqStart:", job.seqStart, "\tseqEnd:", job.seqEnd
					);
            //console.log("job ", job);
	    }
	}
	
	
	console.log("------------------------------------------------");
	console.log("Sending command to last job in list");
	var rrJobEnumHelper = binding.createRRJob();
	var jobIDList= [lastJobID];
	if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		

		
}


connectToServer();

requestClients();



requestJobs();


console.log('###  END  ###');
