'use strict'

const isProduction = process.env.NODE_ENV === 'production'
const glob = require('glob')
const pages = {}

glob.sync('./src/**/main.js').forEach(path => {
  const chunk = path.split('./src/')[1].split('/main.js')[0]
  pages[chunk] = {
    entry: path,
    template: 'public/index.html',
    chunks: ['chunk-vendors', 'chunk-common', chunk]
  }
})

module.exports = {
  baseUrl: isProduction ? './' : '',
  pages,
  chainWebpack: config => config.plugins.delete('named-chunks'),
  devServer: {
    proxy: {
      '/api': {
        target: 'http://127.0.0.1:8080',
        changeOrigin: true,
        pathRewrite: { '^/api': '' }
      }
    }
  }
}