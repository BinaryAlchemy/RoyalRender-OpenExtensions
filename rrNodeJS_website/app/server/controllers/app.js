/*
Load all models here
*/
let	express = require("express"),
	app = express(),
	bodyParser = require("body-parser");
	router = express.Router(),
	assert = require('assert'),
	// binding = require("../connector/nodeJsRR.node"),
	uuidV4 = require('uuid/v4'),
	crypto=require('crypto'),
	os = require("os"),
	async = require('async'),
	binding = require("../connector/nodeJsRR.node"),
	tcp = '';

let testJobs = require('../testing/testJobs')
/*
Empty HTTP method object.
*/
let appMethod = {};

/*
Routings/controller goes here
*/

module.exports = function(router) {
    router.post('/login',appMethod.login);
		router.post('/logged-user',appMethod.loggedUser);
		router.get('/logout', appMethod.logoutUser);
		router.get('/clients-details', appMethod.clientsDetails);
		router.get('/jobs-details', appMethod.jobsDetails);
		router.get('/jobs-filter-details', appMethod.jobsFilterDetails);
		router.post('/job-send-command', appMethod.jobSendCommand);
		router.post('/client-send-command', appMethod.clientSendCommand);
		router.get('/test-jobs', testJobs.jobsDetails);
};


/**************************************************************************************************************************/
/***************************************** All the HTTP methods goes here *************************************************/
/**************************************************************************************************************************/


/*******************************
   User Login here .
********************************/
appMethod.login = function(req, res) {

	tcp = binding.createTCP();
    let username = req.body.username;
	let password = req.body.password;
	let salt = Math.round(new Date().valueOf()*Math.random())+'';
	let hash = crypto.createHmac('sha256',salt);
	let hashedPassword = hash.update(password).digest('hex');
	let userDetails = req.session.userDetails

  if (!userDetails) {
    userDetails = req.session.userDetails = {}
  }

    userDetails["username"] = username;
	userDetails["hashedPassword"] = hashedPassword;
	userDetails["userp"] = password;
	userDetails["salt"] = salt;

    tcp.setServer("192.168.0.100", 7773);

    tcp.setLogin(username, password);

	tcp.jobSetFilter("", "", "", "", 255);

	if(tcp.jobGetInfoSend()) {
		return res.status(200).json(hashedPassword);
	} else {
		req.session.destroy();
		return res.status(200).json(false);
	}

}
/***********************************
       User Login ends here.
***********************************/


/***********************************
       Check Logged User.
***********************************/
appMethod.loggedUser = function(req, res) {
	let token = req.headers.token;
	let userDetails = req.session.userDetails;
	if(userDetails && userDetails.hashedPassword == token) {
		return res.status(200).json({user:"logged"});
	} else {
		return res.status(200).json({user:"notlogged"});
	}
}
/***********************************
       Check Logged User ends here.
***********************************/

/***********************************
      			Logout User.
***********************************/
appMethod.logoutUser = function(req, res) {
	req.session.destroy(function(err) {
		if(err) {
			return res.status(200).json({msg:"Error occured", err: err});
		} else {
			return res.status(200).json({msg:"User Logged out", err: false});
		}
	});
}
/***********************************
       Logout User ends here.
***********************************/

/*******************************
   Get Clients Details .
********************************/
appMethod.clientsDetails = function(req, res) {

	let userDetails = req.session.userDetails;
	if(!userDetails) {
		return res.status(200).json({msg: "login first", err: true});
	}
  tcp = binding.createTCP();
	tcp.setServer("217.253.8.241", 7773);
	tcp.setLogin(userDetails.username, userDetails.userp);
	let clientsDetails = [];

	if (!tcp.clientGetList()) {
		return res.status(200).json({
			msg: "Error getting clients",
			err: tcp.errorMessage()
		});
	}

	const nbClients = tcp.clients.count();
  for (let i = 0; i < nbClients; i++) {
		client = tcp.clients.at(i);
		maxThreads= client.maxJobThreads;
		for (let jt = 0; jt < maxThreads; jt++) {
			let jthread = client.jobThread(jt);
			let clientDetails = {
				client: client,
				clientStatus: jthread.clientStatusAsStringSingle(),
				CPUJob: jthread.jobCPU_Usage,
				clientId: client.name+jt+i,
			}
			clientsDetails.push(clientDetails);
		}
  }
	return res.status(200).json(clientsDetails);
}
/*******************************
   Get Clients Details Ends Here .
********************************/


