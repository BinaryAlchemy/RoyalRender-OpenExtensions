'use strict';

import React from 'react';
import axios from 'axios';
import {NotificationContainer, NotificationManager} from 'react-notifications';

//Login component
export default class Login extends React.Component {
  constructor() {
    super();
    this.state = {
      username: '',
      password: '',
    };
    this.submitLogin = this.submitLogin.bind(this);
  }

  submitLogin(e) {
    e.preventDefault();
    const that = this;
    axios.post('/api/login', {
        username: this.state.username,
        password: this.state.password
    })
    .then(function (response) {
      if(response.data) {
        localStorage.setItem("token", response.data);
        that.setState({username:'', password:''});
        NotificationManager.success('Logged In');
        that.props.history.push('/');
      } else {
        NotificationManager.error('Enter correct login details', 'Invalid Details');
        // alert("Enter correct details");
      }

    })
    .catch(function (error) {
      console.log(error);
    });
  }

  render() {
    return (
      <form className="form-horizontal">
        <div className="form-group">
          <label className="control-label col-sm-2" htmlFor="username">Username:</label>
          <div className="col-sm-10">
            <input type="text" onChange={(e) => this.setState({username: e.target.value})} className="form-control" id="email" />
          </div>
        </div>
        <div className="form-group">
          <label className="control-label col-sm-2" htmlFor="password">Password:</label>
          <div className="col-sm-10">
            <input type="password" onChange={(e) => this.setState({password: e.target.value})} className="form-control" id="password" />
          </div>
        </div>
        <div className="form-group">
          <div className="col-sm-offset-2 col-sm-10">
            <div className="checkbox">
              <label><input type="checkbox" /> Remember me</label>
            </div>
          </div>
        </div>
        <div className="form-group">
          <div className="col-sm-offset-2 col-sm-10">
            <button type="submit" onClick={this.submitLogin} className="btn btn-default">Login</button>
          </div>
        </div>
      </form>
    );
  }
};
