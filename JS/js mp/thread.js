const { workerData, parentPort } = require('worker_threads')
/* Код потока */

const isPrime = (num) => {
  if (num === 2) { return 2; }
  if (num <= 1 || num % 2 === 0) { return false; }
  for (let div = 3; div <= Math.sqrt(num); div += 2) {
    if (num % div === 0) { return false; }
  }
  return true;
}

for (let i = workerData.from; i < workerData.range + workerData.from; i++) {
  isPrime(i);
}

/* Закрываем поток */
parentPort.postMessage({ ready: true });