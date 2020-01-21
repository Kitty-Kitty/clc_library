import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import {Login} from './components';
import LightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import GetMuiTheme from 'material-ui/styles/getMuiTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import Translate  from './locale/Translate'
import InjectTapEventPlugin from 'react-tap-event-plugin';

// Needed for onTouchTap
// http://stackoverflow.com/a/34015469/988941
InjectTapEventPlugin();


const App = () => (
    <MuiThemeProvider muiTheme={GetMuiTheme(LightBaseTheme)}>
        <Login></Login>
    </MuiThemeProvider>
);

let app = document.createElement('div');

ReactDOM.render(
    <Translate Template={<App/>}/>,
    app
);
document.write("<style type='text/css'>body{text-align:center;}</style>");
document.body.appendChild(app);