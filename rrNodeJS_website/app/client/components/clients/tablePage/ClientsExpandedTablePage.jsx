'use strict';

import React from 'react';
import { BootstrapTable, TableHeaderColumn } from 'react-bootstrap-table';


//ClientsExpandedTablePage component
class ClientsExpandedTablePage extends React.Component {
  render() {
    if (this.props.data) {
      return (
        <tr className="drop-list ">
          <td>
            <p className="line client-name">.....</p>
            <span className="client-name">FGFGFFGJGGG</span>
          </td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
          <td>$7,685.00</td>
          <td>$3,544.00</td>
          <td>$5,834.00</td>
          <td>$10,583.00</td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
      );
    } else {
      return (<p>?</p>);
    }
  }
}

export default ClientsExpandedTablePage;
