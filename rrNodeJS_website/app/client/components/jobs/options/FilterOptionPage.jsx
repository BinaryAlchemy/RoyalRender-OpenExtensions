'use strict';

import React from 'react';


//OptionsPage component
const FilterOptionPage = (props) => {
  const renderFilterOptions = (options) => {
    if(options) {
      return options.map((value, index) => {
        return <option key={value+index} value={value}>{value}</option>;
      });
    } else {
      return null;
    }
  }

  return (
    <div className="container">
      <div className="filterContainer">
        <div>
          <label>Project:</label>
            <select id="projectSelect" name="projectSelect" onChange={(e) => props.updateSelectedOption(e)}>
              <option>--all--</option>
              {renderFilterOptions(props.projectOptions)}
            </select>
        </div>
        <div>
          <label>User:</label>
            <select id="userSelect" name="userSelect" onChange={(e) => props.updateSelectedOption(e)}>
              <option>--all--</option>
              {renderFilterOptions(props.userOptions)}
            </select>
        </div>
        <div>
          <label>App:</label>
          <select id="appSelect" name="appSelect" onChange={(e) => props.updateSelectedOption(e)}>
            <option>--all--</option>
            {renderFilterOptions(props.appOptions)}
          </select>
        </div>
      </div>
      <div className="filterCheckBox">
        <div className="checkbox">
          <label><input type="checkbox" onClick={(e) => props.updateFilterChecks("notRendering", e.target.checked)} />Not Rendering</label>
        </div>
        <div className="checkbox">
          <label><input type="checkbox" onClick={(e) => props.updateFilterChecks("isRendering", e.target.checked)} />Rendering</label>
        </div>
        <div className="checkbox">
          <label><input type="checkbox" onClick={(e) => props.updateFilterChecks("isDisabled", e.target.checked)} />Disabled</label>
        </div>
        <div className="checkbox">
          <label><input type="checkbox" onClick={(e) => props.updateFilterChecks("isWaitFor", e.target.checked)} />Waiting For</label>
        </div>
        <div className="checkbox">
          <label><input type="checkbox" onClick={(e) => props.updateFilterChecks("isFinished", e.target.checked)} />Finished</label>
        </div>
      </div>
      <div className="invert">
        <p>Include ...</p>
        <div className="checkbox">
          <label><input type="checkbox" onChange={(e) => props.updateFilterChecks("invert", e.target.checked)} />Update invert search</label>
        </div>
      </div>
    </div>
  );
}



export default FilterOptionPage;
