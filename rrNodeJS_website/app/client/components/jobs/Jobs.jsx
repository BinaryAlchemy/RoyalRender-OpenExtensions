'use strict';

import React from 'react';
import axios from 'axios';
import PropTypes from 'prop-types';
import { NotificationManager } from 'react-notifications';

import JobsOptionsPage from './options/JobsOptionsPage.jsx';
import JobsTablePage from './tablePage/JobsTablePage.jsx';
import JobDetailPage from './details/JobDetailPage.jsx';

//Jobs component
class Jobs extends React.Component {
  constructor(props){
    super(props);
    this.state = {
      jobs: [],
      tempJobs: [],
      selectedJobs: [],
      selectedOptions: {
        projectSelect: '',
        userSelect: '',
        appSelect: '',
      },
      projectOptions: null,
      userOptions: null,
      appOptions: null,
      renderJobDetails: false,
      renderOptionPage: null,
      isRendering: null,
      isNotRenderinge: null,
      isFinished: null,
      isDisabled: null,
      isWaitFor: null,
      invert: false,
      filteredArray: [],
    };
  }

  componentWillMount() {
    let that = this;
    axios.get(`api/jobs-filter-details?project=${this.state.selectedOptions.projectSelect}&&user=${this.state.selectedOptions.userSelect}&&app=${this.state.selectedOptions.appSelect}`)
    .then(function (response) {
      if(response.data.err) {
        that.props.history.push('/login');
        return;
      }
      let filterDetails = JSON.parse(response.data);
      that.setState({
        projectOptions: filterDetails.project,
        userOptions: filterDetails.user,
        appOptions: filterDetails.app,
      });
    })
    .catch(function (error) {
      console.log(error);
    });
    this.renderJobs();
  }

  renderJobs(nextSelectedOptions) {
    let that = this;
    let selectedOptions = nextSelectedOptions || this.state.selectedOptions;
    axios.get(`/api/jobs-details?project=${selectedOptions.projectSelect}&&user=${selectedOptions.userSelect}&&app=${selectedOptions.appSelect}`)
    .then(function (response) {
      if(response.data.err) {
        that.props.history.push('/login');
        return;
      }
      that.setState({jobs: response.data, tempJobs: response.data});
    })
    .catch(function (error) {
      console.log(error);
      NotificationManager.error(error, "Error Getting Jobs");
    });
  }

  updateSelectedOption(event) {
    var selectedOptions = this.state.selectedOptions;
    selectedOptions[event.target.id] = event.target.value;
    this.renderJobs(selectedOptions);
    this.setState({selectedOptions: selectedOptions});
  }

  updateFilterChecks(target, value) {
    this.setState({selectedJobs:[]});
    this.setState({[target]: value});

    let tempFilterJobs = [],
        filteredJobs = [],
        jobs = this.state.jobs,
        tempJobs = this.state.tempJobs,
        checkIsRendering = target=="isRendering"?value:this.state.isRendering,
        checkIsNotRendering = target=="isRendering"?!value:this.state.isNotRendering,
        checkIsDisabled = target=="isDisabled"?value:this.state.isDisabled,
        checkIsWaitFor = target=="isWaitFor"?value:this.state.isWaitFor,
        checkIsFinished = target=="isFinished"?value:this.state.isFinished,
        invert = target=="invert"?value:this.state.invert;

    tempJobs.forEach((job) => {
      let checkDisabled = checkIsDisabled!=null?job.jobMinInfo.isDisabled == checkIsDisabled:true,
          checkWaitFor = checkIsWaitFor!=null?job.jobMinInfo.isWaitFor == checkIsWaitFor:true,
          checkFinished = checkIsFinished!=null?job.jobMinInfo.isFinished == checkIsFinished:true;

      if(invert?!checkDisabled:checkDisabled && invert?!checkWaitFor:checkWaitFor && invert?!checkFinished:checkFinished) {
        tempFilterJobs.push(job);
      }
    });

    tempFilterJobs.forEach((job) => {
      let checkRendering = checkIsRendering!=null?job.jobMinInfo.isRendering == checkIsRendering:true;
      let checkNotRendering = checkIsNotRendering!=null?job.jobMinInfo.isRendering == checkIsNotRendering:false;

      if((invert?!checkRendering:checkRendering == true && invert?!checkNotRendering:checkNotRendering == false) ||
      (invert?!checkRendering:checkRendering == false && invert?!checkNotRendering:checkNotRendering == false)) {
        filteredJobs.push(job);
      }
    })
    this.setState({jobs: filteredJobs});
  }

