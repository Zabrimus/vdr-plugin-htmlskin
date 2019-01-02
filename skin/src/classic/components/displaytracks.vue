<template>
    <div class="displaytracks">
        <div class="track-container">
            <div class="tracks">
                <ul>
                    <li class="title">{{ title }}</li>

                    <li v-for="tr in tracks" :key="tr.idx" :class="selected(tr)">
                        {{ tr }}
                    </li>
                </ul>
            </div>
        </div>
    </div>

    <!--
    <div class="displaytracks">
        <div class="grid-container">
            <div class="filler">
            </div>

            <div class="tracks">
                <ul>
                    <li class="title">{{ title }}</li>

                    <li v-for="tr in tracks" :key="tr.idx" :class="selected(tr)">
                        {{ tr }}
                    </li>
                </ul>
            </div>
        </div>
    </div>
    -->
</template>

<script>
export default {
  name: 'displaytracks',

  created () {
  },

  methods: {
    selected (v) {
      if (v === this.track.value) {
        return 'selected'
      } else {
        return 'unselected'
      }
    }
  },

  computed: {
    title () {
      return this.$myStore.state.payload.title
    },

    tracks () {
      return this.$myStore.state.payload.tracks
    },

    track () {
      return this.$myStore.state.payload.track
    },

    audio () {
      return this.$myStore.state.payload.audio
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaytracks {
    background-color: @clrBackground;
    position: absolute;
    bottom: 2em;
    left: 20%;
    transform: translate(-20%, 0);
}

.track-container {
    display: grid;
    grid-template-columns: auto;
    grid-template-rows: auto;
    grid-template-areas: "tracks";
}

.tracks {
    grid-area: tracks;
    text-align: center;
}

.tracks ul {
    list-style-type: none;
    margin: auto;
    padding: 0;
}

.title {
    background-color: @clrMenuItemNonSelectable;
}

.selected {
    color: @clrBlack !important;
    background-color: @clrCyan;
}

.unselected {
    color: @clrMenuItemSelectable;
}
</style>
