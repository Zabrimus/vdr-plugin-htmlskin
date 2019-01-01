<template>
    <div class="displaymenuevent">
        <div class="grid-container">
            <div class="header">
                {{ title }}
            </div>

            <div class="time">
                {{ event.startDateStr }} {{ event.startTimeStr }} - {{ event.endTimeStr }}
            </div>

            <div class="shorttext">
                {{ event.shortText }}
            </div>

            <div class="description">
                <span v-for="sp in splitDescription(event.description)" :key="sp.xxx">
                    {{ sp }} <br/>
                </span>
            </div>

            <div class="message" :style="messagestyle(message)">
                {{ message.message }}
            </div>

            <div class="title">
                {{ event.title }}
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
  name: 'displaymenuevent',

  components: {
    scrollbar
  },

  created () {
  },

  methods: {
    splitDescription (description) {
      if (typeof description !== 'undefined') {
        return description.split('\n')
      } else {
        return ''
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

    message () {
      return this.$myStore.state.payload.message
    },

    event () {
      return this.$myStore.state.payload.event.event
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaymenuevent {
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
    grid-template-rows: auto auto auto auto 1fr auto auto;
    grid-template-areas: "header header header header header" "time time time time scrollbar" "title title title title scrollbar" "shorttext shorttext shorttext shorttext scrollbar" "description description description description scrollbar" "message message message message scrollbar" "red green yellow blue blue";
    height: 100%;
}

.header {
    grid-area: header;
    background-color: yellow;
    text-align: left;
}

.scrollbar {
    grid-area: scrollbar;
    width: 20px;
    height: 100%;
}

.time {
    grid-area: time;
    text-align: left;
    padding-bottom: 20px;
    padding-top: 20px;
}

.shorttext {
    grid-area: shorttext;
    text-align: left;
    font-weight: 700;
    font-style: italic;
    padding-bottom: 20px;
}

.description {
    grid-area: description;
    text-align: left;
}

.title {
    grid-area: title;
    text-align: left;
    font-weight: bold;
    font-size: 120%;
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
</style>
