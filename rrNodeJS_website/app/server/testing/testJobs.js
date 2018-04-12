let	express = require("express"),
	app = express(),
	bodyParser = require("body-parser"),
	binding = require("../connector/nodeJsRR.node");

/*
Empty HTTP method object.
*/
var testJobs = module.exports = {};

testJobs.jobsDetails = function(req, res) {
	let tcp = binding._rrTCP();
	let rrServer = "79.204.82.58";
	if (!rrServer) {
	    res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}
	if (!tcp.setServer(rrServer, 7773)) {
	    res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}

	tcp.setLogin("TestUser", "Password");
	let jobsDetails = [];
	console.log("\nCheck jobs");
	/* retrieve only job details of user "renderfarm" to reduce
	network traffic, rrServer workload and memory usage. */
	var jobUserName = "";
	var jobProjectName = "";
	var jobAppName = "";
	tcp.jobSetFilter(jobUserName, jobProjectName, jobAppName, "", 255);

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
		}
	}

	res.status(200).json(jobsDetails);
}

// module.exports testJobs;
