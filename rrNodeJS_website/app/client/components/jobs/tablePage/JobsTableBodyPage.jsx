'use strict';

import React from 'react';
import JobsExpandedTablePage from './JobsExpandedTablePage.jsx';


//TableBodyPage component
const JobsTableBodyPage = (props) => {

  const isActive = (value) => {
    if(props.selectedJobs.length) {
      let selectedJobs = props.selectedJobs;
      let i = 0;
      for(i in selectedJobs) {
        if(value===selectedJobs[i].jobId) {
          return 'activeJob';
        }
      }
    } else {
      return '';
    }
  }

  let jobDetails = props.jobDetails;
  return (
    <tr className={'bar '+isActive(jobDetails.jobId)} onClick={() => props.handleRowClick(jobDetails)}>
      <td><input type="checkbox" checked={isActive(jobDetails.jobId)=='activeJob'?true:false} /></td>
      <td>{jobDetails.jobId}</td>
      <td>{jobDetails.job.renderApp.name}</td>
      <td>{jobDetails.job.renderApp.rendererName}</td>
      <td>{jobDetails.job.sceneName}</td>
      <td>{jobDetails.job.layer}</td>
      <td>{jobDetails.job.seqStart}</td>
      <td>{jobDetails.job.seqEnd}</td>
      <td>{jobDetails.job.seqStep}</td>
      <td>{jobDetails.job.framesDone}</td>
      <td>{jobDetails.job.framesLeft}</td>
      <td>{jobDetails.job.status}</td>
      <td>{jobDetails.job.userName}</td>
      <td>{jobDetails.job.clientsRenderingCount}</td>
      <td>{jobDetails.job.errorCount}</td>
    </tr>
  )
};

export default JobsTableBodyPage;
