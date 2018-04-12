'use strict';

import React from 'react';

import ClientsExpandedTablePage from './ClientsExpandedTablePage.jsx';
import ClientsTableBodyPage from './ClientsTableBodyPage.jsx';


//TablePage component
const ClientsTablePage = (props) => {

  const tableBody = () => {
    return props.clientDetails.map((client, index) => {
      return (
        <ClientsTableBodyPage
          key={`keyitem${client}${index}`}
          index={index}
          clientDetail={client}
          selectedClients={props.selectedClients}
          handleRowClick={props.handleRowClick}
        />
      );
    });
  }

  return (
    <div>
      <table className="table-responsive">
      	<thead>
          <tr>
            <th></th>
            <th>Surname</th>
            <th>Max Job Threads</th>
            <th>CPU Usage</th>
            <th>Avail Memory MB</th>
            <th>Temp HDD</th>
            <th>Status</th>
          </tr>
      	</thead>
        <tbody className="labels">
      	{tableBody()}
        </tbody>
      </table>
    </div>
  );
};

export default ClientsTablePage;
