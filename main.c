//
// Created by Seeden on 2025/05/09.
//

#include <stdio.h>

#include "string_helper.h"
#include "token.h"
#include "token_list.h"
#include "tokenizer.h"
#include "parser.h"
#include "solver.h"

int main(void) {

    // Addition, substraction, multiplication, division, () priority w/multiple layers
    // omission of * symbol before (), ^power symbol (priority applies)

    // TO ADD: e=x10^ symbol w/ priority with it and multiple layers,
    // decimal number (double), multiple ^ layers, sqrt, diff between (-n)^x & -n^x
    // Perhaps: cos/sin/tan/acos/asin/atan/global value like pi

    // ln(e)=1 and exp(x)=e^x. ln() is "logarithme népérien" (log[e](x)), log is log[10] and the last common one is
    // log[2]. But hey, let's just add log[n] (idk how to handle it in formula)
    // WELL some problem here: lne=ln(e) but.. in tokenizer how split them if just going for "reading chars until new symbol" uh........
    // E=just a scientific way to write "*10^n"     /     e=CONSTANT (nombre d'Euler).
    // How to deal with it? => SINGLE RESPONSABILITY. Thus, tokenizer should only pass token to the "parser".
    // The "parser" will handle the creation of the tree. It will split the "E" in subbranches: ["n" (*) ["10" (^) "x"]]
    // Same shit for %, let's divide the thing before % and % by adding a sub-branch ["the operation" / "100"]


#ifdef TEST_LIST
    Token t1 = numberToken("90");
    Token t2 = symbolToken(PLUS);
    Token t3 = symbolToken(EXP);
    Token t4 = numberToken("9");
    Token t5 = symbolToken(MULTIPLY);
    Token t6 = numberToken("70");
    TokenList list = initlist();
    listadd(&list, &t1);
    const size_t index2 = listadd(&list, &t2);
    listadd(&list, &t3);
    printf("Here?");
    listadd(&list, &t4);
    printf("Contains t2? %hhd\n", listcontains(&list, &t2));
    Token removedToken = listremove(&list, index2);
    printf("Who has been deleted? %i\n", removedToken.type);
    printf("And now? %hhd\n", listcontains(&list, &t2));
    listadd(&list, &t5);
    listadd(&list, &t6);
    listadd(&list, &t2);
    printlist(&list);
    const Token* getT3 = listget(&list, 3);
    const char * text = mapping[getT3->type-1];
    char * data = getT3->value.data;
    printf("Got Token 3 : %s-%s\n", text, data);
    clearlist(&list);
    printlist(&list);
#else
    //const string formula = strd("9+(4*exp4+3*2e-1)/4-1((4^2.5+5)*(8-7)-logb10)+(-3)*(log(-1))");
    const string formula = initstrd("9+(4+3*2-1)/4-1((4^2+5)*(8-7)-10)+(-3)*(-1)");
    //const string formula = initrd("9+(exp4+3*2e)(2.5*8-logb10)-logexplne");

    /*printf("%p\n", formula);
    printf("%p\n", &formula);
    printf("%p\n", &formula[0]);
    printf("%s\n", formula);
    printf("%s\n", formula+1);
    printf("%c\n", *formula);
    printf("%c\n", *formula+1);
    printf("%c\n----\n", *(formula+1));*/

    TokenList tokensList = initlist();
    printf("ICI%p\n", &tokensList);
    tokenize(&formula, &tokensList);
    if (tokensList.size==0) {
        printf("An error occured: tokenizer failed.");
        return EXIT_FAILURE;
    }
    printlist(&tokensList);

    destroystr(&formula);
    destroylist(&tokensList);
#endif
    return EXIT_SUCCESS;
}
