const deleteWhere = require("./deleteWhere.js");

test("TEST 1 deleteWhere function", () => {
    let origin_objs = [
        {
            "id": 0,
            "name": "Jhon"
        },
        {
            "id": 1,
            "name": "Nikita"
        },
        {
            "id": 2,
            "name": "Sasha"
        },
        {
            "id": 3,
            "name": "Sasha"
        },
        {
            "id": 4,
            "name": "Anton"
        }
    ];

    let expected_objs = [
        {
            "id": 0,
            "name": "Jhon"
        },
        {
            "id": 1,
            "name": "Nikita"
        },
        {
            "id": 4,
            "name": "Anton"
        }
    ];

    expect(deleteWhere(origin_objs, "name", "Sasha")).toEqual(expected_objs);
});

test("TEST 2 deleteWhere function", () => {
    let origin_objs = [
        {
            "id": 0,
            "name": "Jhon"
        },
        {
            "id": 1,
            "name": "Nikita"
        },
        {
            "id": 2,
        },
        {
            "id": 3,
            "name": "Sasha"
        },
        {
            "id": 4,
            "name": "Anton"
        }
    ];

    expect(() => deleteWhere(origin_objs, "name", "Sasha")).toThrow("Объект не содержит поле name");
});
