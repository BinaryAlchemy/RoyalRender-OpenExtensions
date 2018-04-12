'use strict';

import React from 'react';
import Header from './header.jsx';
import Main from './main.jsx';
import {NotificationContainer} from 'react-notifications';

export default () => {
  return (
    <div>
      <Header/>
      <Main/>
      <NotificationContainer/>
    </div>
  );
}
