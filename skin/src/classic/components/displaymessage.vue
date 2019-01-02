<template>
    <div class="displaymessage">
        <div class="grid-container">
            <message></message>
        </div>
    </div>
</template>
<script>
import message from './subcomponents/message'

export default {
  name: 'displaymessage',

  components: {
    message
  },

  created () {
  },

  methods: {
  },

  computed: {
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaymessage {
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
  grid-template-rows: 2em;
  grid-template-areas: ".";
}

.message {
    text-align: center;
    font-weight: bold;
}

</style>
