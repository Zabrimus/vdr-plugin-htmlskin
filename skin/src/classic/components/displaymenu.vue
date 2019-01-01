<template>
    <div class="displaymenu">
        <div class="grid-container">
            <div class="header">
                {{ title }}
                <span class="currentTime">{{ currentTime }}</span>
            </div>

            <div class="menu">
                <table>
                    <tr v-for="item in items" :class="{ 'current': item.current, 'nselectable': !item.selectable, 'selectable': item.selectable }" :key="item.idx">
                        <td v-for="(sp,chidx) in splitItem(item.text)" :style="tabch(chidx)" :key="sp.xxx">
                            {{ sp }}
                        </td>
                    </tr>
                </table>
            </div>

            <div class="message"  :class="messagestyle(message)">
                {{ message.message }}
            </div>

            <div class="red">
                {{ buttons.red }}
            </div>

            <div class="green">
                {{ buttons.green }}
            </div>

            <div class="yellow">
                {{ buttons.yellow }}
            </div>

            <div class="blue">
                {{ buttons.blue }}
            </div>

            <scrollbar class="scrollbar"></scrollbar>
        </div>
    </div>
</template>

<script>
import scrollbar from './subcomponents/scrollbar'

export default {
  name: 'displaymenu',

  components: {
    scrollbar
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

.grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr 1fr auto;
    grid-template-rows: auto 1fr auto auto;
    grid-template-areas: "header header header header header" "menu menu menu menu scrollbar" "message message message message scrollbar" "red green yellow blue blue";
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

.menu {
    grid-area: menu;
    text-align: left;
}

.scrollbar {
    grid-area: scrollbar;
    width: 20px;
    height: 100%;
}

.message {
    grid-area: message;
}

.red {
    grid-area: red;
    color: @clrButtonRedFg;
    background-color: @clrButtonRedBg;
}

.green {
    grid-area: green;
    color: @clrButtonGreenFg;
    background-color: @clrButtonGreenBg;
}

.yellow {
    grid-area: yellow;
    color: @clrButtonYellowFg;
    background-color: @clrButtonYellowBg;
}

.blue {
    grid-area: blue;
    color: @clrButtonBlueFg;
    background-color: @clrButtonBlueBg;
}

.current {
    color: @clrBlack;
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