  handleRowClick(details) {
    var selectedJobs = this.state.selectedJobs.slice();
    let index = selectedJobs.findIndex(x => x.jobId == details.jobId);
    if (index != -1) selectedJobs.splice(index, 1);
    else selectedJobs.push(details);
    this.setState({ selectedJobs: selectedJobs })
  }

  showJobsDetails() {
    this.setState({renderJobDetails: true});
  }

  goBackToJobs() {
    this.setState({renderJobDetails: false});
  }

  buttonAction(method, index) {
    let selectedOptions = this.state.selectedOptions;
    // console.log("########################################################################");
    // for (var j = 0; j < this.state.selectedJobs.length; j++) {
    //      console.log("buttonAction :",this.state.selectedJobs[j].jID);
    // }
    // console.log("########################################################################");
    let selectedJobId = [];
    this.state.selectedJobs.map(selectedJob => {
      selectedJobId.push(selectedJob.jobId);
    });


    let that = this;
    if(!selectedJobId.length) {
      NotificationManager.warning("Select a job!");
      return;
    }

    console.log(selectedJobId, method, index);
    axios.post('/api/job-send-command', {
        project: selectedOptions.projectSelect,
        user: selectedOptions.userSelect,
        app: selectedOptions.appSelect,
        jobsId: selectedJobId,
        method: method,
        index: index
    })
    .then(function (response) {
      if(response.data.msg == "Command Failed") {
        // that.props.history.push('/login');
        NotificationManager.error("Command error");
        return;
      }
      NotificationManager.success("Command success");
    })
    .catch(function (error) {
      console.log(error);
      NotificationManager.error(error, "Error");
    });
  }

  setSelectedButton(value) {
    if(value == this.state.renderOptionPage)
      this.setState({renderOptionPage:null})
    else
      this.setState({renderOptionPage:value})
  }

  updateJobs() {
    this.setState({
      selectedJobs: [],
      selectedOptions: {
        projectSelect: '',
        userSelect: '',
        appSelect: '',
      },
      projectOptions: null,
      userOptions: null,
      appOptions: null,
      renderJobDetails: false,
      renderOptionPage: null,
      isRendering: null,
      isNotRenderinge: null,
      isFinished: null,
      isDisabled: null,
      isWaitFor: null,
    });
    this.renderJobs();
    NotificationManager.succes("Jobs updated");
  }

  render() {
    return (
      <div className="container">
        {this.state.renderJobDetails?
            <JobDetailPage
              selectedJobs={this.state.selectedJobs}
              goBackToJobs={this.goBackToJobs.bind(this)}
            />
          :
            <div className="jobContainer">
              <JobsOptionsPage
                updateJobs={this.updateJobs.bind(this)}
                buttonAction={this.buttonAction.bind(this)}
                showJobsDetails={this.showJobsDetails.bind(this)}
                setSelectedButton={this.setSelectedButton.bind(this)}
                updateSelectedOption={this.updateSelectedOption.bind(this)}
                updateFilterChecks={this.updateFilterChecks.bind(this)}
                {...this.state}
              />
              <JobsTablePage
                renderJobs={this.renderJobs.bind(this)}
                handleRowClick={this.handleRowClick.bind(this)}
                selectedOptions={this.state.selectedOptions}
                jobs={this.state.jobs}
                selectedJobs={this.state.selectedJobs}
                // {...this.state}
              />
            </div>
        }
      </div>
    )
  }
};


export default Jobs;
