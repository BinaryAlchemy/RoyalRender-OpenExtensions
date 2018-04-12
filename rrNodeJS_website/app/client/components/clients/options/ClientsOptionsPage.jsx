'use strict';

import React from 'react';
import buttons from '../../../../../config/buttons.clients.js'

//OptionsPage component
const OptionsPage = (props) => {

  const renderSeletedPage = () => {
    const optionPage = props.renderOptionPage;
    switch(optionPage) {
      case 'check':
        return null;
      case 'command':
        return null;
      case 'details':
        return null;
      case 'filterdropdowny':
        return null;
      case 'commandx':
        return null;
      case 'update':
        return null;
      default:
        return null;
    }
  }

  const renderButton = () => {
    return buttons.map((button, index) => {
      if(button.display) {
        return (
          <button key={button.buttonName} className="button" onClick={() => props.buttonAction(button.buttonMethod, button.index)}>{button.buttonName}</button>
        )
      }
    })
  }

  return (
    <div className="clientOptions">
      <hr/>
      {renderButton()}
      <button className="button" onClick={() => props.showClientsDetails()}>Details</button>
      <button className="button" onClick={() => props.updateClients()}>Update</button>
      <hr/>
      {renderSeletedPage()}
    </div>
  )
}

export default OptionsPage;
