/**
 * Created by fz on 2017/2/16.
 */
import React, {Component, PropTypes} from 'react';
import Paper from 'material-ui/Paper';
import TextField from 'material-ui/TextField';
import FlatButton from 'material-ui/FlatButton';
import IconPerson from 'material-ui/svg-icons/social/person';
import IconLock from 'material-ui/svg-icons/action/lock';
import {grey500} from 'material-ui/styles/colors';
import {FormattedMessage, defineMessages} from 'react-intl';


const getStyles = (props, context, state) => {
    // const {
    //     baseTheme,
    //     svgIcon: {
    //         color,
    //     },
    // } = context.muiTheme;

    const styles = {
        button: {
            margin: 10,
            width: '70%',
            fontWeight: 300,
            fontSize: 14,
            textTransform: 'uppercase',
            padding: 0,
        },
        icon: {
            marginRight: 3,
            marginBottom: -10,
            width: 32,
            height: 32,
            color: grey500,
        },
        paper: {
            //height: '99%',
            width: '60%',
            //align: 'center',
            margin: 0,
            textAlign: 'left',
            display: 'inline-block',
        },
        textField: {
            width: '60%',
        },
    };

    return styles;
};

const messages = defineMessages({
    "login.userName": {
        id: 'login.userName',
        defaultMessage: 'userName',
        description: 'user name',
    },
    "login.userPassword": {
        id: 'login.userPassword',
        defaultMessage: 'userName',
        description: 'user name',
    },
    "login.userInput": {
        id: 'login.userInput',
        defaultMessage: 'input',
        description: 'user input',
    },
    "login.submit": {
        id: 'login.submit',
        defaultMessage: 'submit',
        description: 'user submit',
    },
});

class LoginPanel extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const styles = getStyles(this.props, this.context, this.state);
        return (
            <Paper style={styles.paper} zDepth={0} rounded={false}>
                <IconPerson style={styles.icon}/>
                <TextField
                    style={styles.textField}
                    hintText={<FormattedMessage {...messages["login.userInput"]} />}
                    floatingLabelText={<FormattedMessage {...messages["login.userName"]} /> }
                /><br />
                <IconLock style={styles.icon}/>
                <TextField
                    style={styles.textField}
                    hintText={<FormattedMessage {...messages["login.userInput"]} />}
                    floatingLabelText={<FormattedMessage {...messages["login.userPassword"]} />}
                    type="password"
                /><br />
                <FlatButton label={<FormattedMessage {...messages["login.submit"]} />} style={styles.button}/>
            </Paper>
        );
    }
}

export default LoginPanel ;
