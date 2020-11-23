function isPrime(num) {
    if (num == 2) return true;
    if (num <= 1 || num % 2 == 0) return false;
    for (var div = 3; div <= Math.sqrt(num); div += 2) {
        if (num % div == 0) return false;
    }
    return true
}

var N = 10000000;
var start = new Date().getTime();
for (var i = 0; i < N; i++) isPrime(i);
var end = new Date().getTime();
console.log((end - start) / 1000);