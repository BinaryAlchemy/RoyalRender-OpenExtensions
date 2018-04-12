'use strict';

import React from 'react';
import { Link } from 'react-router-dom';

//ClientsDetailsPage component
const ClientDetailsPage = (props) => {
  const renderDetails = () => {
    if(props.selectedClients.length) {
      return props.selectedClients.map((details) => {
        return (
          <div className="container" key={details.clientId}>
            <h1>{details.client.name}</h1>
            <ul>
              <li>Surname: {details.client.name}</li>
              <li>CPU Usage: {details.CPUJob}</li>
              <li>Avail Memory MB: {details.client.availMemoryMB}</li>
              <li>Temp HDD: {details.client.tempHHD}</li>
              <li>Logged User: {details.client.loggedUser}</li>
              <li>Job Thread: {details.client.maxJobThreads}</li>
            </ul>
            <br/>
          </div>
        );
      });
    } else {
      return (
        <div className="container">
          <h1>No Client Selected</h1>
        </div>
      );
    }

  }

  return (
    <div>
      <h1>Details</h1>
      <button onClick={props.goBack}>Back</button>
      {renderDetails()}
    </div>
  );
}

export default ClientDetailsPage;
