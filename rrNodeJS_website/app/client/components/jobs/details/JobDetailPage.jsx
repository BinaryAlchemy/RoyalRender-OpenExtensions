'use strict';

import React from 'react';

//JobDetailPage component
const JobDetailPage = (props) => {
  const renderDetails = () => {
    if(props.selectedJobs.length) {
      return props.selectedJobs.map((details) => {
        return (
          <div className="container" key={details.jobId}>
            <h1>Job {details.jobId}</h1>
            <ul>
              <li>Name: {details.job.renderApp.name}</li>
              <li>Version: {details.job.renderApp.version}</li>
              <li>Avail Memory MB: {details.job.availMemoryMB}</li>
              <li>Renderer Name: {details.job.renderApp.rendererName }</li>
              <li>Renderer Version: {details.job.renderApp.rendererVersion}</li>
              <li>Max Job Thread: {details.job.maxJobThreads}</li>
              <li>Camera: {details.job.camera}</li>
              <li>Layer: {details.job.layer}</li>
              <li>Channel: {details.job.channel}</li>
              <li>Scene Name: {details.job.sceneName}</li>
              <li>Image Dir: {details.job.imageDir}</li>
              <li>Image File Name: {details.job.imageFileName}</li>
              <li>Image Width: {details.job.imageWidth}</li>
              <li>Image Height: {details.job.imageHeight}</li>
              <li>Seq Start: {details.job.seqStart}</li>
              <li>Seq End: {details.job.seqEnd}</li>
              <li>Seq Step: {details.job.seqStep}</li>
              <li>Frames Done: {details.job.framesDone}</li>
              <li>Frames Left: {details.job.framesLeft}</li>
              <li>Username: {details.job.userName}</li>
              <li>Submit Machine: {details.job.submitMachine}</li>
              <li>Error Count: {details.job.errorCount}</li>
            </ul>
          </div>
        );
      });
    } else {
      return (
        <div className="container">
          <h1>No Job Selected</h1>
        </div>
      );
    }
  }

  return (
    <div>
      <h1>Details</h1>
      <button onClick={props.goBackToJobs}>Back</button>
      {renderDetails()}
    </div>
  );
}

// renderApp.versionMinorDisplay ()
export default JobDetailPage;
