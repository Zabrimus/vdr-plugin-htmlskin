<template>
    <div class="title-container">
        <div class="title-right">
            {{ currentTime }}
        </div>

        <div class="title-left">
            {{ title }}
        </div>
    </div>
</template>

<script>
export default {
  name: 'titlec',

  computed: {
    title () {
      return this.$myStore.state.payload.title
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
    @import '../../assets/globalstyle.less';

    .title-container {
        display: grid;
        grid-template-columns: 1fr auto;
        grid-template-rows: auto;
        grid-template-areas: "title-left title-right";
        border: 0;
        position: relative;
        color: @clrMenuTitleFg;
        background-color: @clrMenuTitleBg;
    }

    .title-right {
        grid-area: title-right;
        text-align: right;
    }

    .title-left {
        grid-area: title-left;
        text-align: left;
    }

    .currentTime {
        text-align: right;
        margin-left: 85%;
    }
</style>
