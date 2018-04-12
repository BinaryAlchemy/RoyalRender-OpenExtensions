'use strict';

import React from 'react';
import { Switch, Route, Router } from 'react-router-dom';
import Home from './home/Home.jsx';
import Login from './login/Login.jsx';
import Clients from './clients/Clients.jsx';
import Jobs from './jobs/Jobs.jsx';
import ClientDetailsPage from './clients/details/ClientDetailsPage.jsx';

export default () => {
  return (
    <section>
      <Switch>
        <Route exact path='/' component={Home}/>
        <Route path='/login' component={Login}/>
        <Route path='/clients' component={Clients}/>
        <Route path='/jobs' component={Jobs}/>
      </Switch>
    </section>
  );
}
