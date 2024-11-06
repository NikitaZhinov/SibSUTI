class Currency {
    constructor(name, rate) {
        this.name = name;
        this.rate = rate;
    }
}

function addCurency() {

}

class Rate {
    constructor() {
        this.buy = 0;
        this.sell = 0;
        this.date = "";
    }

    constructor(buy, sell, date) {
        this.buy = buy;
        this.sell = sell;
        this.date = date;
    }
}

class TypeOfExpense {
    constructor() { this.name = ""; }

    constructor(name) { this.name = name; }
}

class TypeOfIncome {
    constructor() { this.name = ""; }

    constructor(name) { this.name = name; }
}

class Expense {
    constructor() {
        this.value = 0;
        this.type = "";
        this.date = "";
    }

    constructor(value, type, date) {
        this.value = value;
        this.type = type;
        this.date = date;
    }
}

class Income {
    constructor() {
        this.value = 0;
        this.type = "";
        this.date = "";
    }

    constructor(value, type, date) {
        this.value = value;
        this.type = type;
        this.date = date;
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

    constructor(currencies, types_of_expenses, types_of_incomes, incomes, expenses) {
        this.currencies = currencies;
        this.types_of_expenses = types_of_expenses;
        this.types_of_incomes = types_of_incomes;
        this.incomes = incomes;
        this.expenses = expenses;
    }

    balans() {

    }

    filter() {

    }
}