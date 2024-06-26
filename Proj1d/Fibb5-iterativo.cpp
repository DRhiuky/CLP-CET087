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
 
    code[0].f = INT; code[0].l = 0; code[0].a = 6; // reserva 6 espaços na pilha
    code[1].f = LIT; code[1].l = 0; code[1].a = 5; // carrega parametro da função n = 5
    code[2].f = STO; code[2].l = 0; code[2].a = 3; // armazena n na posição 3
    code[3].f = LIT; code[3].l = 0; code[3].a = 3; // carrega 3 no topo, sendo i = 3
    code[4].f = STO; code[4].l = 0; code[4].a = 4; // armazena i na posicao 4
    code[5].f = LIT; code[5].l = 0; code[5].a = 0; // carrega 0 no topo, i = 1
    code[6].f = STO; code[6].l = 0; code[6].a = 9; // armazena na posicao 9
    code[7].f = LIT; code[7].l = 0; code[7].a = 1; // carrega 1 no topo, i = 2
    code[8].f = STO; code[8].l = 0; code[8].a = 10; // armazena na posicao 10
    
    code[9].f = CAL; code[9].l = 0; code[9].a = 19; // chama fibb(5)
    
    code[10].f = LOD; code[10].l = 0; code[10].a = 4; // carrega valor do espaco 4 no topo (i)
    code[11].f = LOD; code[11].l = 0; code[11].a = 3; // carrega valor do espaco 3 (n = 5)
    code[12].f = OPR; code[12].l = 0; code[12].a = 11; // verifica se i >= n
    code[13].f = JPC; code[13].l = 0; code[13].a = 30; // se verdadeiro, RETURN
    
    code[14].f = LOD; code[14].l = 0; code[14].a = 4; // carrega valor do espaco 4 no topo (i)
    code[15].f = LIT; code[15].l = 0; code[15].a = 1; // carrega 1 no topo
    code[16].f = OPR; code[16].l = 0; code[16].a = 2; // soma i + 1
    code[17].f = STO; code[17].l = 0; code[17].a = 4; // armazena resultado no espaco 4
    
    code[18].f = JMP; code[18].l = 0; code[18].a = 9; // pula para a chamad da funcao, fazendo loop do-while
    
    code[19].f = INT; code[19].l = 0; code[19].a = 5; // reserva 5 espacos na pilha
    code[20].f = LOD; code[20].l = 0; code[20].a = 4; // carrega valor do espaco 4 no topo da pilha
    code[21].f = STO; code[21].l = 0; code[21].a = 8; // armazena valor no espaco 8
    code[22].f = LOD; code[22].l = 0; code[22].a = 3; // carrega valor do espaco 3 no topo
    code[23].f = LOD; code[23].l = 0; code[23].a = 4; // carrega valor do espaco 4 no topo
    code[24].f = OPR; code[24].l = 0; code[24].a = 2; // operacao de soma com valores no topo
    code[25].f = STO; code[25].l = 0; code[25].a = 4; // armazena resultado em 4
    code[26].f = LOD; code[26].l = 0; code[26].a = 8; // carrega valor do espaco 8 no topo da pilha
    code[27].f = STO; code[27].l = 0; code[27].a = 3; //armazena no espaco 3
    code[28].f = LOD; code[28].l = 0; code[28].a = 4; // carrega valor do espaco 4 no topo da pilha
    code[29].f = STO; code[29].l = 1; code[29].a = 5; // armazena o resultado no espaco 5 do nivel lexical 1
    
    code[30].f = OPR; code[30].l = 0; code[30].a = 0;// RETURN // FIM-fib

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
   0   0  -1   INT   0   6      s[] :    0   0   0   0   0   0
   1   0   5   LIT   0   5      s[] :    0   0   0   0   0   0   5
   2   0   6   STO   0   3      s[] :    0   0   0   5   0   0
   3   0   5   LIT   0   3      s[] :    0   0   0   5   0   0   3
   4   0   6   STO   0   4      s[] :    0   0   0   5   3   0
   5   0   5   LIT   0   0      s[] :    0   0   0   5   3   0   0
   6   0   6   STO   0   9      s[] :    0   0   0   5   3   0
   7   0   5   LIT   0   1      s[] :    0   0   0   5   3   0   1
   8   0   6   STO   0  10      s[] :    0   0   0   5   3   0
   9   0   5   CAL   0  19      s[] :    0   0   0   5   3   0
  19   6   5   INT   0   5      s[] :    0   0   0   5   3   0   0   0  10   0   1
  20   6  10   LOD   0   4      s[] :    0   0   0   5   3   0   0   0  10   0   1   1
  21   6  11   STO   0   8      s[] :    0   0   0   5   3   0   0   0  10   0   1
  22   6  10   LOD   0   3      s[] :    0   0   0   5   3   0   0   0  10   0   1   0
  23   6  11   LOD   0   4      s[] :    0   0   0   5   3   0   0   0  10   0   1   0   1
  24   6  12   OPR   0   2      s[] :    0   0   0   5   3   0   0   0  10   0   1   1
  25   6  11   STO   0   4      s[] :    0   0   0   5   3   0   0   0  10   0   1
  26   6  10   LOD   0   8      s[] :    0   0   0   5   3   0   0   0  10   0   1   1
  27   6  11   STO   0   3      s[] :    0   0   0   5   3   0   0   0  10   1   1
  28   6  10   LOD   0   4      s[] :    0   0   0   5   3   0   0   0  10   1   1   1
  29   6  11   STO   1   5      s[] :    0   0   0   5   3   1   0   0  10   1   1
  30   6  10   OPR   0   0      s[] :    0   0   0   5   3   1
  10   0   5   LOD   0   4      s[] :    0   0   0   5   3   1   3
  11   0   6   LOD   0   3      s[] :    0   0   0   5   3   1   3   5
  12   0   7   OPR   0  11      s[] :    0   0   0   5   3   1   0
  13   0   6   JPC   0  30      s[] :    0   0   0   5   3   1
  14   0   5   LOD   0   4      s[] :    0   0   0   5   3   1   3
  15   0   6   LIT   0   1      s[] :    0   0   0   5   3   1   3   1
  16   0   7   OPR   0   2      s[] :    0   0   0   5   3   1   4
  17   0   6   STO   0   4      s[] :    0   0   0   5   4   1
  18   0   5   JMP   0   9      s[] :    0   0   0   5   4   1
   9   0   5   CAL   0  19      s[] :    0   0   0   5   4   1
  19   6   5   INT   0   5      s[] :    0   0   0   5   4   1   0   0  10   1   1
  20   6  10   LOD   0   4      s[] :    0   0   0   5   4   1   0   0  10   1   1   1
  21   6  11   STO   0   8      s[] :    0   0   0   5   4   1   0   0  10   1   1
  22   6  10   LOD   0   3      s[] :    0   0   0   5   4   1   0   0  10   1   1   1
  23   6  11   LOD   0   4      s[] :    0   0   0   5   4   1   0   0  10   1   1   1   1
  24   6  12   OPR   0   2      s[] :    0   0   0   5   4   1   0   0  10   1   1   2
  25   6  11   STO   0   4      s[] :    0   0   0   5   4   1   0   0  10   1   2
  26   6  10   LOD   0   8      s[] :    0   0   0   5   4   1   0   0  10   1   2   1
  27   6  11   STO   0   3      s[] :    0   0   0   5   4   1   0   0  10   1   2
  28   6  10   LOD   0   4      s[] :    0   0   0   5   4   1   0   0  10   1   2   2
  29   6  11   STO   1   5      s[] :    0   0   0   5   4   2   0   0  10   1   2
  30   6  10   OPR   0   0      s[] :    0   0   0   5   4   2
  10   0   5   LOD   0   4      s[] :    0   0   0   5   4   2   4
  11   0   6   LOD   0   3      s[] :    0   0   0   5   4   2   4   5
  12   0   7   OPR   0  11      s[] :    0   0   0   5   4   2   0
  13   0   6   JPC   0  30      s[] :    0   0   0   5   4   2
  14   0   5   LOD   0   4      s[] :    0   0   0   5   4   2   4
  15   0   6   LIT   0   1      s[] :    0   0   0   5   4   2   4   1
  16   0   7   OPR   0   2      s[] :    0   0   0   5   4   2   5
  17   0   6   STO   0   4      s[] :    0   0   0   5   5   2
  18   0   5   JMP   0   9      s[] :    0   0   0   5   5   2
   9   0   5   CAL   0  19      s[] :    0   0   0   5   5   2
  19   6   5   INT   0   5      s[] :    0   0   0   5   5   2   0   0  10   1   2
  20   6  10   LOD   0   4      s[] :    0   0   0   5   5   2   0   0  10   1   2   2
  21   6  11   STO   0   8      s[] :    0   0   0   5   5   2   0   0  10   1   2
  22   6  10   LOD   0   3      s[] :    0   0   0   5   5   2   0   0  10   1   2   1
  23   6  11   LOD   0   4      s[] :    0   0   0   5   5   2   0   0  10   1   2   1   2
  24   6  12   OPR   0   2      s[] :    0   0   0   5   5   2   0   0  10   1   2   3
  25   6  11   STO   0   4      s[] :    0   0   0   5   5   2   0   0  10   1   3
  26   6  10   LOD   0   8      s[] :    0   0   0   5   5   2   0   0  10   1   3   2
  27   6  11   STO   0   3      s[] :    0   0   0   5   5   2   0   0  10   2   3
  28   6  10   LOD   0   4      s[] :    0   0   0   5   5   2   0   0  10   2   3   3
  29   6  11   STO   1   5      s[] :    0   0   0   5   5   3   0   0  10   2   3
  30   6  10   OPR   0   0      s[] :    0   0   0   5   5   3
  10   0   5   LOD   0   4      s[] :    0   0   0   5   5   3   5
  11   0   6   LOD   0   3      s[] :    0   0   0   5   5   3   5   5
  12   0   7   OPR   0  11      s[] :    0   0   0   5   5   3   1
  13   0   6   JPC   0  30      s[] :    0   0   0   5   5   3
  30   0   5   OPR   0   0      s[] :
 === === ===   === === ===             === === === === === === === === === === === === === === ===
 p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
 end pl/0
Pressione qualquer tecla para continuar. . .

*/
