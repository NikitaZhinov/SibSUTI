let num = 42;
let str = "Привет";
let bool = true;
let empty = null;
let notDefined = undefined;
let obj = {};

const NUM = 42;
const STR = "Привет";
const BOOL = true;
const EMPTY = null;
const NOT_DEFINED = undefined;
const OBJ = {};

// function checkAvailability() {
//     const output = document.getElementById('output');
//     output.innerHTML += `<p>Переменная localNum, определенная в mainFunction - ${typeof localNum !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Константа localStr, определенная в mainFunction - ${typeof localStr !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Переменная num, определенная в документе - ${typeof num !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Константа str, определенная в документе - ${typeof str !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Переменная bool, определенная в документе - ${typeof bool !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Переменная empty, определенная в документе - ${typeof empty !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Переменная notDefined, определенная в документе - ${typeof notDefined !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
//     output.innerHTML += `<p>Константа obj, определенная в документе - ${typeof obj !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
// }

function mainFunction() {
    let localNum = 100;
    const localStr = "Локальная строка";


    otherFunction();
}

function otherFunction() {
    const output = document.getElementById('output');

    output.innerHTML += `<p>Переменная localNum, определенная в mainFunction - ${typeof localNum !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
    output.innerHTML += `<p>Константа localStr, определенная в mainFunction - ${typeof localStr !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
    output.innerHTML += `<p>Переменная num, определенная в документе - ${typeof num !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
    output.innerHTML += `<p>Константа str, определенная в документе - ${typeof str !== 'undefined' ? "Доступна" : "Не доступна"}</p>`;
}

function typeConversionExamples() {
    let number = "5";

    const output = document.getElementById('output');

    output.innerHTML += `<p>Строка "5" + 5 = ${number + 5}</p>`;
    output.innerHTML += `<p>Строка "5" превращается в число: +number = ${+number}</p>`;

    let a = 5;
    output.innerHTML += `<p>a++ = ${a++}</p>`;
    output.innerHTML += `<p>++a = ${++a}</p>`;
    
    //let b = 5;
    //output.innerHTML += `<p>b++ = ${b++}, после: b = ${b}</p>`;
}

function userInteraction() {
    alert("Это сообщение через alert!");
    let confirmation;
    let name;

    do {
        name = prompt("напиши что-то");
        confirmation = confirm("точно??");
    } while (confirmation != true);

    const output = document.getElementById('output');

    output.innerHTML += `<p>То что написал пользователь: ${name}</p>`;
    output.innerHTML += `<p>Пользователь уверен: ${confirmation ? "Да" : "Нет"}</p>`;
}

function loopsAndSwitchExample() {
    const output = document.getElementById('output');

    output.innerHTML += `<p>Цикл for:</p>`;
    for (let i = 1; i <= 5; i++) {
        output.innerHTML += `<p>Итерация ${i}</p>`;
    }

    let arg = prompt("Введите число...");
    switch (arg) {
        case '0': case '1':
            alert('Один или ноль');
            break;

        case '2':
            alert('Два');
            break;

        case '52':
            alert('Да здраствует Санкт-Питербург!');
            break;

        default:
            alert('ладно');
    }
}

typeConversionExamples();
// checkAvailability();
mainFunction();
userInteraction();
loopsAndSwitchExample();

let funcExpression = function() {
    alert("А это Function Expression!");
}
funcExpression();
