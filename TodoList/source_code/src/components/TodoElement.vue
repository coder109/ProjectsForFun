<script setup>
    import { ref } from 'vue';

    const isModify = ref(false);
    const props = defineProps({
        todo: { type: Object, required: true },
    })

    const emit = defineEmits(['deleteTodo']);

    function deleteTodo() {
        emit('deleteTodo', props.todo.id);
    }
</script>

<template>
    <div class="todo_element">
        <div class="todo_name">
            <p v-if="!isModify">{{ todo.text }}</p>
            <input type="text" v-else v-model="todo.text" @keydown.enter="isModify = false">
        </div>
        <button @click="isModify = true">Modify</button>
        <button @click="deleteTodo">Done</button>
    </div>
</template>

<style scoped>
    .todo_element {
        border: 2px solid gray;
        margin-top: 10px;
        display: flex;
    }
    .todo_name {
        width: 100%;
    }
</style>