/* Модуль для общения с потоками */
const { Worker } = require('worker_threads')

/* Настройки - количество потоков, до какого числа */
const threadsNumber = 4; // У меня лучше всего работает в 4 потока
const number = 10000000;

/* Время пошло */
console.log('Стартуем!');
const startTime = Date.now();
let threadsReady = 0;

/* Подключаем потоки */
function runService(workerData) {
  new Promise((resolve, reject) => {
    const worker = new Worker('./thread.js', { workerData });
    worker.on('message', resolve);
    worker.on('error', reject);
    worker.on('exit', (code) => {
      if (code !== 0)
        reject(new Error(`Worker stopped with exit code ${code}`));
    });
  }).then(() => {
    if (threadsReady === threadsNumber - 1) {
      end();
    } else {
      threadsReady++;
    }
  });
}

const threadRange = Math.round(number / threadsNumber);
let threadsRangeFrom = 1;

for (let i = 0; i < threadsNumber; i++) {
  threadsNumber - i === 1 
    ? runService({ number: i, range: number - (threadsRangeFrom - 1), from: threadsRangeFrom })
    : runService({ number: i, range: threadRange, from: threadsRangeFrom });
  threadsRangeFrom += threadRange;
}

function end() {
  const endTime = Date.now();
  console.log('Время: ', (endTime - startTime) / 1000);
}