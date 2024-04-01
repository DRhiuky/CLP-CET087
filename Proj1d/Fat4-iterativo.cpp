// nome: Luiz Augusto Bello
// matricula: 202010242

// p-code.cpp :  cpp.sh
//
// C conventions
// 0 == FALSE
//
#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     enum fct    f;
     int    l; // l: 0..levmax; // Level buffer
     int    a; // a: 0..amax;   // Address buffer
}instruction;

instruction code[2048];

//procedure interpret;
// const stacksize = 500;

#define stacksize 5012

 // p, b, t: integer; {program-, base-, topstack-registers}
 int p, // program-register
     b, // base-register
     t; // topstack-register
 
instruction i;            //: instruction; {instruction register}
int         s[stacksize]; //: array [1..stacksize] of integer; {datastore}

int base(int l){ //l: integer)
 int b1; //

 b1 = b; // {find base l levels down}
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}//end-int-base

// Determina se seu argumento é impar
int odd(int x){ return (  ((x%2)==1) ); }

void pcodevhw(){ // begin 
 printf("\n start pl/0");
 printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 t = -1; // topstack-register
 b = 0;  // base-register
 p = 0;  // program-register
 
 // OBS: s[0] must not be used
 s[1] = 0; 
 s[2] = 0; 
 s[3] = 0;
 
    code[ 0].f = INT; code[ 0].l = 0; code[ 0].a = 5; // 5 espaços na pilha
    code[ 1].f = LIT; code[ 1].l = 0; code[ 1].a = 4; // parâmetro da função n = 4
    code[ 2].f = STO; code[ 2].l = 0; code[ 2].a = 3; // armazena n na posição 3
    code[ 3].f = LOD; code[ 3].l = 0; code[ 3].a = 3; // pega o valor de n na posição 3 e coloca no topo
    code[ 4].f = STO; code[ 4].l = 0; code[ 4].a = 8; // armazena em topo + 3;

    code[ 5].f = CAL; code[ 5].l = 0; code[ 5].a = 9; // chama a função fat(n)

    code[ 6].f = LOD; code[ 6].l = 0; code[ 6].a = 9; // // carrega resultado da multiplicacao da funcao
    code[ 7].f = STO; code[ 7].l = 0; code[ 7].a = 4; // armazena resultado da funcao em 4
    code[ 8].f = OPR; code[ 8].l = 0; code[ 8].a = 0; // RETURN // main-FIM

    code[ 9].f = INT; code[ 9].l = 0; code[ 9].a = 6; // funcao fat(n)
    code[ 10].f = LIT; code[ 10].l = 0; code[10].a = 1; // 1 no topo
    code[ 11].f = STO; code[ 11].l = 0; code[ 11].a = 4; // Armazena 1 na posição 4
    code[ 12].f = LIT; code[ 12].l = 0; code[ 12].a = 1; // 1 no topo
    code[ 13].f = STO; code[ 13].l = 0; code[ 13].a = 5; // Armazena 1 na posição 5
    
    code[ 14].f = LOD; code[ 14].l = 0; code[ 14].a = 4; // Carrega o valor do espaco 4
    code[ 15].f = LOD; code[ 15].l = 0; code[15].a = 5; // Carrega o valor do espaco 5
    code[ 16].f = OPR; code[ 16].l = 0; code[ 16].a = 4; // Realiza multiplicacao dos valores no topo da pilha
    code[ 17].f = STO; code[ 17].l = 0; code[ 17].a = 4; // armazena resultado da multiplicacao

    code[ 18].f = LOD; code[ 18].l = 0; code[ 18].a = 5; // carrega valor do espaco 5
    code[ 19].f = LIT; code[ 19].l = 0; code[ 19].a = 1; // 1 no topo
    code[ 20].f = OPR; code[ 20].l = 0; code[ 20].a = 2; // realiza soma dos valores no topo
    code[ 21].f = STO; code[ 21].l = 0; code[ 21].a = 5; // armazena resultado no espaco 5

    code[ 22].f = LOD; code[22].l = 0; code[ 22].a = 5; // carrega valor armazenado em 5
    code[ 23].f = LOD; code[ 23].l = 0; code[23].a = 3; // carrega valor de n armazenado em 3
    code[ 24].f = OPR; code[ 24].l = 0; code[ 24].a = 12; // compara se o valor atual e maior que n
    code[ 25].f = JPC; code[ 25].l = 0; code[ 25].a = 27; // se for maior que n, pula para 27

    code[ 26].f = JMP; code[ 26].l = 0; code[26].a = 14; // senao, pula para 14

    code[ 27].f = OPR; code[ 27].l = 0; code[ 27].a = 0; // RETURN // fat(4)-FIM
 
 do {
  i = code[p]; 
  //printf("\n %3d %3d %3d - %3d %3d %3d", p, b, t, i.f, i.l, i.a);
  printf("\n %3d %3d %3d   ", p, b, t);
  p = p + 1;
 // switch case i.f-BEGIN
  switch  (i.f) { // with i do case f of
    case LIT : { t = t + 1; s[t] = i.a; printf("LIT %3d %3d", i.l, i.a); } break;
    case OPR :
               printf("OPR %3d %3d", i.l, i.a);
//             switch case i.a-BEGIN
               switch (i.a) { // case a of {operator}
                 case  0: { // return
                            t = b - 1; 
                            p = s[t + 3]; 
                            b = s[t + 2];
                          }
                          break;
         
                 case  1: { //
                            s[t] = -s[t];
                          }
                          break;
         
                 case  2: { //  ADD     : PUSH( POP()+POP() )
                            t    = t - 1; 
                            s[t] = s[t] + s[t + 1];
                          }
                          break;
         
                 case  3: { // SUBSTRACT: PUSH( POP()-POP() )
                            t    = t - 1; 
                            s[t] = s[t] - s[t + 1];
                          }
                          break;
         
                 case  4: { // MULTIPLY: PUSH( POP()*POP() )
                            t    = t - 1; 
                            s[t] = s[t] * s[t + 1];
                          }
                          break;
         
                 case  5: { // DIVIDE  : PUSH( POP()/POP() )
                            t    = t - 1; 
                            s[t] = s[t] / s[t + 1];
                          }
                          break;
         
                 case  6: { // 
                            s[t] = odd(s[t]); //s[t] = ord(odd(s[t]));
                          }
                          break;
         
                 case  8: { // EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] == s[t + 1]);
                          }
                          break;
         
                 case  9: { // NOT.EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] != s[t + 1]);
                          }
                          break;
         
                 case 10: { // LESS THAN
                            t    = t - 1; 
                            s[t] = (s[t] < s[t + 1]);
                          }
                          break;
         
                 case 11: { // GREATER EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] >= s[t + 1]);
                          }
                          break;
         
                 case 12: { // GREATER THAN
                            t = t - 1; 
                            s[t] = (s[t] > s[t + 1]);
                          }
                          break;
         
                 case 13: { // LESS EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] <= s[t + 1]);
                          }
                          break;
               } // end;
//         switch case i.a-END
           break;

   case LOD : { // LOAD
                printf("LOD %3d %3d", i.l, i.a);
                t    = t + 1; 
                s[t] = s[base(i.l) + i.a];
              }
              break;

   case STO : { // STORE
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l)+i.a] = s[t]; 
                t            = t - 1;
              }
              break;

   case CAL :
              { // {generate new block mark}
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = base(i.l); 
                s[t + 2] = b; 
                s[t + 3] = p;
                b        = t + 1; 
                p        = i.a;
              }
              break;

   case INT : t = t + i.a;printf("INT %3d %3d", i.l, i.a); break;
   case JMP : p = i.a;    printf("JMP %3d %3d", i.l, i.a); break;
   case JPC : if (s[t] != 0) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } // end {with, case}
  // switch case i.f-END
  
  // print stack
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
 printf("\n p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}//end-void-pcmachine() {interpret};

int main(){

	// Aqui vc preenche as instrucoes no vetor code
    code[ 0].f = OPR; code[ 0].l = 0; code[ 0].a = 0;

	// Aqui vc chama a P-code machine para interpretar essas instrucoes
	pcodevhw();
	return 0;
}

/*

 start pl/0
 p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
 === === ===   === === ===             === === === === === === === === === === === === === === ===
   0   0  -1   INT   0   5      s[] :    0   0   0   0   0
   1   0   4   LIT   0   4      s[] :    0   0   0   0   0   4
   2   0   5   STO   0   3      s[] :    0   0   0   4   0
   3   0   4   LOD   0   3      s[] :    0   0   0   4   0   4
   4   0   5   STO   0   8      s[] :    0   0   0   4   0
   5   0   4   CAL   0   9      s[] :    0   0   0   4   0
   9   5   4   INT   0   6      s[] :    0   0   0   4   0   0   0   6   4   0   0
  10   5  10   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4   0   0   1
  11   5  11   STO   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   0
  12   5  10   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4   1   0   1
  13   5  11   STO   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   1
  14   5  10   LOD   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   1   1
  15   5  11   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   1   1   1
  16   5  12   OPR   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   1   1
  17   5  11   STO   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   1
  18   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   1   1
  19   5  11   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4   1   1   1   1
  20   5  12   OPR   0   2      s[] :    0   0   0   4   0   0   0   6   4   1   1   2
  21   5  11   STO   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   2
  22   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   2   2
  23   5  11   LOD   0   3      s[] :    0   0   0   4   0   0   0   6   4   1   2   2   4
  24   5  12   OPR   0  12      s[] :    0   0   0   4   0   0   0   6   4   1   2   0
  25   5  11   JPC   0  27      s[] :    0   0   0   4   0   0   0   6   4   1   2
  26   5  10   JMP   0  14      s[] :    0   0   0   4   0   0   0   6   4   1   2
  14   5  10   LOD   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   2   1
  15   5  11   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   1   2   1   2
  16   5  12   OPR   0   4      s[] :    0   0   0   4   0   0   0   6   4   1   2   2
  17   5  11   STO   0   4      s[] :    0   0   0   4   0   0   0   6   4   2   2
  18   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   2   2   2
  19   5  11   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4   2   2   2   1
  20   5  12   OPR   0   2      s[] :    0   0   0   4   0   0   0   6   4   2   2   3
  21   5  11   STO   0   5      s[] :    0   0   0   4   0   0   0   6   4   2   3
  22   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   2   3   3
  23   5  11   LOD   0   3      s[] :    0   0   0   4   0   0   0   6   4   2   3   3   4
  24   5  12   OPR   0  12      s[] :    0   0   0   4   0   0   0   6   4   2   3   0
  25   5  11   JPC   0  27      s[] :    0   0   0   4   0   0   0   6   4   2   3
  26   5  10   JMP   0  14      s[] :    0   0   0   4   0   0   0   6   4   2   3
  14   5  10   LOD   0   4      s[] :    0   0   0   4   0   0   0   6   4   2   3   2
  15   5  11   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   2   3   2   3
  16   5  12   OPR   0   4      s[] :    0   0   0   4   0   0   0   6   4   2   3   6
  17   5  11   STO   0   4      s[] :    0   0   0   4   0   0   0   6   4   6   3
  18   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   6   3   3
  19   5  11   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4   6   3   3   1
  20   5  12   OPR   0   2      s[] :    0   0   0   4   0   0   0   6   4   6   3   4
  21   5  11   STO   0   5      s[] :    0   0   0   4   0   0   0   6   4   6   4
  22   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   6   4   4
  23   5  11   LOD   0   3      s[] :    0   0   0   4   0   0   0   6   4   6   4   4   4
  24   5  12   OPR   0  12      s[] :    0   0   0   4   0   0   0   6   4   6   4   0
  25   5  11   JPC   0  27      s[] :    0   0   0   4   0   0   0   6   4   6   4
  26   5  10   JMP   0  14      s[] :    0   0   0   4   0   0   0   6   4   6   4
  14   5  10   LOD   0   4      s[] :    0   0   0   4   0   0   0   6   4   6   4   6
  15   5  11   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4   6   4   6   4
  16   5  12   OPR   0   4      s[] :    0   0   0   4   0   0   0   6   4   6   4  24
  17   5  11   STO   0   4      s[] :    0   0   0   4   0   0   0   6   4  24   4
  18   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4  24   4   4
  19   5  11   LIT   0   1      s[] :    0   0   0   4   0   0   0   6   4  24   4   4   1
  20   5  12   OPR   0   2      s[] :    0   0   0   4   0   0   0   6   4  24   4   5
  21   5  11   STO   0   5      s[] :    0   0   0   4   0   0   0   6   4  24   5
  22   5  10   LOD   0   5      s[] :    0   0   0   4   0   0   0   6   4  24   5   5
  23   5  11   LOD   0   3      s[] :    0   0   0   4   0   0   0   6   4  24   5   5   4
  24   5  12   OPR   0  12      s[] :    0   0   0   4   0   0   0   6   4  24   5   1
  25   5  11   JPC   0  27      s[] :    0   0   0   4   0   0   0   6   4  24   5
  27   5  10   OPR   0   0      s[] :    0   0   0   4   0
   6   0   4   LOD   0   9      s[] :    0   0   0   4   0  24
   7   0   5   STO   0   4      s[] :    0   0   0   4  24
   8   0   4   OPR   0   0      s[] :
 === === ===   === === ===             === === === === === === === === === === === === === === ===
 p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
 end pl/0
Pressione qualquer tecla para continuar. . .

*/