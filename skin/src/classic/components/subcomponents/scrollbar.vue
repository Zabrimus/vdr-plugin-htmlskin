<template>
    <div v-if="calcsb.height > 0">
        <svg viewBox="0 0 20 600" class="sbsvg" preserveAspectRatio="none">
            <rect id="eins" x="0" y="0"   width="20" height="600" class="scrollbar_total" />
            <rect id="zwei" x="0" :y="calcsb.y" width="20" :height="calcsb.height" class="scrollbar_sel" />
        </svg>
    </div>
</template>

<script>
export default {
  name: 'scrollbar',

  computed: {
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
    @import '../../assets/globalstyle.less';

    .scrollbar {
        width: 10px;
        height: 100%;
    }

    .sbsvg {
        height: 95%;
        width:10px;
        padding-top:10px;
    }

    .scrollbar_total {
        fill: @clrMenuScrollbarTotal;
    }

    .scrollbar_sel {
        fill: @clrMenuScrollbarShown;
    }

    .sbsvg {
        height: 95%;
        width:10px;
        padding-top:10px;
    }
</style>
