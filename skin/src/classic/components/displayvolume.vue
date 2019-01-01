<template>
    <div class="displayvolume">
        <div class="grid-container">
            <div class="volume" v-if="! vol.mute">
                <svg viewBox="0 0 600 20" class="sbsvg" preserveAspectRatio="none">
                    <rect id="eins" x="0" y="0" width="600" height="20" fill="#1a53ff" />
                    <rect id="zwei" x="0" y="0" :width="calcsb.width" height="20" fill="#ffff99" />
                </svg>
            </div>

            <div class="volume" v-if="vol.mute">
                Stumm
            </div>
        </div>
    </div>
</template>

<script>
export default {
  name: 'displayvolume',

  created () {
  },

  methods: {
  },

  computed: {
    vol () {
      return this.$myStore.state.payload.volume
    },

    calcsb () {
      if (typeof this.vol === 'undefined' || this.vol === null) {
        return { width: 0 }
      }

      if (this.vol.current > 0) {
        var cx = 600 * this.vol.current / this.vol.total

        return { width: cx }
      } else {
        return { width: 0 }
      }
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displayvolume {
    background-color: @clrBackground;
    position: absolute;
    bottom: 2em;
    width: 90%;
    left: 50%;
    transform: translate(-50%, 0);
}

.grid-container {
    display: grid;
    grid-template-columns: 1fr;
    grid-template-rows: auto;
    grid-template-areas: "volume";
}

.volume {
    grid-area: volume;
}

</style>
