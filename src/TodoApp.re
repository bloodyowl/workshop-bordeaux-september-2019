type status =
  | Done(string)
  | NotDone;

type todo = {
  id: string,
  title: string,
  status,
};

type state = {
  todos: array(todo),
  todoInput: string,
};

module Styles = {
  open Css;
  let input =
    style([
      backgroundColor("eee"->hex),
      borderRadius(10->px),
      width(100.0->pct),
      padding(10->px),
      fontSize(18->px),
      borderStyle(none),
      boxSizing(borderBox),
    ]);
};

type action =
  | AddTodo
  | ChangeTodoStatus(string, status)
  | DeleteTodo(string)
  | UpdateTodoInput(string);

[@react.component]
let make = () => {
  let (state, send) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | AddTodo => {
            todos:
              state.todos
              ->Belt.Array.concat([|
                  {
                    id: Js.Math.random()->Js.String.make,
                    title: state.todoInput,
                    status: NotDone,
                  },
                |]),
            todoInput: "",
          }
        | UpdateTodoInput(todoInput) => {...state, todoInput}
        | ChangeTodoStatus(todoId, status) => {
            ...state,
            todos:
              state.todos
              ->Belt.Array.map(todo =>
                  if (todo.id == todoId) {
                    {...todo, status};
                  } else {
                    todo;
                  }
                ),
          }
        | DeleteTodo(todoId) => {
            ...state,
            todos: state.todos->Belt.Array.keep(({id}) => id != todoId),
          }
        },
      {todos: [||], todoInput: ""},
    );
  <div>
    {state.todos
     ->Belt.Array.map(todo =>
         <div key={todo.id}>
           todo.title->React.string
           <input
             type_="checkbox"
             checked={
               switch (todo.status) {
               | Done(_) => true
               | NotDone => false
               }
             }
             onChange={_ =>
               send(
                 ChangeTodoStatus(
                   todo.id,
                   switch (todo.status) {
                   | Done(_) => NotDone
                   | NotDone => Done(Js.Date.make()->Js.Date.toISOString)
                   },
                 ),
               )
             }
           />
           {switch (todo.status) {
            | Done(date) => {j|Completed on $date|j}->React.string
            | NotDone => React.null
            }}
           <button onClick={_ => send(DeleteTodo(todo.id))}>
             "Delete"->React.string
           </button>
         </div>
       )
     ->React.array}
    <input
      value={state.todoInput}
      onChange={event =>
        send(UpdateTodoInput(event->ReactEvent.Form.target##value))
      }
      placeholder="Type something"
      className=Styles.input
    />
    <button onClick={_ => send(AddTodo)}> "Add"->React.string </button>
  </div>;
};
