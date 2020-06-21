// functionExpression();

// let functionExpression = function () {
//     window.console.log("function expression called")
// };
//
// functionExpression();
//
// functionDeclaration("before declaration");
//
// function functionDeclaration(message) {
//     window.console.log("function declaration called " + message);
// }
//
// functionDeclaration("after declaration");

const TO_DO_TASKS = [];
const DONE_TASKS = [];

const setElementValueByProperty = (property, id, message) => { getElementById(id)[property] = message; };
const getElementById = (id) => { return document.getElementById(id); };

const isValidEntry = (task) => {
    /* if it doesn't match only spaces, it will be null and should be added as a task*/
    return task.match(/^\s*$/) === null
};

const addTask = () => {
    const task = getElementById("new-task").value;

    if (isValidEntry(task)) {
        const allTasks = getElementById("all-tasks").innerHTML;

        /* add task to document */
        setElementValueByProperty("innerHTML", "all-tasks", allTasks.concat("<div class='task-wrapper'><div><input class=\"status-checkbox\" type=\"checkbox\" onchange='setOpacity(this)'/></div><div>" + task + "</div></div>"));

        /* reset textarea */
        setElementValueByProperty("value", "new-task", "");

        TO_DO_TASKS.push(task);

        /* update total tasks to do in document */
        setElementValueByProperty("innerHTML", "num-items-to-do", TO_DO_TASKS.length);
    }

    getElementById("new-task").focus();
};

const deleteTask = (task, taskWrapper) => {
    DONE_TASKS.unshift(task);
    TO_DO_TASKS.splice(TO_DO_TASKS.indexOf(task), 1); /* remove from TO_DO_TASKS */

    taskWrapper.remove(); /* remove the task */
};

const uncheck = (checkBoxContainer) => {
    checkBoxContainer.firstChild.checked = false;
};

const deleteDoneTasks = () => {
    const allTasks = getElementById("all-tasks").children;

    for (let i = allTasks.length - 1; i > 0; --i) {
        const taskWrapper = allTasks.item(i);
        const checkBoxContainer = taskWrapper.firstElementChild;
        const taskContainer = taskWrapper.lastElementChild;

        if (checkBoxContainer.firstChild.checked) {
            const task = taskContainer.firstChild.textContent;
            const wasConfirmed = window.confirm("Do you really want to delete task: " + task + "?");

            if (wasConfirmed) {
                deleteTask(task, taskWrapper);
            } else {
                uncheck(checkBoxContainer);
                setOpacity(checkBoxContainer.firstChild);
            }
        }
    }

    setElementValueByProperty("innerHTML", "num-items-to-do", TO_DO_TASKS.length);
    getElementById("new-task").focus();
};

const selectAllTasks = () => {
    const allTasks = getElementById("all-tasks").children;

    for (let i = allTasks.length - 1; i > 0; --i) {
        const taskWrapper = allTasks.item(i);
        const checkbox = taskWrapper.firstElementChild.firstChild;

        checkbox.checked = true;
        setOpacity(checkbox);
    }
};

//TODO: still not correct
const setOpacity = (element) => {
    if (element.checked) {
        element.setAttribute("checked", true);
        element.parentElement.nextElementSibling.style.opacity = ".2";
    }
    else {
        element.removeAttribute("checked");
        element.parentElement.nextElementSibling.style.opacity = "revert";
    }
};

const createDoneView = () => {
    let allTasks = getElementById("all-tasks");

    allTasks.innerHTML = "<div class=\"task-wrapper\">\n" +
        "                <div>\n" +
        "                    Status\n" +
        "                </div>\n" +
        "                <div>\n" +
        "                    Task\n" +
        "                </div>\n" +
        "            </div>";
    for (let i = 0; i < DONE_TASKS.length; ++i) {
        console.log(DONE_TASKS[i]);
        allTasks.append("<div class=\"task-wrapper\"></div><div></div><div>" + DONE_TASKS[i] + "</div></div>")
    }
};

const setEventListener = (id, type, eventHandler) => {
    getElementById(id).addEventListener(type, eventHandler);
};

setEventListener("add-new-task-button", "click", addTask);
setEventListener("clear-done-tasks-button", "click", deleteDoneTasks);
setEventListener("select-all-tasks-button", "click", selectAllTasks);