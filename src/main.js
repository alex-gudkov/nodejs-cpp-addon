const myAddon = require('../build/Release/my_addon.node');

console.log(myAddon.getHello());

console.log(myAddon.sum(1, 2));
