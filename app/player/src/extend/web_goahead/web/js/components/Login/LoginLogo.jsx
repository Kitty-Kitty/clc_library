/**
 * Created by fz on 2017/2/16.
 */
import React, {Component} from 'react';
import Paper from 'material-ui/Paper';
import Chip from 'material-ui/Chip';
import IconSpeaker from 'material-ui/svg-icons/hardware/speaker';
import {grey400, grey300} from 'material-ui/styles/colors';
import {FormattedMessage, defineMessages} from 'react-intl';


const getStyles = (props, context, state) => {
    // const {
    //     baseTheme,
    //     svgIcon: {
    //         color,
    //     },
    // } = context.muiTheme;

    const styles = {
        paper: {
            //height: '100%',
            width: '40%',
            //align: 'center',
            margin: 0,
            textAlign: 'center',
            display: 'inline-block',
        },
        icon: {
            // marginRight: 3,
            // marginBottom: 0,
            width: '100%',
            height: '100%',
            color: grey400,
        },
        text: {
            fontWeight: 300,
            fontSize: 14,
            textTransform: 'uppercase',
            padding: 0,
        },
        chip: {
            //margin: 2,
            display: 'inline-block',
            color: grey300,
        }
    };

    return styles;
};

const messages = defineMessages({
    "login.logo": {
        id: 'login.logo',
        defaultMessage: 'audio device',
        description: 'audio device',
    },
});

class LoginLogo extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const styles = getStyles(this.props, this.context, this.state);
        return (
            <Paper style={styles.paper} zDepth={0} rounded={false}>
                <IconSpeaker style={styles.icon}/>
                <br />
                <Chip style={styles.chip} backgroundColor={grey300}>
                    <FormattedMessage {...messages["login.logo"]}/>
                </Chip>
            </Paper>
        );
    }
}

export default LoginLogo ;
