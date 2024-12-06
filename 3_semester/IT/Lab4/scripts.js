class Currency {
    constructor(name, rate) {
        this.name = name;
        this.rate = rate;
    }
}

// Класс для представления отдельной транзакции
class Transaction {
    constructor(amount, type, category, date, currency) {
        this.amount = parseFloat(amount); // Сумма транзакции
        this.type = type; // Тип транзакции (доход или расход)
        this.category = category; // Категория транзакции
        this.date = date; // Дата транзакции
        this.currency = currency; // Валюта транзакции
    }
}

// Класс для управления бюджетом
class Budget {
    constructor() {
        this.transactions = []; // Массив для хранения текущих транзакций
        this.originalTransactions = []; // Массив для хранения исходных транзакций (до фильтрации)
        this.currencyRates = {
            USD: 1,   // 1 USD = 1 USD
            EUR: 1.05, // 1 EUR = 1.05 USD
            RUB: 0.01 // 1 RUB = 1/100 USD
        };
        this.filter = {
            startDate: '',
            endDate: '',
            category: '',
            currency: '',
            amount: ''
        };
    }

    // Метод для добавления новой транзакции в массив
    addTransaction(transaction) {
        this.transactions.push(transaction);
        this.originalTransactions.push(transaction); // Сохраняем транзакцию в исходном массиве
        this.updateTotalAmount(); // Обновляем итоговую сумму после добавления транзакции
        this.renderTransactions(); // Обновляем отображение транзакций
    }

    // Метод для редактирования транзакции по индексу
    editTransaction(index, transaction) {
        this.transactions[index] = transaction;
        this.originalTransactions[index] = transaction; // Сохраняем изменения в исходном массиве
        this.updateTotalAmount(); // Обновляем итоговую сумму после изменения транзакции
        this.renderTransactions(); // Обновляем отображение транзакций
    }

    // Метод для удаления транзакции по индексу
    removeTransaction(index) {
        this.transactions.splice(index, 1);
        this.originalTransactions.splice(index, 1); // Удаляем из исходного массива
        this.updateTotalAmount(); // Обновляем итоговую сумму после удаления транзакции
        this.renderTransactions(); // Обновляем отображение транзакций
    }

    // Метод для получения всех транзакций
    getTransactions() {
        return this.transactions;
    }

    // Метод для расчета итоговой суммы
    calculateTotalAmount() {
        let totalIncome = 0; // Общий доход в USD
        let totalExpense = 0; // Общий расход в USD

        this.transactions.forEach(transaction => {
            let amountInUSD = this.convertToUSD(transaction.amount, transaction.currency);
            if (transaction.type === 'income') {
                totalIncome += amountInUSD;
            } else {
                totalExpense += amountInUSD;
            }
        });

        let totalAmountInUSD = totalIncome - totalExpense;

        return {
            USD: totalAmountInUSD,
            EUR: totalAmountInUSD * this.currencyRates.EUR,
            RUB: totalAmountInUSD * (1 / this.currencyRates.RUB)
        };
    }

    // Метод для конвертации суммы в USD
    convertToUSD(amount, currency) {
        return amount * this.currencyRates[currency];
    }

    // Метод для обновления отображаемой итоговой суммы
    updateTotalAmount() {
        let totals = this.calculateTotalAmount();
        document.getElementById('totalAmount').innerHTML =
            `USD: ${totals.USD.toFixed(2)}, EUR: ${totals.EUR.toFixed(2)}, RUB: ${totals.RUB.toFixed(2)}`;
    }

    // Метод для отображения транзакций в таблице
    renderTransactions() {
        let tbody = document.querySelector('#transactionTable tbody');
        tbody.innerHTML = ''; // Очищаем текущую таблицу

        // Отображаем все транзакции
        this.transactions.forEach((transaction, index) => {
            let row = document.createElement('tr');
            row.innerHTML = `
                <td>${transaction.amount.toFixed(2)}</td>
                <td>${transaction.type === 'income' ? 'Доход' : 'Расход'}</td>
                <td>${transaction.category}</td>
                <td>${transaction.date}</td>
                <td>${transaction.currency}</td>
                <td>
                    <button onclick='editTransaction(${index})'>Редактировать</button>
                    <button onclick='removeTransaction(${index})'>Удалить</button>
                </td>
            `;
            tbody.appendChild(row);
        });
    }

