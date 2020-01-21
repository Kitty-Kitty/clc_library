/**
 * Created by fz on 2017/2/16.
 */
import React from 'react';
import Paper from 'material-ui/Paper';
import {FormattedMessage} from 'react-intl';

const style = {
    height: 100,
    width: 100,
    margin: 20,
    textAlign: 'center',
    display: 'inline-block',
};

const Login = () => (
    <div>
        <Paper style={style} zDepth={1} rounded={false} >
            <h1>
                <FormattedMessage
                    id="userName"
                    defaultMessage='userName'
                    description='user name'
                />
            </h1>
        </Paper>
    </div>
);

export default Login;

