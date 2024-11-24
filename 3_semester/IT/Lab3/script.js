class Currency {
    constructor(name, rate) {
        this.name = name;
        this.rate = rate;
    }
}

class Rate {
    constructor(buy, sell, date) {
        this.buy = buy;
        this.sell = sell;
        this.date = date;
    }
}

class TypeOfExpense {
    constructor(name) { this.name = name; }
}

class TypeOfIncome {
    constructor(name) { this.name = name; }
}

class Expense {
    constructor(value, type, date, currency) {
        this.value = value;
        this.type = type;
        this.date = date;
        this.currency = currency;
    }
}

class Income {
    constructor(value, type, date, currency) {
        this.value = value;
        this.type = type;
        this.date = date;
        this.currency = currency;
    }
}

class Budget {
    constructor() {
        this.currencies = [];
        this.types_of_expenses = [];
        this.types_of_incomes = [];
        this.incomes = [];
        this.expenses = [];
    }

    getRateCurrencies(currency_name) {
        for (let i = 0; i < this.currencies.length; ++i) {
            if (this.currencies.at(i).name === currency_name) {
                return this.currencies.at(i).rate;
            }
        }
        return 1;
    }

    balans(start_date, end_date) {
        let balans_in_badget = 0;
        this.incomes.forEach((income, index) => {
            let cur_date = new Date(income.date);
            if (cur_date >= start_date && cur_date <= end_date) {
                balans_in_badget += income.value / this.getRateCurrencies(income.currency);
            }
        });
        this.expenses.forEach((expense, index) => {
            let cur_date = new Date(expense.date);
            if (cur_date >= start_date && cur_date <= end_date) {
                balans_in_badget -= expense.value / this.getRateCurrencies(expense.currency);
            }
        });
        return balans_in_badget;
    }

    filter(start_date, end_date, income_type, expense_type) {
        let filter_incomes = [];
        let filter_expenses = [];

        this.incomes.forEach((income, index) => {
            let cur_date = new Date(income.date);
            if (cur_date >= start_date && cur_date <= end_date && income_type === income.type) {
                filter_incomes.push(income);
            }
        });
        this.expenses.forEach((expense, index) => {
            let cur_date = new Date(expense.date);
            if (cur_date >= start_date && cur_date <= end_date && expense_type === expense.type) {
                filter_expenses.push(expense);
            }
        });

        return { filter_incomes, filter_expenses };
    }

    getCurrencies() { return this.currencies; }
    addCurrencies(currency) { this.currencies.push(currency); }
    updateCurrencies(currency) {
        for (let i = 0; i < this.currencies.length; ++i) {
            if (this.currencies.at(i).name === currency.name) {
                this.currencies.at(i).rate = currency.rate;
                break;
            }
        }
    }
    removeCurrencies(currency) {
        for (let i = 0; i < this.currencies.length; ++i) {
            if (this.currencies.at(i).name === currency.name) {
                this.currencies.splice(i, 1);
                break;
            }
        }
    }

    getTypesOfExpenses() { return this.types_of_expenses; }
    addTypesOfExpenses(type_of_expenses) { this.types_of_expenses.push(type_of_expenses); }
    updateTypesOfExpenses(type_of_expenses_old, type_of_expenses_new) {
        for (let i = 0; i < this.types_of_expenses.length; ++i) {
            if (this.types_of_expenses.at(i).name === type_of_expenses_old.name) {
                this.types_of_expenses.at(i).name = type_of_expenses_new.name;
                break;
            }
        }
    }
    removeTypesOfExpenses(type_of_expenses) {
        for (let i = 0; i < this.types_of_expenses.length; ++i) {
            if (this.types_of_expenses.at(i).name === type_of_expenses.name) {
                this.types_of_expenses.splice(i, 1);
                break;
            }
        }
    }

    getTypesOfIncomes() { return this.types_of_incomes; }
    addTypesOfIncomes(type_of_incomes) { this.types_of_incomes.push(type_of_incomes); }
    updateTypesOfIncomes(type_of_incomes_old, type_of_incomes_new) {
        for (let i = 0; i < this.types_of_incomes.length; ++i) {
            if (this.types_of_incomes.at(i).name === type_of_incomes_old.name) {
                this.types_of_incomes.at(i).name = type_of_incomes_new.name;
                break;
            }
        }
    }
    removeTypesOfIncomes(type_of_incomes) {
        for (let i = 0; i < this.types_of_incomes.length; ++i) {
            if (this.types_of_incomes.at(i).name === type_of_incomes.name) {
                this.types_of_incomes.splice(i, 1);
                break;
            }
        }
    }

