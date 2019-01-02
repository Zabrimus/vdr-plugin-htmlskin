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

            <div class="event">
                <event></event>
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
import event from './subcomponents/event'

export default {
  name: 'displaymenuevent',

  components: {
    scrollbar, buttons, titlec, message, event
  },

  created () {
  },

  methods: {
  },

  computed: {
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
        grid-template-areas: "header header" "event scrollbar" "message message" "buttons buttons";
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

    .event {
        grid-area: event;
        height: 100%;
    }

    .header {
        grid-area: header;
    }
</style>