    // Метод для фильтрации транзакций
    filterTransactions() {
        let filteredTransactions = this.originalTransactions; // Начинаем с исходных транзакций

        let { startDate, endDate, category, currency, amount } = this.filter;

        if (startDate) {
            filteredTransactions = filteredTransactions.filter(transaction => transaction.date >= startDate);
        }
        if (endDate) {
            filteredTransactions = filteredTransactions.filter(transaction => transaction.date <= endDate);
        }
        if (category) {
            filteredTransactions = filteredTransactions.filter(transaction => transaction.category.includes(category));
        }
        if (currency) {
            filteredTransactions = filteredTransactions.filter(transaction => transaction.currency === currency);
        }
        if (amount) {
            filteredTransactions = filteredTransactions.filter(transaction => transaction.amount >= amount);
        }

        this.transactions = filteredTransactions;
        this.renderTransactions();
        this.updateTotalAmount(); // Обновляем итоговую сумму
    }

    // Сохранение фильтра
    setFilter(filter) {
        this.filter = { ...this.filter, ...filter };
        this.filterTransactions(); // Применяем фильтр
    }

    // Очистка фильтра
    clearFilters() {
        this.filter = {
            startDate: '',
            endDate: '',
            category: '',
            currency: '',
            amount: ''
        };
        this.transactions = [...this.originalTransactions]; // Возвращаем все транзакции, включая добавленные или отредактированные
        this.renderTransactions();
        this.updateTotalAmount(); // Обновляем итоговую сумму
    }
}

// Инициализация менеджера бюджета
let budget = new Budget();

// Функция для добавления новой транзакции
function addTransaction() {
    let amount = document.getElementById('amount').value;
    let type = document.getElementById('type').value;
    let category = document.getElementById('category').value;
    let date = document.getElementById('date').value;
    let currency = document.getElementById('currency').value;

    let transaction = new Transaction(amount, type, category, date, currency);

    budget.addTransaction(transaction);

    document.getElementById('amount').value = '';
    document.getElementById('category').value = '';
    document.getElementById('date').value = '';
}

// Функция для редактирования транзакции
function editTransaction(index) {
    let transaction = budget.getTransactions()[index];

    // Вставляем текущие данные в форму редактирования
    document.getElementById('amount').value = transaction.amount;
    document.getElementById('category').value = transaction.category;
    document.getElementById('date').value = transaction.date;
    document.getElementById('currency').value = transaction.currency;

    // Обновляем действие кнопки, чтобы редактировать существующую транзакцию
    document.querySelector('button[type="button"]').setAttribute('onclick', `saveEdit(${index})`);
}

// Функция для сохранения отредактированной транзакции
function saveEdit(index) {
    let amount = document.getElementById('amount').value;
    let type = document.getElementById('type').value;
    let category = document.getElementById('category').value;
    let date = document.getElementById('date').value;
    let currency = document.getElementById('currency').value;

    let editedTransaction = new Transaction(amount, type, category, date, currency);

    budget.editTransaction(index, editedTransaction);

    document.getElementById('amount').value = '';
    document.getElementById('category').value = '';
    document.getElementById('date').value = '';

    // Восстанавливаем исходный onclick для добавления новой транзакции
    document.querySelector('button[type="button"]').setAttribute('onclick', 'addTransaction()');
}

// Функция для удаления транзакции
function removeTransaction(index) {
    budget.removeTransaction(index);
}

// Функция для фильтрации транзакций
function filterTransactions() {
    let startDate = document.getElementById('startDate').value;
    let endDate = document.getElementById('endDate').value;
    let category = document.getElementById('categoryFilter').value;
    let currency = document.getElementById('currencyFilter').value;
    let amount = document.getElementById('amountFilter').value;

    // Сохраняем фильтры в менеджере
    budget.setFilter({
        startDate,
        endDate,
        category,
        currency,
        amount
    });
}

// Функция для сброса фильтров
function clearFilters() {
    document.getElementById('startDate').value = '';
    document.getElementById('endDate').value = '';
    document.getElementById('categoryFilter').value = '';
    document.getElementById('currencyFilter').value = '';
    document.getElementById('amountFilter').value = '';

    budget.clearFilters();
}

