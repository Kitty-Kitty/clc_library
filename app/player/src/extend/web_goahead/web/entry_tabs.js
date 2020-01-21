import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import getMuiTheme from 'material-ui/styles/getMuiTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import {Tabs, Tab} from 'material-ui/Tabs';
// From https://github.com/oliviertassinari/react-swipeable-views
import SwipeableViews from 'react-swipeable-views';
import FontIcon from 'material-ui/FontIcon';
import IconLocationOn from 'material-ui/svg-icons/communication/location-on';
import MapsPersonPin from 'material-ui/svg-icons/maps/person-pin';
import {BottomNavigation, BottomNavigationItem} from 'material-ui/BottomNavigation';
import Paper from 'material-ui/Paper';
import {Toolbar, ToolbarGroup, ToolbarSeparator, ToolbarTitle} from 'material-ui/Toolbar';
import Badge from 'material-ui/Badge';
import IconButton from 'material-ui/IconButton';
import NotificationsIcon from 'material-ui/svg-icons/social/notifications';
import injectTapEventPlugin from 'react-tap-event-plugin';


injectTapEventPlugin();


const recentsIcon = <IconLocationOn />;
const favoritesIcon = <IconLocationOn />;
const nearbyIcon = <IconLocationOn />;


const styles = {
    headline: {
        fontSize: 24,
        paddingTop: 16,
        marginBottom: 12,
        fontWeight: 400,
    },
    slide: {
        padding: 10,
    },
    paper:{

       height: 830,
       // width: 1800,
        margin: 0,
        textAlign: 'center',
        display: 'inline-block',
    },
    toolbar :{
        margin: 0,
    }
};


const BadgeExampleSimple = () => (
  <div>
    <Badge
      badgeContent={4}
      primary={true}
    >
      <NotificationsIcon />
    </Badge>
    <Badge
      badgeContent={10}
      secondary={true}
      badgeStyle={{top: 12, right: 12}}
    >
      <IconButton tooltip="Notifications">
        <NotificationsIcon />
      </IconButton>
    </Badge>
  </div>
);


export default class TabsExampleSwipeable extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            slideIndex: 0,
        };
    }

    handleChange = (value) => {
        this.setState({
            slideIndex: value,
        });
    };

    render() {
        return (
            <div>
                <Tabs
                    onChange={this.handleChange}
                    value={this.state.slideIndex}
                >
                    <Tab
                        icon={<FontIcon className="material-icons">phone</FontIcon>}
                        label="RECENTS"
                        value={0}
                    />
                    <Tab
                        icon={<FontIcon className="material-icons">favorite</FontIcon>}
                        label="当前"
                        value={1}
                    />
                    <Tab
                        icon={<MapsPersonPin />}
                        label="系统"
                        value={2}
                    />
                </Tabs>
                <SwipeableViews
                    index={this.state.slideIndex}
                    onChangeIndex={this.handleChange}
                >
                    <div>

                    </div>
                    <div style={styles.slide}>

                    </div>
                    <div style={styles.slide}>

                    </div>
                </SwipeableViews>
            </div>
        );
    }
}

class ToolbarExamplesSimple extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            value: 3,
        };
    }

    handleChange = (event, index, value) => this.setState({value});

    render() {
        return (
            <Toolbar>
                <ToolbarGroup firstChild={true}>

                </ToolbarGroup>
                <ToolbarGroup style={styles.paper}>
                    <ToolbarTitle text="Options" />
                </ToolbarGroup>
            </Toolbar>
        );
    }
}


/**
 * A simple example of `BottomNavigation`, with three labels and icons
 * provided. The selected `BottomNavigationItem` is determined by application
 * state (for instance, by the URL).
 */
class CssBottomNavigation extends Component {
  state = {
    selectedIndex: 0,
  };

  select = (index) => this.setState({selectedIndex: index});

  render() {
    return (
      <Paper zDepth={1}>
        <BottomNavigation selectedIndex={this.state.selectedIndex}>
          <BottomNavigationItem
            label="视图"
            icon={recentsIcon}
            onTouchTap={() => this.select(0)}
          />
          <BottomNavigationItem
            label="屏组"
            icon={favoritesIcon}
            onTouchTap={() => this.select(1)}
          />
          <BottomNavigationItem
            label="布局"
            icon={recentsIcon}
            onClick={() => this.select(2)}
          />
          <BottomNavigationItem
            label="场景"
            icon={recentsIcon}
            onClick={() => this.select(3)}
          />
          <BottomNavigationItem
            label="预案"
            icon={recentsIcon}
            onClick={() => this.select(4)}
          />
          <BottomNavigationItem
            label="预监"
            icon={recentsIcon}
            onClick={() => this.select(5)}
          />
        </BottomNavigation>
      </Paper>
    );
  }
}


const App = () => (
    <MuiThemeProvider muiTheme={getMuiTheme()}>
        <div>
            <TabsExampleSwipeable />
            <ToolbarExamplesSimple/>
            <Paper zDepth={1} style={styles.paper}/>
            <CssBottomNavigation/>
        </div>
    </MuiThemeProvider>
);

let app = document.createElement('div');
ReactDOM.render(<App />, app);
document.body.appendChild(app);
