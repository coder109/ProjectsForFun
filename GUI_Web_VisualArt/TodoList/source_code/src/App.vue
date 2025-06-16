<script setup>
import { ref } from 'vue';
import TodoElement from './components/TodoElement.vue';
import AddTodo from './components/AddTodo.vue';

const todoID = ref(0);
const todoList = ref([
	{ id: todoID.value++, text: 'Learn Vue', done: false },
	{ id: todoID.value++, text: 'Learn React', done: false },
]);

function addTodo(newTodo) {
	// Avoid adding empty todos
	if (!newTodo) return;
	// Avoid adding duplicate todos
	if (todoList.value.some((todo) => todo.text === newTodo)) return;
	todoList.value.push({ id: todoID.value++, text: newTodo, done: false });
}

function deleteTodo(id) {
	todoList.value = todoList.value.filter((todo) => todo.id !== id);
}
</script>

<template>
	<div class="container">
		<AddTodo @addTodo="addTodo" />
		<div class="score">
			<p v-if="todoList.length === 0">No todos</p>
			<p v-else-if="todoList.length === 1">1 todo</p>
			<p v-else>{{ todoList.length }} todos</p>
		</div>
		<TodoElement v-for="todo in todoList" :key="todo.id" :todo="todo" @deleteTodo="(id)=>deleteTodo(id)"/>
	</div>
</template>

<style scoped>
.container {
	display: flex;
	flex-direction: column;
}

</style>