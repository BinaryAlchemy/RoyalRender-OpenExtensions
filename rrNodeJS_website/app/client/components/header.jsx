'use strict';

import React from 'react';
import { Link, browserHistory, Router } from 'react-router-dom';
import axios from 'axios';
import {NotificationManager} from 'react-notifications';

class Header extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      checkLoggedUser: false,
      token: ''
    }
    this.userLogged = this.userLogged.bind(this);
  }

  componentWillMount() {
    this.userLogged();
  }

  componentWillUpdate(nextProps, nextState) {
    if((this.state.checkLoggedUser != nextState.checkLoggedUser) ||
      (localStorage.getItem("token") != this.state.token)) {
        this.userLogged();
      }
  }

  userLogged() {
    let token = localStorage.getItem("token");
    this.setState({token:token});
    let that = this;
    if(token) {
      axios.defaults.headers.token = token;
      axios.post('/api/logged-user')
        .then(function (response) {
          if(response.data.user == "notlogged") {
            that.setState({'checkLoggedUser':false});
          } else {
            that.setState({'checkLoggedUser':true});
          }
        })
        .catch(function (error) {
          console.log(error);
        });
    } else {
      that.setState({'checkLoggedUser':false});
    }
  }

  logoutUser() {
    localStorage.setItem("token", null);
    let that = this;
    axios.get('/api/logout')
      .then(function (response) {
        that.setState({'checkLoggedUser':false});
        NotificationManager.info("You have been logged out")
      })
      .catch(function (error) {
        console.log(error);
        NotificationManager.error('Error', error);
      });
  }

  render() {
    return (
      <header>
        <nav className="navbar navbar-default">
          <div className="container-fluid">
            <div className="navbar-header">
              <Link to='/' className="navbar-brand">Royal Render</Link>
            </div>
            {this.state.checkLoggedUser?
              <ul className="nav navbar-nav">
                  <li className="active"><Link to="/">Home</Link></li>
                  <li><Link to="/clients">Clients</Link></li>
                  <li><Link to="/jobs">Jobs</Link></li>
                  <li><Link to="/" onClick={() => this.logoutUser()}>Logout</Link></li>
              </ul>
            :
              <ul className="nav navbar-nav">
                  <li className="active"><Link to="/login">Login</Link></li>
              </ul>
            }
          </div>
        </nav>
      </header>
    );
  }

}

export default Header;
