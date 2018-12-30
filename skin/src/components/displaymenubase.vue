<template>
  <div id="menubase">
      <component v-bind:is="currentmenu"></component>
  </div>
</template>

<script>
import displaymenu from './displaymenu'
import displaymenuevent from './displaymenuevent'

export default {
  name: 'displaymenubase',

  data: function () {
    return {
      menus: [
        { name: 'menuUndefined', component: 'displaymenu' },
        { name: 'menuUnknown', component: 'displaymenu' },
        { name: 'menuMain', component: 'displaymenu' },
        { name: 'menuSchedule', component: 'displaymenu' },
        { name: 'menuScheduleNow', component: 'displaymenu' },
        { name: 'menuScheduleNext', component: 'displaymenu' },
        { name: 'menuChannel', component: 'displaymenu' },
        { name: 'menuChannelEdit', component: 'displaymenu' },
        { name: 'menuTimer', component: 'displaymenu' },
        { name: 'menuTimerEdit', component: 'displaymenu' },
        { name: 'menuRecording', component: 'displaymenu' },
        { name: 'menuRecordingInfo', component: 'displaymenu' },
        { name: 'menuRecordingEdit', component: 'displaymenu' },
        { name: 'menuPlugin', component: 'displaymenu' },
        { name: 'menuPluginSetup', component: 'displaymenu' },
        { name: 'menuSetup', component: 'displaymenu' },
        { name: 'menuSetupOsd', component: 'displaymenu' },
        { name: 'menuSetupEpg', component: 'displaymenu' },
        { name: 'menuSetupDvb', component: 'displaymenu' },
        { name: 'menuSetupLnb', component: 'displaymenu' },
        { name: 'menuSetupCam', component: 'displaymenu' },
        { name: 'menuSetupRecord', component: 'displaymenu' },
        { name: 'menuSetupReplay', component: 'displaymenu' },
        { name: 'menuSetupMisc', component: 'displaymenu' },
        { name: 'menuSetupPlugins', component: 'displaymenu' },
        { name: 'menuCommand', component: 'displaymenu' },
        { name: 'menuEvent', component: 'displaymenuevent' },
        { name: 'menuText', component: 'displaymenu' },
        { name: 'menuFolder', component: 'displaymenu' },
        { name: 'menuCam', component: 'displaymenu' }
      ]
    }
  },

  components: {
    /* eslint-disable vue/no-unused-components */
    displaymenu, displaymenuevent
  },

  computed: {
    currentmenu: function () {
      if (this.$myStore.state.currentMenu !== null) {
        if (this.$myStore.state.currentMenu <= this.menus.length) {
          return this.menus[this.$myStore.state.currentMenu + 1].component
        } else {
          return 'displaymenu'
        }
      } else {
        return 'displaymenu'
      }
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

#menubase {
   height: 100%;
   width: 100%;
}
</style>
