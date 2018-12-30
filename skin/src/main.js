import Vue from 'vue'
import App from './App.vue'
import store from './store'
import storePlugin from './storePlugin'

import './assets/globalstyle.less'

Vue.use(storePlugin)

// eslint-disable-next-line
var vm = new Vue({
  el: '#app',
  store,

  render: function (h) {
    return h(App)
  },

  data: {
    current: ''
  }
})

var showPage = function (page, data) {
  vm.$store.commit('setPayload', data)
  vm.$store.commit('activatePage', page)

  if (typeof data.menucategory !== 'undefined') {
    vm.$store.commit('activateMenu', data.menucategory)
  }
}

window.showPage = showPage
