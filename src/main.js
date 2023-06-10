const myAddon = require('../build/my-addon.node');

console.log(myAddon.getHello());

console.log(myAddon.sum(1, 2));

myAddon.runCallback((value) => {
  console.log(value);
});