/*******************************
   Get Jobs Details .
********************************/
appMethod.jobsDetails = function(req, res) {

	let userDetails = req.session.userDetails;
	if(!userDetails) {
		return res.status(200).json({msg: "login first", err: true});
	}
	tcp = binding._rrTCP();
	let rrServer = "217.253.8.241";
	tcp.setLogin(userDetails.username, userDetails.userp);
	if (!rrServer) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}
	if (!tcp.setServer(rrServer, 7773)) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}

	// tcp.setLogin("TestUser", "Password");
	let jobsDetails = [];
	/* retrieve only job details of user "renderfarm" to reduce
	network traffic, rrServer workload and memory usage. */
	let jobUserName = req.query.user;
	let jobProjectName = req.query.project;
	let jobAppName = req.query.app;
	tcp.jobSetFilter(jobUserName, jobProjectName, jobAppName, "", 255);

	if (!tcp.jobGetInfoSend()) {
		console.log("Error getting jobs:", tcp.errorMessage());
	} else {
		let jobs = tcp.jobs;
		let nbJobs = jobs.getMaxJobsFiltered();

		for (let i = 0; i < nbJobs; i++) {
			let jID = jobs.getJobMinInfo_filterQueue(i).ID;
			// let username= jobs.getJobMinInfo_filterQueue(i).userName;
			// let jobDataType = jobs.getJobDataType(jID);  // which kind of data we have for the job
			let job = jobs.getJobSend(jID);
			console.log(job.IDstr())
			let jobDetails = {
				job: job,
				jobId: job.IDstr(),
				jID: jID,
				jobMinInfo: jobs.getJobMinInfo_queue(i),
			}
			jobsDetails.push(jobDetails);
		}
	}

	return res.status(200).json(jobsDetails);
}
/*******************************
   Get Jobs Details Ends Here .
********************************/


/*******************************
   Get Jobs Filters
********************************/
appMethod.jobsFilterDetails = function(req, res) {

	let userDetails = req.session.userDetails;
	if(!userDetails) {
		return res.status(200).json({msg: "login first", err: true});
	}
	tcp = binding._rrTCP();
	let rrServer = "217.253.8.241";
	tcp.setLogin(userDetails.username, userDetails.userp);
	if (!rrServer) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}
	if (!tcp.setServer(rrServer, 7773)) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}

	let jobsDetails = {
		project: [],
		user: [],
		app: [],
	};
	console.log("\nCheck jobs");
	/* retrieve only job details of user "renderfarm" to reduce
	network traffic, rrServer workload and memory usage. */
	let jobUserName = req.query.user;
	let jobProjectName = req.query.project;
	let jobAppName = req.query.app;
	tcp.jobSetFilter(jobUserName, jobProjectName, jobAppName, "", 255);

	if (!tcp.jobGetInfoSend()) {
		console.log("Error getting jobs:", tcp.errorMessage());
	} else {
		let jobs = tcp.jobs;
		let nbJobs = jobs.getMaxJobs();

		for (let i = 0; i < nbJobs; i++) {
			let jobMinInfo = jobs.getJobMinInfo_queue(i);
			if(!jobsDetails.user.includes(jobMinInfo.userName)) {
				jobsDetails.user.push(jobMinInfo.userName);
			}
			if(!jobsDetails.project.includes(jobMinInfo.companyProjectName)) {
				jobsDetails.project.push(jobMinInfo.companyProjectName);
			}
			if(!jobsDetails.app.includes(jobMinInfo.rendererName)) {
				jobsDetails.app.push(jobMinInfo.rendererName);
			}
		}
	}

	return res.status(200).json(JSON.stringify(jobsDetails));
}
/*******************************
   Get Jobs Filters Ends Here.
********************************/

