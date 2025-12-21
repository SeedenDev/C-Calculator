//
// Created by Seeden on 2025/05/10.
//

#include "parser.h"

// Warning about:
// -Omission of * between: 10(2+2)=10*(2+2) AND 10e20=10*e20.
// -Multiple ^ layers (not () needed, ex: 10^10^10). But if 10^10*10, it means (10^10)+10 not 10^(10+10).
// -NOT SAME with e: 10e10e10=10*e10*e10. Also 10ee10e=10*e(e(10))*e(1). () needed: 10e(10e10)=10*e(10*e(10))
// ALSO: 10e=10e(0)=10*1=1 WARNING. 10e is not e(1) !!!!!! (but that's because e is a "shortcut" while ^ is a "func")
// AND "E" can be used alone, just meaning 1*e, and REALLY ALONE juste 1*e(0)
// -Func like sqrt/cos/etc need () for more than 1 operation (or this operation is also a sub like e or ^)
// sqrt10=sqrt(10) but sqrt10+10 or sqrt10*10 != sqrt(10+10) or sqrt(10*10). () NEEDED. (but as sqrt10e2^4=sqrt(10*e(2^4)) it's ok.
// It is just "lego", reading from inside/top priority to resolve. Or also from left to right, cutting operations
// if new symbol ONLY IF NOT () because it could be to create subgroup. Only as * if after a number (omitted)
// -Also, as -x^n != (-x)^n, /!\. System should work like that: -x is not a number, but a "stg before minus the number"
// and (-x) is a negative number. If -x is first in the formula, must take it as negative number.