const orderBy = require('./orderBy');

test('sorts array of objects by multiple properties', () => {
    const input = [
        { name: 'Alice', age: 25 },
        { name: 'Bob', age: 30 },
        { name: 'Alice', age: 20 }
    ];
    const expected = [
        { name: 'Alice', age: 20 },
        { name: 'Alice', age: 25 },
        { name: 'Bob', age: 30 }
    ];
    expect(orderBy(input, ['name', 'age'])).toEqual(expected);
});

test('throws error if first argument is not an array of objects', () => {
    expect(() => orderBy([1, 2, 3], ['name'])).toThrow('The first argument must be an array of objects');
    expect(() => orderBy([null, undefined], ['name'])).toThrow('The first argument must be an array of objects');
});

test('throws error if any object is missing a property', () => {
    const input = [
        { name: 'Alice', age: 25 },
        { name: 'Bob' } // missing age
    ];
    expect(() => orderBy(input, ['name', 'age'])).toThrow('Property "age" is missing in one or more objects');
});