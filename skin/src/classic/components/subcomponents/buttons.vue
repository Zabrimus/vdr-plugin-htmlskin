<template>
    <div>
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
    </div>
</template>

<script>
export default {
  name: 'buttons',

  computed: {
    buttons () {
      return this.$myStore.state.payload.buttons
    }
  }
}
</script>

<style scoped lang="less">
    @import '../../assets/globalstyle.less';

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
</style>
