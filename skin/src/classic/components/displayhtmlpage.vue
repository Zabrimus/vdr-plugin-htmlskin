<template>
    <div class="displayhtmlpage">
        <div class="grid-container">
            <iframe :src="url" sandbox="allow-scripts allow-same-origin" width="100%" height="100%"></iframe>
        </div>
    </div>
</template>

<script>
export default {
  name: 'displayhtmlpage',

  components: {
  },

  created () {
  },

  methods: {
  },

  computed: {
    url () {
      return this.$myStore.state.payload.title.substring(4)
    }
  }
}
</script>

<style scoped lang="less">
@import '../assets/globalstyle.less';

.displayhtmlpage {
    background-color: @clrBackground;
    position: absolute;
    width: 90%;
    height: 90%;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
}

.grid-container {
    display: grid;
    grid-template-columns: 1fr;
    grid-template-rows: 1fr;
    grid-template-areas: ".";
    height: 100%;
    width: 100%;
}
</style>
