'use strict';

import React from 'react';
import axios from 'axios';
import { NotificationManager } from 'react-notifications';

import ClientsOptionsPage from './options/ClientsOptionsPage.jsx';
import ClientsTablePage from './tablePage/ClientsTablePage.jsx';
import ClientsDetailsPage from './details/ClientDetailsPage.jsx'


//Clients component
class Clients extends React.Component {
  constructor(props){
    super(props);
    this.state = {
      clients: [],
      selectedClients: [],
      renderClientDetails: false,
    };
  }

  componentWillMount() {
    this.renderClients();
  }

  renderClients() {
    let that = this;
    axios.get('/api/clients-details')
    .then(function (response) {
      if(response.data.err) {
        that.props.history.push('/login');
        return;
      }
      that.setState({clients:response.data});
    })
    .catch(function (error) {
      console.log(error);
      NotificationManager.error(error, "Error Getting Clients");
    });
  }

  handleRowClick(details) {
    var selectedClients = this.state.selectedClients.slice()
    let index = selectedClients.findIndex(x => x.clientId == details.clientId)
    if (index != -1) selectedClients.splice(index, 1);
    else selectedClients.push(details)
    this.setState({ selectedClients: selectedClients })
  }

  showClientsDetails() {
    this.setState({renderClientDetails: true});
  }

  goBack() {
    this.setState({renderClientDetails: false});
  }

  buttonAction(method, index) {
    let selectedClient = [];
    this.state.selectedClients.map(clientList => {
      selectedClient.push(clientList.client);
    });
    let that = this;
    if(!selectedClient.length) {
      NotificationManager.error("Select Client");
      return;
    }

    axios.post('/api/client-send-command', {
        clientList: selectedClient,
        method: method,
        index: index
    })
    .then(function (response) {
      if(response.data.err) {
        that.props.history.push('/login');
        NotificationManager.error(response.data.err, "Error");
        return;
      }
      NotificationManager.success("Command Successfull");
    })
    .catch(function (error) {
      console.log(error);
      NotificationManager.error(error, "Command Error");
    });
  }

  setSelectedButton(value) {
    if(value == this.state.renderOptionPage)
      this.setState({renderOptionPage:null});
    else
      this.setState({renderOptionPage:value});
  }

  updateClients() {
      this.setState({
        clients: [],
        selectedClients: [],
        renderClientDetails: false,
      });
      this.renderClients();
      NotificationManager.info("Clients Updated");
  }

  render() {
    return (
      <div className="container">
        {this.state.renderClientDetails?
            <ClientsDetailsPage
              selectedClients={this.state.selectedClients}
              goBack={this.goBack.bind(this)}
            />
          :
            <div>
              <ClientsOptionsPage
                updateClients={this.updateClients.bind(this)}
                buttonAction={this.buttonAction.bind(this)}
                showClientsDetails={this.showClientsDetails.bind(this)}
                setSelectedButton={this.setSelectedButton.bind(this)}
                {...this.state}
              />
              <ClientsTablePage
                selectedClients={this.state.selectedClients}
                clientDetails={this.state.clients}
                history={this.props.history}
                handleRowClick={this.handleRowClick.bind(this)}
              />
            </div>
        }
      </div>
    )
  }
};

export default Clients;
