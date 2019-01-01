<template>
  <div id="app">
      <component v-bind:is="currentview"></component>
  </div>
</template>

<script>
import displaychannel from './components/displaychannel'
import displaymessage from './components/displaymessage'
import displaymenubase from './components/displaymenubase'
import displaymenuevent from './components/displaymenuevent'
import displayreplay from './components/displayreplay'
import displaytracks from './components/displaytracks'
import displayvolume from './components/displayvolume'

export default {
  name: 'app',

  components: {
    /* eslint-disable vue/no-unused-components */
    displaychannel, displaymessage, displaymenubase, displaymenuevent, displayreplay, displaytracks, displayvolume
  },

  mounted () {
    window.addEventListener('keypress', e => {
      console.log(String.fromCharCode(e.key))
    })
  },

  computed: {
    currentview: function () {
      return this.$myStore.state.currentPage
    }
  }
}
</script>

<style lang="less">
html, body {
    width: 100%;
    height: 100%;
    margin: 0;
    padding: 0;
    background-color: rgba(0,0,0,0);
}

#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  height: 100%;
}
</style>
