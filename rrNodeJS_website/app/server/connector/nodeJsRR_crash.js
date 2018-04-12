let	binding = require("./nodeJsRR.node");
console.log("start")

/*
Empty HTTP method object.
*/

let tcp = binding._rrTCP();
let rrServer = "localhost";
if (!rrServer) {
    res.status(400).json(JSON.stringify(tcp.errorMessage()));
}
if (!tcp.setServer(rrServer, 7773)) {
    res.status(400).json(JSON.stringify(tcp.errorMessage()));
}
tcp.setLogin("rrDev", "test");


function jobsDetails() {
	let jobsDetails = [];
	console.log("\nCheck jobs");
	/* retrieve only job details of user "renderfarm" to reduce
	network traffic, rrServer workload and memory usage. */
	var jobUserName = "";
	var jobProjectName = "";
	var jobAppName = "";
	tcp.jobSetFilter(jobUserName, jobProjectName, jobAppName, "", 255);

	var lastJobID=0
	if (!tcp.jobGetInfoSend()) {
		console.log("Error getting jobs:", tcp.errorMessage());
	} else {
		var jobs = tcp.jobs;
		var nbJobs = jobs.getMaxJobsFiltered();

		for (var i = 0; i < nbJobs; i++) {
			var jID = jobs.getJobMinInfo_filterQueue(i).ID;
			var username= jobs.getJobMinInfo_filterQueue(i).userName;
			var jobDataType = jobs.getJobDataType(jID);  // which kind of data we have for the job
			var job = jobs.getJobSend(jID);
			let jobDetails = {
				job: job,
				jobId: job.IDstr(),
			}
			jobsDetails.push(jobDetails);
			lastJobID =jID
		}
	}
	console.log(jobsDetails)
	
	var rrJobEnumHelper = binding.createRRJob();
	var jobIDList= [lastJobID];
	if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
	if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}
		if (!tcp.jobSendCommand (jobIDList,  rrJobEnumHelper._logMessage.lEnable, 0 )) {
	    console.log("Error sending job command:", tcp.errorMessage());
	}

		
}

jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()


jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()
jobsDetails()




console.log("----------------------------------DONE-------------------------------")
