<template>
    <div class="message-container">
        <div class="message-value" :class="messagestyle(message)">
            {{ message.message }}
        </div>
    </div>
</template>

<script>
export default {
  name: 'message',

  methods: {
    messagestyle (message) {
      if (message === null || message.message === null) {
        return
      }

      return 'message_' + message.type
    }
  },

  computed: {
    message () {
      return this.$myStore.state.payload.message
    }
  }
}
</script>

<style scoped lang="less">
    @import '../../assets/globalstyle.less';

    .message-container {
        display: grid;
        grid-template-columns: 1fr;
        grid-template-rows: auto;
        grid-template-areas: "message-value";
    }

    .message-value{
        grid-area: message-value;
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
