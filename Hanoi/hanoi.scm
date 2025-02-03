; Plates are 1 ~ nPlate
(define nPlate 5)

(define lResult (list))

(define (GenerateResult idx from to)
    (printf 
        (string-append (number->string idx) ": " (number->string from) "->" (number->string to) "\n")
    )
)

(define (Move n from via to)
    (if (= n 1)
        (GenerateResult n from to)
        (begin
            (Move (- n 1) from to via)
            (GenerateResult n from to)
            (Move (- n 1) via from to)
        )
    )
)

(Move nPlate 1 2 3)