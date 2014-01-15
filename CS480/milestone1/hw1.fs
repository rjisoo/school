\ Geoffrey Corey
." Hello world" cr

16 32 / 16 16 * 16 * 74 * + 5 10 mod + . cr
16 32 / 16 16 * 16 * 74 * + 5 10 mod + . cr
16.0e0 32.0e0 f/ 16.0e0 16.0e0 f* 16.0e0 f* 74.0e0 F* 5 10 mod s>f f+ f. cr
16 32 / 16 16 * 16 * 74 * + 5 10 mod + . cr
16 s>f 32.0e0 f+ 3.0e0 6 10 / s>f f* f- f. cr
: check < if nip else drop endif ; 2 7 5 3 check . see check cr
: check > if nip else drop endif ; 2 7 5 3 check . see check cr

: convertint s>f ; see convertint cr
: fact recursive dup 1 > IF dup 1 - fact * else drop 1 endif ; see fact cr
: fib recursive dup 2 u< if exit then 1- dup fib swap 1- fib + ; see fib cr
