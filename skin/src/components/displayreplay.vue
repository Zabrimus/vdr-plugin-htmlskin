<template>
    <div class="displayreplay">
        <div class="grid-container">
            <div class="header">
                {{ title }}
            </div>

            <div class="progress">
                <svg viewBox="0 0 600 20" class="sbsvg" preserveAspectRatio="none">
                    <rect id="eins" x="0" y="0" width="600" height="20" fill="#1a53ff" />
                    <rect id="zwei" x="0" y="0" :width="calcsb.width" height="20" fill="#ffff99" />
                </svg>
            </div>

            <div class="start">
                {{ current }}
            </div>

            <div class="jump">
                {{ jump }}
            </div>

            <div class="end">
                {{ total }}
            </div>

            <div class="message">
                {{ message }}
            </div>
        </div>
    </div>
</template>

<script>
export default {
  name: 'displayreplay',

  created () {
  },

  methods: {
  },

  computed: {
    title () {
      return this.$myStore.state.payload.title
    },

    total () {
      return this.$myStore.state.payload.total
    },

    progress () {
      return this.$myStore.state.payload.progress
    },

    current () {
      return this.$myStore.state.payload.current
    },

    mode () {
      return this.$myStore.state.payload.mode
    },

    message () {
      return this.$myStore.state.payload.message
    },

    jump () {
      return this.$myStore.state.payload.jump
    },

    calcsb () {
      if (typeof this.progress === 'undefined' || this.progress === null) {
        return { width: 0 }
      }

      if (this.progress.current > 0) {
        var cx = 600 * this.progress.current / this.progress.total

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

.displayreplay {
    background-color: yellow;
    background-color:rgba(0, 0, 0, 0.9);
    position: absolute;
    bottom: 2em;
    width: 90%;
    left: 50%;
    transform: translate(-50%, 0);
}

.grid-container {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-rows: auto auto auto auto;
    grid-template-areas: "message message message" "header header header" "progress progress progress" "start jump end";
}

.header {
    grid-area: header;
    text-align: left;
}

.progress {
    grid-area: progress;
}

.start {
    grid-area: start;
    text-align: left;
}

.jump {
    grid-area: jump;
}

.end {
    grid-area: end;
    text-align: right;
}

.message {
    grid-area: message;
}

</style>
