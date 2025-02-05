fizzBuzz(Num):- var(Num),writeln("Please provide a number").
fizzBuzz(Num):- 0 is (Num mod 15),writeln("Fizzbuzz").
fizzBuzz(Num):- 0 is (Num mod 3),writeln("Fizz").
fizzBuzz(Num):- 0 is (Num mod 5),writeln("Buzz").
fizzBuzz(Num):- writeln(Num).

fizzBuzzToN(1):- writeln(1).
fizzBuzzToN(Num):- N is (Num - 1),fizzBuzzToN(N),fizzBuzz(Num).
