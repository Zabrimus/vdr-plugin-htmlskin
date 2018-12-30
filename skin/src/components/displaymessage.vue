<template>
    <div class="displaymessage">
        <div class="grid-container">
            <div class="message">
                {{ message.text }}
                {{ message.type }}
            </div>
        </div>
    </div>
</template>
<script>
export default {
  name: 'displaymessage',

  created () {
  },

  methods: {
  },

  computed: {
    message () {
      return this.$myStore.state.payload.message
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displaymessage {
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
  grid-template-columns: 1fr;
  grid-template-rows: 2em;
  grid-template-areas: ".";
}

.message {
    text-align: center;
    font-weight: bold;
}

</style>
