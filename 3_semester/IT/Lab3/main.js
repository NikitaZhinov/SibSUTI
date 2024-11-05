class Currency {
    constructor(name, rate) {
        this.name = name;
        this.rate = rate;
    }

    setRate(rate) { this.rate = rate; }

    getName() { return this.name; }

    getRate() { return this.rate; }
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
    constructor(value, type, date) {
        this.value = value;
        this.type = type;
        this.date = date;
    }
}

class Income {
    constructor(value, type, date) {
        this.value = value;
        this.type = type;
        this.date = date;
    }
}

class Budget {
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