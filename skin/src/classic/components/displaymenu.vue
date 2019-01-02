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

            <!-- Begin: Menuitems or text -->
            <!-- IF -->
            <div class="menu" v-if="hasText" >
                <span v-for="line in splitMenuText" class="menutext" :key="line.xxx">
                    {{ line }} <br/>
                </span>
            </div>

            <!-- ELSE -->
            <div class="menu" v-else>
                <table>
                    <tr v-for="item in items" :class="{ 'nselectable': !item.selectable, 'selectable': item.selectable, 'current': item.current }" :key="item.idx">
                        <td v-for="(sp,chidx) in splitItem(item.text)" :style="tabch(chidx)" :key="sp.xxx">
                            {{ sp }}
                        </td>
                    </tr>
                </table>
            </div>
            <!-- End: Menuitems or text -->

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
        return { width: 'auto', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }
      }

      if (x === 0) {
        return { width: 'auto', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }
      } else {
        return { width: x + 'ch', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }
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
    },

    menutext () {
      return this.$myStore.state.payload.menutext
    },

    hasText () {
      var t = this.$myStore.state.payload.menutext
      return (typeof t !== 'undefined') && (typeof t.text !== 'undefined')
    },

    splitMenuText () {
      if (typeof this.$myStore.state.payload.menutext !== 'undefined') {
        return this.$myStore.state.payload.menutext.text.split('\n')
      } else {
        return ''
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
    overflow: hidden;
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

.menutext {
    color: @clrMenuItemNonSelectable;
    text-overflow: ellipsis;
    overflow:hidden;
}

.selectable {
    color: @clrMenuItemSelectable;
}
</style>
