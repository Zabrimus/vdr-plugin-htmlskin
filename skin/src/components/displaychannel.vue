<template>
    <div class="displaychannel">
        <div class="grid-container">
            <div class="present_time">
                {{ present.startTimeStr }}
            </div>

            <div class="following_time">
                {{ following.startTimeStr }}
            </div>

            <div class="present_title">
                {{ present.title }}
            </div>

            <div class="present_shorttext">
                {{ present.shortText }}
            </div>

            <div class="following_title">
                {{ following.title }}
            </div>

            <div class="following_shorttext">
                {{ following.shortText }}
            </div>

            <div class="channel">
                <span v-if="channel.number > 0"> {{ channel.number}} </span>
                <span class="channel_name">{{ channel.name }}</span>
            </div>

            <div class="channel current_time">
                {{ currentTime }}
            </div>
        </div>
    </div>
</template>

<script>

/*
   payload.channel          channel
   payload.events.present   present event
   payload.events.following following event
*/

export default {
  name: 'displaychannel',

  created () {
  },

  methods: {
  },

  computed: {
    channel () {
      if (typeof this.$myStore.state.payload.channel !== 'undefined') {
        return this.$myStore.state.payload.channel
      } else {
        return JSON.parse('{}')
      }
    },

    present () {
      if (typeof this.$myStore.state.payload.events !== 'undefined' && typeof typeof this.$myStore.state.payload.events.present !== 'undefined') {
        return this.$myStore.state.payload.events.present
      } else {
        return JSON.parse('{}')
      }
    },

    following () {
      if (typeof this.$myStore.state.payload.events !== 'undefined' && typeof typeof this.$myStore.state.payload.events.following !== 'undefined') {
        return this.$myStore.state.payload.events.following
      } else {
        return JSON.parse('{}')
      }
    },

    currentTime: {
      cache: false,
      get () {
        var d = new Date()
        return ('0' + d.getHours()).slice(-2) + ':' + ('0' + d.getMinutes()).slice(-2)
      }
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaychannel {
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
  grid-template-columns: 4em 1fr;
  grid-template-rows: 2em 1.2em 1.2em 1.2em 1.2em;
  grid-template-areas: "channel channel"
                       "present_time present_title"
                       "present_time present_shorttext"
                       "following_time following_title"
                       "following_time following_shorttext";
}

.present_time {
    grid-area: present_time;
    text-align: left;
    background-color:rgba(200, 200, 20, 0.9);
    font-weight: bold;
}

.following_time {
    grid-area: following_time;
    text-align: left;
    background-color:rgba(200, 200, 20, 0.9);
    font-weight: bold;
}

.present_title {
    grid-area: present_title;
    text-align: left;
    font-weight: bold;
}

.present_shorttext {
    grid-area: present_shorttext;
    text-align: left;
    overflow: hidden;
    font-size:small;
}

.following_title {
    grid-area: following_title;
    text-align: left;
    font-weight: bold;
}

.following_shorttext {
    grid-area: following_shorttext;
    text-align: left;
    overflow: hidden;
    font-size:small;
}

.channel {
    grid-area: channel;
    text-align: left;
    font-weight: bold;
}

.current_time {
    text-align: right;
    font-weight: bold;
    width:100%;
}

.channel_name {
    justify-self: end;
    font-weight: bold;
    width:100%;
}

</style>
