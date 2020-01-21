var path = require('path');
var webpack = require('webpack');
var htmlWebpackPlugin = require('html-webpack-plugin');
var babelPresets = {presets: ['react', 'es2015']};


module.exports = {
    entry: {
        index: path.resolve(__dirname, './js/index.js'),
    },
    output: {
        filename: '[name].bundle.js',
        path: path.join(__dirname, 'dist'),
        //publicPath: '/static',
    },
    module: {
        loaders: [
            {
                test: /\.json$/,
                loader: ['json']
            },
            {
                test: /\.jsx?$/,
                //loaders: ['react-hot', 'babel'],
                exclude: /(node_modules|bower_components)/,
                loaders: ['react-hot', 'jsx', 'babel?'+JSON.stringify(babelPresets)],
            },
            {
                test: /\.(css | scss)$/,
                loaders: ['style', 'css']
            },
            {
                test: /\.less$/,
                loaders: ['style', 'css', 'less']
            },
            {
                test: /\.(png|jpg|jpeg|gif)$/,
                loaders: ['url']
            },
            {
                test: /\.woff(\?v=\d+\.\d+\.\d+)?$/,
                loaders: ['url']
            },
            {
                test: /\.woff2(\?v=\d+\.\d+\.\d+)?$/,
                loaders: ['url']
            },
            {
                test: /\.ttf(\?v=\d+\.\d+\.\d+)?$/,
                loaders: ['url']
            },
            {
                test: /\.eot(\?v=\d+\.\d+\.\d+)?$/,
                loaders: ['file']
            },
            {
                test: /\.svg(\?v=\d+\.\d+\.\d+)?$/,
                loaders: ['url']
            },
        ]
    },
    resolve: {
        extensions: ['*', '.js', '.jsx', '.css']
    },
    resolveLoader: {
        moduleExtensions: ['-loader']
    },
    plugins: [
        new htmlWebpackPlugin({
            title: 'React Biolerplate by Fangzhenmu',
            filename: 'index.html',
            //template: path.resolve(__dirname, 'dist/index.ejs'),
            //inject: 'body'
        }),                                                                    //自动生成index.html
        new webpack.BannerPlugin("copyright @fangzhengmu novigo.com"),  //这里是打包文件头部注释
    ]
}