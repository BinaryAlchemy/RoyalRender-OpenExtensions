'use strict';

import React from 'react';
import axios from 'axios';

import JobsExpandedTablePage from './JobsExpandedTablePage.jsx';
import JobsTableBodyPage from './JobsTableBodyPage.jsx';


//TablePage component
const JobsTablePage = (props) => {

  const renderTableBody = () => {
    if(props.jobs) {
      return props.jobs.map((jobDetails, index) => {
        return (
          <JobsTableBodyPage
            key={`jobkey${index}`}
            jobDetails={jobDetails}
            selectedJobs={props.selectedJobs}
            handleRowClick={props.handleRowClick}
          />
        );
      });
    } else {
      return null
    }
  }

  return (
    <div className="table-responsive">
      <table className="">
      	<thead>
          <tr>
            <th></th>
            <th>IDstr</th>
            <th>renderApp.name</th>
            <th>renderApp.rendererName</th>
            <th>scene display name</th>
            <th>layer</th>
            <th>seqStart</th>
            <th>SEQEND</th>
            <th>seqStep</th>
            <th>frame done</th>
            <th>frame left</th>
            <th>status</th>
            <th>username</th>
            <th>client rendering count</th>
            <th>error count</th>
          </tr>
      	</thead>
        <tbody className="labels">
      	   {renderTableBody()}
        </tbody>
      </table>
    </div>
  );
};

export default JobsTablePage;
