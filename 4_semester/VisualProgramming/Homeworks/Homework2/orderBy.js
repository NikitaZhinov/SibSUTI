function orderBy(array, properties) {
    if (!Array.isArray(array) || !array.every(item => typeof item === 'object' && item !== null)) {
        throw new Error('The first argument must be an array of objects');
    }

    for (const obj of array) {
        for (const prop of properties) {
            if (!(prop in obj)) {
                throw new Error(`Property "${prop}" is missing in one or more objects`);
            }
        }
    }

    const sortedArray = [...array];

    sortedArray.sort((a, b) => {
        for (const prop of properties) {
            if (a[prop] < b[prop]) return -1;
            if (a[prop] > b[prop]) return 1;
        }
        return 0;
    });

    return sortedArray;
}

module.exports = orderBy;