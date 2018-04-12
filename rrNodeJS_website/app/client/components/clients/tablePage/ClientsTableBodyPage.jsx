'use strict';

import React from 'react';

//ClientsTableBodyPage component
const ClientsTableBodyPage = (props) => {
  const isActive = (value) => {
    if(props.selectedClients.length) {
      let selectedClients = props.selectedClients;
      let i = 0;
      for(i in selectedClients) {
        if(value===selectedClients[i].clientId) {
          return 'activeJob';
        }
      }
    } else {
      return '';
    }
  }

  let clientDetail = props.clientDetail;
  return (
    <tr className={'bar '+isActive(clientDetail.clientId)} onClick={() => props.handleRowClick(clientDetail)}>
      <td><input type="checkbox" checked={isActive(clientDetail.clientId)=='activeJob'?true:false} /></td>
      <td>
        {clientDetail.client.name}
      </td>
      <td>{clientDetail.client.maxJobThreads}</td>
      <td>{clientDetail.CPUJob}</td>
      <td>{clientDetail.client.availMemoryMB}</td>
      <td>{clientDetail.client.tempHDD}</td>
      <td>{clientDetail.clientStatus}</td>
    </tr>
  )
};

export default ClientsTableBodyPage;