document.addEventListener('DOMContentLoaded', () => {
    // Окно транзакций
    let transactionModal = document.getElementById('transactionModal');
    let modalTitle = document.getElementById('modalTitle');
    let saveTransactionButton = document.getElementById('saveTransactionButton');
    let cancelTransactionButton = document.getElementById('cancelTransactionButton');
    let modalAmount = document.getElementById('modalAmount');
    let modalCategory = document.getElementById('modalCategory');
    let modalDate = document.getElementById('modalDate');
    let modalCurrency = document.getElementById('modalCurrency');

    let incomeTable = document.getElementById('incomeTable');
    let expensesTable = document.getElementById('expensesTable');

    let balanceChartCtx = document.getElementById('balanceChart').getContext('2d');

    let transactionType = 'income'; // Тип текущей транзакции (доход по умолчанию)
    let incomes = [];
    let expenses = [];

    // Инициализация линейного графика
    let balanceChart = new Chart(balanceChartCtx, {
        type: 'line',
        data: {
            labels: [], // Даты транзакций
            datasets: [
                {
                    label: 'Баланс',
                    data: [], // Данные для баланса
                    borderColor: '#2196f3', // Цвет линии
                    backgroundColor: 'rgba(33, 150, 243, 0.2)', // Цвет заливки (отключен)
                    pointBackgroundColor: '#2196f3', // Цвет маркеров
                    pointBorderColor: '#2196f3', // Обводка маркеров
                    pointRadius: 5, // Радиус маркеров
                    pointHoverRadius: 7, // Радиус маркеров при наведении
                    fill: false, // Убираем заливку под графиком
                    tension: 0.4 // Сглаживание линии
                }
            ]
        },
        options: {
            responsive: true,
            plugins: {
                legend: { position: 'top' }, // Легенда сверху
            },
            scales: {
                x: {
                    title: {
                        display: true,
                        text: 'Дата', // Название оси X
                    },
                    ticks: {
                        autoSkip: true, // Пропуск лишних меток, если их слишком много
                        maxRotation: 45, // Максимальный угол поворота меток
                        minRotation: 0, // Минимальный угол поворота меток
                    },
                },
                y: {
                    title: {
                        display: true,
                        text: 'Сумма', // Название оси Y
                    },
                    beginAtZero: true, // Начало оси с нуля
                    ticks: {
                        precision: 0, // Отображение чисел без дробных значений
                    }
                }
            },
        }
    });

    // Открытие модального окна для доходов
    document.getElementById('addIncomeButton').addEventListener('click', () => {
        transactionType = 'income';
        modalTitle.textContent = 'Добавить доход';
        transactionModal.showModal();
    });

    // Открытие модального окна для расходов
    document.getElementById('addExpenseButton').addEventListener('click', () => {
        transactionType = 'expense';
        modalTitle.textContent = 'Добавить расход';
        transactionModal.showModal();
    });

    // Закрытие модального окна
    cancelTransactionButton.addEventListener('click', () => {
        transactionModal.close();
        clearModalFields();
    });

    // Фильтровка
    document.getElementById('filterButton').addEventListener('click', () => {
        updateChart(incomes, expenses, balanceChart);
    });

    document.getElementById('filterButtonIncomes').addEventListener('click', () => {
        incomeTable.innerHTML = '';
        let beginFilter = document.getElementById('beginFilterIncomes').value;
        let endFilter = document.getElementById('endFilterIncomes').value;
        let typeIncomes = document.getElementById('typeIncomes').value;
        incomes.forEach((inc, i) => {
            if ((!typeIncomes || typeIncomes === inc.category) && (!beginFilter || (new Date(date)) >= (new Date(beginFilter))) && (!endFilter || (new Date(date)) <= (new Date(endFilter))))
                addTransactionToTable(incomeTable, inc, 'income');
        });
    });

    document.getElementById('filterButtonExpenses').addEventListener('click', () => {
        expensesTable.innerHTML = '';
        let beginFilter = document.getElementById('beginFilterExpenses').value;
        let endFilter = document.getElementById('endFilterExpenses').value;
        let typyExpenses = document.getElementById('typyExpenses').value;
        expenses.forEach((ex, i) => {
            if ((!typyExpenses || typyExpenses === inc.category) && (!beginFilter || (new Date(date)) >= (new Date(beginFilter))) && (!endFilter || (new Date(date)) <= (new Date(endFilter))))
                addTransactionToTable(incomeTable, ex, 'expense');
        });
    });

    // Сохранение транзакции
    saveTransactionButton.addEventListener('click', () => {
        let amount = parseFloat(modalAmount.value) * budget.currencyRates[modalCurrency.value];
        let category = modalCategory.value;
        let date = modalDate.value;

        if (!amount || !category || !date) {
            alert('Пожалуйста, заполните все поля.');
            return;
        }

        let transaction = { amount, category, date };

        if (transactionType === 'income') {
            incomes.push(transaction);
            addTransactionToTable(incomeTable, transaction, 'income');
        } else {
            expenses.push(transaction);
            addTransactionToTable(expensesTable, transaction, 'expense');
        }

        updateChart(incomes, expenses, balanceChart);
        transactionModal.close();
        clearModalFields();
    });

    // Удаление транзакции
    window.deleteTransaction = (button, type) => {
        let row = button.closest('tr');
        let table = type === 'income' ? incomes : expenses;
        let index = Array.from(row.parentNode.children).indexOf(row);

        table.splice(index, 1);
        row.remove();
        updateChart(incomes, expenses, balanceChart);
    };

    window.updateTransaction = (button, type) => {
        let value = prompt("Введите новую сумму");
        let category = prompt("Введите новую категорию");
        let date = prompt("Введите новую дату (YYYY-MM-DD)");

        let row = button.closest('tr');
        let table = type === 'income' ? incomes : expenses;
        let index = Array.from(row.parentNode.children).indexOf(row);

        table[index].amount = value;
        table[index].category = category;
        table[index].date = date;
        row.innerHTML = `
            <td>${category}</td>
            <td>${value}</td>
            <td>${date}</td>
            <td>
                <button class='btn btn-danger btn-sm' onclick='deleteTransaction(this, "${type}")'>Удалить</button>
                <button class='btn btn-warning btn-sm' onclick='updateTransaction(this, "${type}")'>Редактировать</button>
            </td>`;
        updateChart(incomes, expenses, balanceChart);
    };

    // Окно валют
    let settingsModal = document.getElementById('settingsModal');
    let modalSettingsTitle = document.getElementById('modalSettingsTitle');
    let modalSettingsCurrency = document.getElementById('modalSettingsCurrency');
    let currencyName = document.getElementById('currencyName');
    let cancelSettingsButton = document.getElementById('cancelSettingsButton');
    let saveSettingsButton = document.getElementById('saveSettingsButton');

    document.getElementById('addCurrencyButton').addEventListener('click', () => {
        modalSettingsTitle.textContent = 'Добавить валюту';
        updateSettingsCurrencies();
        settingsModal.showModal();
    });

    document.getElementById('removeCurrencyButton').addEventListener('click', () => {
        modalSettingsTitle.textContent = 'Удалить валюту';
        settingsModal.showModal();
    });
});

