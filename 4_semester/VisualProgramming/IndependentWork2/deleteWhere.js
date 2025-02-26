function deleteWhere(objs, field, value) {
    let new_objs = [];
    for (const obj of objs) {
        if (!(field in obj)) {
            throw new Error(`Объект не содержит поле ${field}`);
        } else if (obj[field] !== value) {
            new_objs.push(obj);
        }
    }
    return new_objs;
}

module.exports = deleteWhere;