    getIncomes() { return this.incomes; }
    addIncomes(income) { this.incomes.push(income); }
    updateIncomes(income_old, income_new) {
        for (let i = 0; i < this.incomes.length; ++i) {
            if (this.incomes.at(i).value === income_old.value &&
                this.incomes.at(i).type === income_old.type &&
                this.incomes.at(i).date === income_old.date &&
                this.incomes.at(i).currency === income_old.currency) {
                this.incomes.at(i).value = income_new.value;
                this.incomes.at(i).type = income_new.type;
                this.incomes.at(i).date = income_new.date;
                this.incomes.at(i).currency = income_new.currency;
                break;
            }
        }
    }
    removeIncomes(income) {
        for (let i = 0; i < this.incomes.length; ++i) {
            if (this.incomes.at(i).value === income.value &&
                this.incomes.at(i).type === income.type &&
                this.incomes.at(i).date === income.date &&
                his.incomes.at(i).currency.name === income.currency.name) {
                this.incomes.splice(i, 1);
                break;
            }
        }
    }

    getExpenses() { return this.expenses; }
    addExpenses(expense) { this.expenses.push(expense); }
    updateExpenses(expense_old, expense_new) {
        for (let i = 0; i < this.expenses.length; ++i) {
            if (this.expenses.at(i).value === expense_old.value &&
                this.expenses.at(i).type === expense_old.type &&
                this.expenses.at(i).date === expense_old.date &&
                this.expenses.at(i).currency === expense_old.currency) {
                this.expenses.at(i).value = expense_new.value;
                this.expenses.at(i).type = expense_new.type;
                this.expenses.at(i).date = expense_new.date;
                this.expenses.at(i).currency = expense_new.currency;
                break;
            }
        }
    }
    removeExpenses(expense) {
        for (let i = 0; i < this.expenses.length; ++i) {
            if (this.expenses.at(i).value === expense.value &&
                this.expenses.at(i).type === expense.type &&
                this.expenses.at(i).date === expense.date &&
                this.incomes.at(i).currency.name === expense.currency.name) {
                this.expenses.splice(i, 1);
                break;
            }
        }
    }
}

let budget = new Budget();

// Currencies
function veiwCurrencies() {
    let list = document.getElementById('currency-list');
    list.innerHTML = '';
    let currencies = budget.getCurrencies();
    currencies.forEach((currency, index) => {
        let li = document.createElement('li');
        li.textContent = `${index}: ${currency.name} - ${currency.rate}`;
        list.appendChild(li);
    });
}
function addCurrencies() {
    let name = document.getElementById('currency-name').value;
    let rate = document.getElementById('currency-rate').value;
    let currency = new Currency(name, rate);
    budget.addCurrencies(currency);
}
function updateCurrencies() {
    let name = document.getElementById('currency-name').value;
    let rate = document.getElementById('currency-rate').value;
    let currency = new Currency(name, rate);
    budget.updateCurrencies(currency);
}
function removeCurrencies() {
    let name = document.getElementById('currency-name').value;
    let rate = document.getElementById('currency-rate').value;
    let currency = new Currency(name, rate);
    budget.removeCurrencies(currency);
}

// Types Of Expenses
function veiwTypesOfExpenses() {
    let list = document.getElementById('expense-type-list');
    list.innerHTML = '';
    let types_of_expenses = budget.getTypesOfExpenses();
    types_of_expenses.forEach((type_of_expenses, index) => {
        let li = document.createElement('li');
        li.textContent = `${index}: ${type_of_expenses.name}`;
        list.appendChild(li);
    });
}
function addTypesOfExpenses() {
    let name = document.getElementById('expense-type-name').value;
    let type_of_expenses = new TypeOfExpense(name);
    budget.addTypesOfExpenses(type_of_expenses);
}
function updateTypesOfExpenses() {
    let name = document.getElementById('expense-type-name').value;
    let type_of_expenses = new TypeOfExpense(name);
    let new_name = prompt("Введите новое название");
    let new_type_of_expenses = new TypeOfExpense(new_name);
    budget.updateTypesOfExpenses(type_of_expenses, new_type_of_expenses);
}
function removeTypesOfExpenses() {
    let name = document.getElementById('expense-type-name').value;
    let type_of_expenses = new TypeOfExpense(name);
    budget.removeTypesOfExpenses(type_of_expenses);
}

// Types Of Incomes
function veiwTypesOfIncomes() {
    let list = document.getElementById('income-type-list');
    list.innerHTML = '';
    let types_of_incomes = budget.getTypesOfIncomes();
    types_of_incomes.forEach((type_of_incomes, index) => {
        let li = document.createElement('li');
        li.textContent = `${index}: ${type_of_incomes.name}`;
        list.appendChild(li);
    });
}
function addTypesOfIncomes() {
    let name = document.getElementById('income-type-name').value;
    let type_of_incomes = new TypeOfIncome(name);
    budget.addTypesOfIncomes(type_of_incomes);
}
function updateTypesOfIncomes() {
    let name = document.getElementById('income-type-name').value;
    let type_of_incomes = new TypeOfIncome(name);
    let new_name = prompt("Введите новое название");
    let new_type_of_incomes = new TypeOfIncome(new_name);
    budget.updateTypesOfIncomes(type_of_incomes, new_type_of_incomes);
}
function removeTypesOfIncomes() {
    let name = document.getElementById('income-type-name').value;
    let type_of_incomes = new TypeOfIncome(name);
    budget.removeTypesOfIncomes(type_of_incomes);
}

