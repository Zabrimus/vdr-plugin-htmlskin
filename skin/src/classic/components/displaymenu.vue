<template>
    <div class="displaymenu">
        <div class="grid-container">
            <div class="message">
                <message></message>
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
                <titlec></titlec>
            </div>
        </div>
    </div>
</template>

<script>
import scrollbar from './subcomponents/scrollbar'
import buttons from './subcomponents/buttons'
import titlec from './subcomponents/title'
import message from './subcomponents/message'

export default {
  name: 'displaymenu',

  components: {
    scrollbar, buttons, titlec, message
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
    }
  },

  computed: {
    buttons () {
      return this.$myStore.state.payload.buttons
    },

    items () {
      return this.$myStore.state.payload.items
    },

    tabs () {
      return this.$myStore.state.payload.tabs
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
</style>
