'use strict';

import React from 'react';
import ReactDOM from 'react-dom';
import MemoryRouter from 'react-router/MemoryRouter';

//import { Router, Route, IndexRoute, browserHistory } from 'react-router';
import { HashRouter, BrowserRouter } from 'react-router-dom';

import App from './components/app.jsx';

//Connecting React Component with DOM Element
ReactDOM.render(
  <BrowserRouter>
    <App/>
  </BrowserRouter>,
  document.getElementById('app'));