// Expenses
function veiwExpenses() {
    let list = document.getElementById('expense-list');
    list.innerHTML = '';
    let expenses = budget.getExpenses();
    expenses.forEach((expense, index) => {
        let li = document.createElement('li');
        li.textContent = `${index}: ${expense.value} - ${expense.type} - ${expense.date} - ${expense.currency}`;
        list.appendChild(li);
    });
}
function addExpenses() {
    let value = document.getElementById('expense-value').value;
    let type = document.getElementById('expense-type').value;
    let date = document.getElementById('expense-date').value;
    let currency = document.getElementById('expense-currency').value;
    let expense = new Expense(value, type, date, currency);
    budget.addExpenses(expense);
}
function updateExpenses() {
    let value = document.getElementById('expense-value').value;
    let type = document.getElementById('expense-type').value;
    let date = document.getElementById('expense-date').value;
    let currency = document.getElementById('expense-currency').value;
    let expense = new Expense(value, type, date, currency);

    let new_value = prompt("Введите новое значение");
    let new_type = prompt("Введите новый тип");
    let new_date = prompt("Введите новую дату");
    let new_currency = prompt("Введите новую валюту");
    let new_expense = new Expense(new_value, new_type, new_date, new_currency);
    budget.updateExpenses(expense, new_expense);
}
function removeExpenses() {
    let value = document.getElementById('expense-value').value;
    let type = document.getElementById('expense-type').value;
    let date = document.getElementById('expense-date').value;
    let currency = document.getElementById('expense-currency').value;
    let expense = new Expense(value, type, date, currency);
    budget.removeExpenses(expense);
}

// Incomes
function veiwIncomes() {
    let list = document.getElementById('income-list');
    list.innerHTML = '';
    let incomes = budget.getIncomes();
    incomes.forEach((income, index) => {
        let li = document.createElement('li');
        li.textContent = `${index}: ${income.value} - ${income.type} - ${income.date} - ${income.currency}`;
        list.appendChild(li);
    });
}
function addIncomes() {
    let value = document.getElementById('income-value').value;
    let type = document.getElementById('income-type').value;
    let date = document.getElementById('income-date').value;
    let currency = document.getElementById('income-currency').value;
    let income = new Income(value, type, date, currency);
    budget.addIncomes(income);
}
function updateIncomes() {
    let value = document.getElementById('income-value').value;
    let type = document.getElementById('income-type').value;
    let date = document.getElementById('income-date').value;
    let currency = document.getElementById('income-currency').value;
    let income = new Income(value, type, date, currency);

    let new_value = prompt("Введите новое значение");
    let new_type = prompt("Введите новый тип");
    let new_date = prompt("Введите новую дату");
    let new_currency = prompt("Введите новую валюту");
    let new_income = new Income(new_value, new_type, new_date, new_currency);

    budget.updateIncomes(income, new_income);
}
function removeIncomes() {
    let value = document.getElementById('income-value').value;
    let type = document.getElementById('income-type').value;
    let date = document.getElementById('income-date').value;
    let currency = document.getElementById('income-currency').value;
    let income = new Income(value, type, date, currency);
    budget.removeIncomes(income);
}

// Balans
function balans() {
    let start_date = new Date(document.getElementById('balance-start-date').value);
    let end_date = new Date(document.getElementById('balance-end-date').value);
    let b = budget.balans(start_date, end_date);
    let p = document.getElementById('balance-field');
    p.innerHTML = `balance: ${b}`;
}

// Filter
function filter() {
    let start_date = new Date(document.getElementById('filter-start-date').value);
    let end_date = new Date(document.getElementById('filter-end-date').value);
    let income_type = document.getElementById('filter-income-type').value;
    let expense_type = document.getElementById('filter-expense-type').value;

    let list = budget.filter(start_date, end_date, income_type, expense_type);
    let table = document.getElementById('filter-table');

    let list_incomes = list.filter_incomes;
    let list_expenses = list.filter_expenses;

    table.innerHTML = '<tr> <th>Доходы</th> <th>Расходы</th> </tr>';

    let max_length = list_incomes.length;
    if (max_length < list_expenses.length) {
        max_length = list_expenses.length;
    }

    for (let i = 0; i < max_length; ++i) {
        let tr = document.createElement('tr');
        let income_text = '';
        if (i < list_incomes.length) {
            income_text = `${list_incomes.at(i).value} - ${list_incomes.at(i).type} - ${list_incomes.at(i).date} - ${list_incomes.at(i).currency}`;
        }
        let expense_text = '';
        if (i < list_expenses.length) {
            expense_text = `${list_expenses.at(i).value} - ${list_expenses.at(i).type} - ${list_expenses.at(i).date} - ${list_expenses.at(i).currency}`;
        }
        tr.innerHTML = `<tr> <th>${income_text}</th> <th>${expense_text}</th> </tr>`;
        table.appendChild(tr);
    }
}