/*******************************
   Post Job Send Command.
********************************/
appMethod.jobSendCommand = function(req, res) {

 	let userDetails = req.session.userDetails;
	if(!userDetails) {
		return res.status(200).json({msg: "login first", err: true});
	}
	let rrJob = binding.createRRJob();
	tcp = binding._rrTCP();
  tcp.setLogin(userDetails.username, userDetails.userp);
	// tcp.setLogin("rrDev", "test");
	let rrServer = "217.253.8.241";
	if (!rrServer) {
	   return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}
	if (!tcp.setServer(rrServer, 7773)) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}


	let jobsApply = req.body.jobsId;
	let methodName = req.body.method;
	let index = 0;

	if(jobsApply.length) {
		tcp.jobSetFilter("", "", "", "", 255);

		if (!tcp.jobGetInfoSend()) {
			console.log("Error getting jobs:", tcp.errorMessage());
		} else {
			let jobs = tcp.jobs;
			let nbJobs = jobs.getMaxJobsFiltered();
			let jobApplyjID = [];
			async.series([
		    function(callback) {
		        async.times(nbJobs, function(index, callback) {
							let jID = jobs.getJobMinInfo_filterQueue(index).ID;
							let job = jobs.getJobSend(jID);
							if(jobsApply.indexOf(job.IDstr()) != -1) {
								jobApplyjID.push(jID);
							}
							callback(null);
						}, function(err, users) {
						   callback(null, jobApplyjID)
						});

		    },
		    function(callback) {
					switch(methodName) {
					 case 'lAbortedReservedClients':
						 if(!tcp.jobSendCommand(jobApplyjID,  rrJob._logMessage.lAbortedReservedClients, index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lEnable':
						 if(!tcp.jobSendCommand(jobApplyjID,  rrJob._logMessage.lEnable, index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lDisable':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lDisable,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lDisableAbort':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lDisableAbort,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lApprove':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lApprove,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lDisApprove':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lDisApprove,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lDelete':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lDelete,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lAbort':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lAbort,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lCheck':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lCheck,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lReset':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lReset,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 case 'lResetNDelete':
						 if(!tcp.jobSendCommand(jobApplyjID, rrJob._logMessage.lResetNDelete,index)) {
							  return callback("failed");
						 }
						 callback();
						 break;
					 default:
						 return res.status(200).json({result:"Wrong Command"});
				 }
		    }
			],
			function(err, results) {
				if(err) {
					return res.status(200).json({msg: "Command Failed"});
				} else {
					return res.status(200).json({msg: "Success"})
				}
			});
		}
	} else {
		return res.status(200).json({msg: "Select a job."});
	}

	// if(!jobsApply.length) {
	// 	return res.status(200).json({result:"Command cannot be executed on empty list."});
	// }
}
/*******************************
   Post Job Send Command Ends Here.
********************************/

/*******************************
   Post Client Send Command.
********************************/
appMethod.clientSendCommand = function(req, res) {

	let userDetails = req.session.userDetails;
	if(!userDetails) {
		return res.status(200).json({msg: "login first", err: true});
	}
	tcp = binding._rrTCP();
	let rrGlobal = binding.rrGlobal();
	let rrServer = "217.253.8.241";
	tcp.setLogin(userDetails.username, userDetails.userp);
	if (!rrServer) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}
	if (!tcp.setServer(rrServer, 7773)) {
	    return res.status(400).json(JSON.stringify(tcp.errorMessage()));
	}

	if (!tcp.clientGetList()) {
	  return res.status(400).json({msg:"Error getting clients", err: tcp.errorMessage()});
	}

	// let this_machine = os.hostname();

	let clientList = req.body.clientList;
	let methodName = req.body.method;
	let index = req.body.index;
	let clientApplyList = [];

	for(let i = 0; i < clientList.length; i++) {
		// let clientname = clientList[i];
		// console.log(clientname, ' == ', this_machine)
		// if (clientname == this_machine) {
	        clientApplyList.push(i);
		// }
	}
	console.log(clientApplyList, "=========clientApplyList");

	if(clientApplyList.length) {
		switch(methodName) {
			case 'cEnable':
				if (!tcp.clientSendCommand(clientApplyList, rrGlobal.ClientCommand.cEnable, "")) {
					return res.status(200).json({result:"falied"});
				}
				break;
			case 'cDisable':
				if (!tcp.clientSendCommand(clientApplyList, rrGlobal.ClientCommand.cDisable, "")) {
					return res.status(200).json({result:"falied"});
				}
				break;
			default:
				return res.status(200).json({result:"Wrong Command"});
		}
	}

	if(!clientApplyList.length) {
		return res.status(200).json({result:"Command cannot be executed on empty list."});
	}

	return res.status(200).json({result:"success"});
}
/*******************************
   Post Client Send Command Ends Here.
********************************/
