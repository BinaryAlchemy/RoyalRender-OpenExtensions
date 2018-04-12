'use strict';

import React from 'react';
import FilterOptionPage from './FilterOptionPage.jsx';
import buttons from '../../../../../config/buttons.jobs.js';

//OptionsPage component
const JobsOptionsPage = (props) => {

  const renderSeletedPage = () => {
    const optionPage = props.renderOptionPage;
    switch(optionPage) {
      case 'filter':
        return <FilterOptionPage {...props}/>;
      default:
        return null;
    }
  }

  const renderButton = () => {
    return buttons.map((button, index) => {
      if(button.display) {
        return (
          <button key={button.buttonName} className="button" onClick={() => props.buttonAction(button.buttonMethod, button.index)}>{button.buttonName}</button>
        );
      }
    });
  }

  return (
    <div className="jobOptions">
      <hr/>
      <button className="button" onClick={() => props.setSelectedButton("filter")}>Filter</button>
      {renderButton()}
      <button className="button" onClick={() => props.showJobsDetails()}>Details</button>
      <button className="button" onClick={() => props.updateJobs()}>Update</button>
      <hr/>
      {renderSeletedPage()}
    </div>
  );
}


export default JobsOptionsPage;
