/**
 * Created by fz on 2017/2/16.
 */
import React, {Component, PropTypes} from 'react';
import {render} from 'react-dom';
import {IntlProvider, addLocaleData} from 'react-intl';
import en from 'react-intl/locale-data/en';
import zh from 'react-intl/locale-data/zh';
import zh_CN from './zh_CN.js';
import en_US from './en_US.js';

//需要本地化的语言
addLocaleData([...en, ...zh]);

function chooseLocale() {
    switch (navigator.language.split('_')[0]) {
        case 'en':
            return 'en_US';
            break;
        case 'zh':
            return 'zh_CN';
            break;
        default:
            return 'en_US';
            break;
    }
}

class Translate extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        //this.props.Template 父级传来的 this.props.Template
        return (
            //<IntlProvider locale={ navigator.language.split('_')[0] } messages={ chooseLocale() }>
            //      {this.props.Template}
            //</IntlProvider>
            <IntlProvider locale={ 'zh' } messages={ zh_CN }>
                {this.props.Template}
            </IntlProvider>
        );
    }
}

module.exports = Translate;