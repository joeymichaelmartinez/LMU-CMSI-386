// This is homework 2 written by John Hardy and Jordan Sanders, linter = pylama

const rp = require('request-promise');
const crypto = require('crypto');

function change(amount) {
  if (amount < 0) {
    throw new RangeError('amount cannot be negative');
  }
  const result = [];
  let remaining = amount;
  [25, 10, 5, 1].forEach((coin) => {
    result.push(Math.floor(remaining / coin));
    remaining %= coin;
  });
  return result;
}

function stripQuotes(arg) {
  let newString = arg;
  newString = newString.replace(/"/g, '');
  newString = newString.replace(/\\/g, '');
  newString = newString.replace(/'/g, '');
  return newString;
}

function scramble(arg) {
  if (arg === '') {
    return '';
  }
  const randomElement = Math.floor(Math.random() * arg.length);
  let string = arg.slice(0, randomElement) + arg.slice(randomElement + 1, arg.length);
  string = arg.charAt(randomElement) + scramble(string);
  return string;
}

function powers(base, limit, callback) {
  let current = 1;
  for (let exp = 1; current <= limit; exp += 1) {
    callback(current);
    current = base ** exp;
  }
}

function* powersGenerator(base, limit) { // eslint-disable-line func-names
  for (let x = 1; x <= limit; x *= base) {
    yield x;
  }
}

function say(str) {
  let result = '';
  function recurse(str2) {
    if (str2 === undefined) {
      result = result.substring(0, result.length - 1);
      return result;
    }
    result += `${str2} `;
    return recurse;
  }
  return recurse(str);
}

function interleave(...args) {
  const firstArray = args.shift();
  const secondArray = args;
  if (firstArray.length === 0) {
    return secondArray;
  } else if (secondArray.length === 0) {
    return firstArray;
  }
  let result = [];
  let current = 0;
  function hasNext(val, arr) {
    return val + 1 < arr.length;
  }
  do {
    result.push(firstArray.shift());
    result.push(secondArray.shift());
    current += 1;
  } while (hasNext(current, firstArray) && hasNext(current, secondArray));
  result = result.concat(firstArray);
  result = result.concat(secondArray);
  return result;
}

function cylinder(obj) {
  let { radius = 1, height = 1 } = obj;

  const surfaceArea = () =>
    ((2 * (Math.PI) * radius * height) + (2 * (Math.PI) * (radius * radius)));

  const volume = () => ((Math.PI) * (radius * radius) * height);

  const widen = (factor) => {
    radius *= factor;
  };
  const stretch = (factor) => {
    height *= factor;
  };
  const toString = () => `Cylinder with radius ${radius} and height ${height}`;

  return Object.freeze({
    get radius() {
      return radius;
    },
    get height() {
      return height;
    },
    surfaceArea,
    volume,
    widen,
    stretch,
    toString,
  });
}

function makeCryptoFunctions(key, alg) {
  function encrypt(val) {
    const cipher = crypto.createCipher(alg, key);
    let result = cipher.update(val, 'utf8', 'hex');
    result += cipher.final('hex');
    return result;
  }

  function decrypt(val) {
    const cipher = crypto.createDecipher(alg, key);
    let result = cipher.update(val, 'hex', 'utf8');
    result += cipher.final('utf8');
    return result;
  }

  return [encrypt, decrypt];
}

function randomName(obj) {
  const { gender, region } = obj;
  const options = {
    uri: 'http://uinames.com/api/',
    qs: {
      gender,
      region,
      amount: 1,
    },
    json: true,
  };
  return rp(options).then(person => `${person.surname}, ${person.name}`);
}

module.exports = {
  change,
  stripQuotes,
  scramble,
  powers,
  powersGenerator,
  say,
  interleave,
  cylinder,
  makeCryptoFunctions,
  randomName,
};
