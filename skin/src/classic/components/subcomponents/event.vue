<template>
    <div class="displaymenuevent">
        <div class="event-container">
            <div class="event-time">
                {{ event.startDateStr }} {{ event.startTimeStr }} - {{ event.endTimeStr }}
            </div>

            <div class="event-title">
                {{ event.title }}
            </div>

            <div class="event-short">
                {{ event.shortText }}
            </div>

            <div class="event-description">
                <span v-for="sp in splitDescription(event.description)" :key="sp.xxx">
                    {{ sp }} <br/>
                </span>
            </div>
        </div>
    </div>
</template>

<script>
export default {
  name: 'displaymenuevent',

  methods: {
    splitDescription (description) {
      if (typeof description !== 'undefined') {
        return description.split('\n')
      } else {
        return ''
      }
    }
  },

  computed: {
    event () {
      return this.$myStore.state.payload.event.event
    }
  }
}
</script>

<style scoped lang="less">
    @import '../../assets/globalstyle.less';

    .displaymenuevent {
    }

    .event-container {
        display: grid;
        grid-template-columns: 1fr;
        grid-template-rows: 1fr 1fr 1fr 1fr;
        grid-template-areas: "event-time" "event-title" "event-short" "event-description";
    }

    .event-time {
        grid-area: event-time;
        text-align: left;
        padding-bottom: 20px;
        padding-top: 20px;
        color: @clrMenuEventTime;
    }

    .event-title {
        grid-area: event-title;
        text-align: left;
        font-weight: bold;
        font-size: 120%;
        color: @clrMenuEventTitle;
    }

    .event-short {
        grid-area: event-short;
        text-align: left;
        font-weight: 700;
        font-style: italic;
        padding-bottom: 20px;
        color: @clrMenuEventShortText;
    }

    .event-description {
        grid-area: event-description;
        text-align: left;
        color: @clrMenuEventDescription;
    }
</style>