// Функция для добавления строки в таблицу
function addTransactionToTable(table, transaction, type) {
    let row = table.insertRow();
    row.innerHTML = `
            <td>${transaction.category}</td>
            <td>${transaction.amount}</td>
            <td>${transaction.date}</td>
            <td>
                <button class='btn btn-danger btn-sm' onclick='deleteTransaction(this, "${type}")'>Удалить</button>
                <button class='btn btn-warning btn-sm' onclick='updateTransaction(this, "${type}")'>Редактировать</button>
            </td>`;
}

// Очистка полей модального окна
function clearModalFields() {
    modalAmount.value = '';
    modalCategory.value = '';
    modalDate.value = '';
}

// Обновление данных на графике
function updateChart(incomes, expenses, balanceChart) {
    let beginFilter = document.getElementById('beginFilter').value;
    let endFilter = document.getElementById('endFilter').value;
    let typeIncomeBalance = document.getElementById('typeIncomeBalance').value;
    let typyExpenseBalance = document.getElementById('typyExpenseBalance').value;

    // Сортируем транзакции по дате
    let allTransactions = [...incomes, ...expenses].sort((a, b) => new Date(a.date) - new Date(b.date));

    // Уникальные даты для графика
    let labels = [];
    (new Set(allTransactions.map(t => t.date))).forEach(date => {
        if ((!beginFilter || (new Date(date)) >= (new Date(beginFilter))) && (!endFilter || (new Date(date)) <= (new Date(endFilter)))) {
            labels.push(date);
        }
    });

    // Инициализируем массивы для доходов, расходов и баланса
    let balanceData = [];

    let cumulativeBalance = 0; // Начальный баланс (кумулятивная сумма)

    labels.forEach(date => {
        // Сумма доходов и расходов за конкретную дату
        let dailyIncome = incomes
            .filter(t => t.date === date && (!typeIncomeBalance || t.category === typeIncomeBalance))
            .reduce((sum, t) => sum + t.amount, 0);

        let dailyExpense = expenses
            .filter(t => t.date === date && (!typyExpenseBalance || t.category === typyExpenseBalance))
            .reduce((sum, t) => sum + t.amount, 0);

        // Считаем текущий баланс как разницу доходов и расходов
        cumulativeBalance += dailyIncome - dailyExpense;
        balanceData.push(cumulativeBalance);
    });

    // Обновляем данные графика
    balanceChart.data.labels = labels;
    balanceChart.data.datasets[0].data = balanceData; // Баланс

    balanceChart.update();
}

function updateSettingsCurrencies() {
    let modalSettingsCurrency = document.getElementById('modalSettingsCurrency');

    budget.currencyRates.forEach((c, i) => {
        modalSettingsCurrency.innerHTML += `<option value="${c}">${c}</option>`;
    });
}
