import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import getMuiTheme from 'material-ui/styles/getMuiTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import FontIcon from 'material-ui/FontIcon';
import {BottomNavigation, BottomNavigationItem} from 'material-ui/BottomNavigation';
import Paper from 'material-ui/Paper';
import IconLocationOn from 'material-ui/svg-icons/communication/location-on';
import AppBar from 'material-ui/AppBar';
import {Tabs, Tab} from 'material-ui/Tabs';
import MapsPersonPin from 'material-ui/svg-icons/maps/person-pin';



const recentsIcon = <FontIcon className="material-icons">restore</FontIcon>;
const favoritesIcon = <FontIcon className="material-icons">favorite</FontIcon>;
const nearbyIcon = <IconLocationOn />;


const TabsExampleIconText = () => (
    <Tabs>
        <Tab
            icon={<FontIcon className="material-icons">phone</FontIcon>}
            label="RECENTS"
        />
        <Tab
            icon={<FontIcon className="material-icons">favorite</FontIcon>}
            label="FAVORITES"
        />
        <Tab
            icon={<MapsPersonPin />}
            label="NEARBY"
        />
    </Tabs>
);



const style = {
    height: 100,
    width: 100,
    margin: 20,
    textAlign: 'center',
    display: 'inline-block',
};

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
            <div>
                <TabsExampleIconText/>
                <AppBar title="成都洛维格科技有限公司" />
                <div>
                    <Paper style={style} zDepth={1} />
                    <Paper zDepth={1} >
                        <BottomNavigation selectedIndex={this.state.selectedIndex}>
                            <BottomNavigationItem
                                label="Recents"
                                icon={recentsIcon}
                                onTouchTap={() => this.select(0)}
                            />
                            <BottomNavigationItem
                                label="Favorites"
                                icon={favoritesIcon}
                                onTouchTap={() => this.select(1)}
                            />
                            <BottomNavigationItem
                                label="Nearby"
                                icon={nearbyIcon}
                                onTouchTap={() => this.select(2)}
                            />
                        </BottomNavigation>
                    </Paper>
                    <Paper style={style} zDepth={1} />
                </div>
            </div>
        );
    }
}



const PaperExampleSimple = () => (
    <div>
        <Paper style={style} zDepth={1} />
        <Paper style={style} zDepth={2} />
        <Paper style={style} zDepth={3} />
        <Paper style={style} zDepth={4} />
        <Paper style={style} zDepth={5} />
    </div>
);

const App = () => (
    <MuiThemeProvider muiTheme={getMuiTheme()}>
        <CssBottomNavigation />
    </MuiThemeProvider>
);

let app = document.createElement('div');
ReactDOM.render(<App />, app);
document.body.appendChild(app);