<template>
    <div class="displaymenu">
        <div class="grid-container">
            <div class="header">
                {{ title }}
            </div>

            <div class="menu">
                <table>
                    <tr v-for="item in items" :class="{ 'current': item.current, 'nselectable': !item.selectable }" :key="item.idx">
                        <td v-for="(sp,chidx) in splitItem(item.text)" :style="tabch(chidx)" :key="sp.xxx">
                            {{ sp }}
                        </td>
                    </tr>
                </table>
            </div>

            <div class="message" :style="messagestyle(message)">
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

            <div class="scrollbar" v-if="calcsb.height > 0">
                <svg viewBox="0 0 20 600" class="sbsvg" preserveAspectRatio="none">
                    <rect id="eins" x="0" y="0"   width="20" height="600" fill="#1a53ff" />
                    <rect id="zwei" x="0" :y="calcsb.y" width="20" :height="calcsb.height" fill="#ffff99" />
                </svg>
            </div>
        </div>
    </div>
</template>

<script>

/*
   payload.title    title
   payload.buttons  buttons
   payload.message  message
   payload.items    items
   payload.tabs     tabs
*/

export default {
  name: 'displaymenu',

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
        return { width: 'auto' }
      }

      if (x === 0) {
        return { width: 'auto' }
      } else {
        return { width: x + 'ch' }
      }
    },

    messagestyle (message) {
      if (message === null) {
        return
      }

      switch (message.type) {
        case 0:
          return { backgroundColor: 'LightYellow' }
        case 1:
          return { backgroundColor: 'OldLace' }
        case 2:
          return { backgroundColor: 'orangered' }
        case 3:
          return { backgroundColor: 'red' }
      }
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

    scrollbar () {
      return this.$myStore.state.payload.scrollbar
    },

    calcsb () {
      if (typeof this.scrollbar === 'undefined' || this.scrollbar === null) {
        return { height: 0, y: 0 }
      }

      if (this.scrollbar.total > 0 && this.scrollbar.total > this.scrollbar.max) {
        var ch = 600 * this.scrollbar.max / this.scrollbar.total
        var cy = 600 * this.scrollbar.offset / this.scrollbar.total

        return { height: ch, y: cy }
      } else {
        return { height: 0, y: 0 }
      }
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaymenu {
    background-color: yellow;
    background-color:rgba(0, 0, 0, 0.9);
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
    background-color: yellow;
    text-align: left;
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

.sbsvg {
    height: 95%;
    width:20px;
    padding-top:10px;
}

.message {
    grid-area: message;
}

.red {
    grid-area: red;
    background-color: red;
}

.green {
    grid-area: green;
    background-color: green;
}

.yellow {
    grid-area: yellow;
    background-color: yellow;
}

.blue {
    grid-area: blue;
    background-color: blue;
}

.current {
    background-color: gainsboro;
}

.nselectable {
    font-style: italic;

}
</style>
