<script setup>
    import { ref } from 'vue';
    
    const newTodo = ref('');
    const emit = defineEmits(['addTodo']);
    function addTodo() {
        emit('addTodo', newTodo.value);
        newTodo.value = '';
    }
</script>

<template>
<div class="add_todo">
    <input v-model="newTodo" @keydown.enter="addTodo">
    <button @click="addTodo">Add</button>
</div>
</template>

<style scoped>
    .add_todo {
        display: flex;
    }
    input {
        width: 100%;
    }
</style>