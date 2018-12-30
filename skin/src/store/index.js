import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const state = {
  currentPage: '',
  currentMenu: -2,

  payload: ''
}

const mutations = {
  activatePage (state, page) {
    state.currentPage = page
  },

  activateMenu (state, menu) {
    state.currentMenu = menu
  },

  setPayload (state, data) {
    // console.log('In SetPayload: ' + JSON.stringify(data))
    state.payload = data
  }
}

const actions = {
  showPage (context, data) {
    context.commit('setPayload', data.data)
    context.commit('activatePage', data.page)

    if (typeof data.data.menucategory !== 'undefined') {
      context.commit('activateMenu', data.data.menucategory)
    }
  }
}

const getters = {
}

export default new Vuex.Store({
  state,
  getters,
  actions,
  mutations
})
