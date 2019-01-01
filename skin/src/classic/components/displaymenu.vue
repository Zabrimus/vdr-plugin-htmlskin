<template>
    <div class="displaymenu">
        <div class="grid-container">
            <div class="message" :class="messagestyle(message)">
                {{ message.message }}
            </div>

            <div class="buttons">
                <buttons></buttons>
            </div>

            <div class="scrollbar">
                <scrollbar></scrollbar>
            </div>

            <div class="menu">
                <table>
                    <tr v-for="item in items" :class="{ 'nselectable': !item.selectable, 'selectable': item.selectable, 'current': item.current }" :key="item.idx">
                        <td v-for="(sp,chidx) in splitItem(item.text)" :style="tabch(chidx)" :key="sp.xxx">
                            {{ sp }}
                        </td>
                    </tr>
                </table>
            </div>

            <div class="header">
                {{ title }}
                <span class="currentTime">{{ currentTime }}</span>
            </div>
        </div>
    </div>
</template>

<script>
import scrollbar from './subcomponents/scrollbar'
import buttons from './subcomponents/buttons'

export default {
  name: 'displaymenu',

  components: {
    scrollbar, buttons
  },

  created () {
  },

  methods: {
    splitItem (item) {
      if (typeof item !== 'undefined') {
        return item.split('\t')
      } else {
        return ''
      }
    },

    tabch (idx) {
      var x = this.tabs[idx]

      if (idx === 0 && this.tabs[idx + 1] === 0) {
        return { width: 'auto', whiteSpace: 'nowrap', overflow: 'hidden' }
      }

      if (x === 0) {
        return { width: 'auto', whiteSpace: 'nowrap', overflow: 'hidden' }
      } else {
        return { width: x + 'ch', whiteSpace: 'nowrap', overflow: 'hidden' }
      }
    },

    messagestyle (message) {
      if (message === null) {
        return
      }

      return 'message_' + message.type
    }
  },

  computed: {
    title () {
      return this.$myStore.state.payload.title
    },

    buttons () {
      return this.$myStore.state.payload.buttons
    },

    items () {
      return this.$myStore.state.payload.items
    },

    tabs () {
      return this.$myStore.state.payload.tabs
    },

    message () {
      return this.$myStore.state.payload.message
    },

    currentTime: {
      cache: false,
      get () {
        var d = new Date()
        return d.getDate() + '.' + (d.getMonth() + 1) + '.' + d.getFullYear() + '  ' + ('0' + d.getHours()).slice(-2) + ':' + ('0' + d.getMinutes()).slice(-2)
      }
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaymenu {
    background-color: @clrBackground;
    position: absolute;
    width: 90%;
    height: 90%;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
}

.grid-container * {
    border: 0;
    position: relative;
}

.grid-container {
    display: grid;
    height: 100%;
    grid-template-columns: 1fr auto;
    grid-template-rows: auto 1fr auto auto;
    grid-template-areas: "header header" "menu scrollbar" "message message" "buttons buttons";
}

.message {
    grid-area: message;
}

.buttons {
    grid-area: buttons;
}

.scrollbar {
    grid-area: scrollbar;
    width: 10px;
    height: 100%;
}

.menu {
    grid-area: menu;
    text-align: left;
    height: 100%;
}

.header {
    grid-area: header;
    text-align: left;
    color: @clrMenuTitleFg;
    background-color: @clrMenuTitleBg;
}

.currentTime {
    text-align: right;
    margin-left: 85%;
}

.current {
    color: @clrBlack !important;
    background-color: @clrCyan;
}

.nselectable {
    color: @clrMenuItemNonSelectable;
}

.selectable {
    color: @clrMenuItemSelectable;
}

.message_0 {
    color: @clrMessageStatusFg;
    background-color: @clrMessageStatusBg;
}

.message_1 {
    color: @clrMessageInfoFg;
    background-color: @clrMessageInfoBg;
}

.message_2 {
    color: @clrMessageWarningFg;
    background-color: @clrMessageWarningBg;
}

.message_3 {
    color: @clrMessageErrorFg;
    background-color: @clrMessageErrorBg;
}
</style>
