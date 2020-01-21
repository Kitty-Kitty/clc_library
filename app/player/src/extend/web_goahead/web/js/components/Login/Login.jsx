/**
 * Created by fz on 2017/2/16.
 */
import React, {Component, PropTypes} from 'react';
import Paper from 'material-ui/Paper';
import LoginLogo from './LoginLogo';
import LoginPanel from './LoginPanel'


const getStyles = (props, context, state) => {
    //const {paper} = context.muiTheme;

    const styles = {
        container: {
            margin: 0,
            width: '100%',
            height: '100%',
            textAlign: 'center',
            paddingTop: '10%',
        },
        paper: {
            height: 250,
            width: 450,
            //align: 'center',
            margin: 0,
            textAlign: 'center',
            display: 'inline-block',
        },
    };

    return styles;
};

class Login extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const styles = getStyles(this.props, this.context, this.state);
        return (
            <div style={styles.container}>
                <Paper style={styles.paper} zDepth={1} rounded={false}>
                    <LoginLogo/>
                    <LoginPanel/>
                </Paper>
            </div>
        );
    }
}

export default Login ;
