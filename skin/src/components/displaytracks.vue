<template>
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
</template>

/*
{
    "action": "showPage",
    "page": "displaytracks",
    "data": {
        "title": "Audio",
        "numTracks": 2,
        "tracks": [
            "stereo",
            "mit Audiodeskription"
        ],
        "track": {
            "value": "stereo",
            "index": 0
        },
        "audio": {
            "channel": 0
        }
    }
}
*/

<script>
export default {
  name: 'displaytracks',

  created () {
  },

  methods: {
    selected (v) {
      if (v === this.track.value) {
        return 'selected'
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
    position: absolute;
    width: 90%;
    height: 100%;
    left: 50%;
    transform: translate(-50%, 0);
}

.grid-container {
    display: grid;
    grid-template-columns: 1fr;
    grid-template-rows: 1fr auto;
    grid-template-areas: "filler" "tracks";
    height: 100%;
}

.filler {
    grid-area: filler;
}

.tracks {
    grid-area: tracks;
    background-color: yellow;
    background-color:rgba(0, 0, 0, 0.9);
}

.tracks ul {
    list-style-type: none;
}

.title {
    background-color: yellow;
}

.selected {
    background-color: gainsboro;
}
</style>
