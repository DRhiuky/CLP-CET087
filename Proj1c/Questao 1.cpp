// nome: Luiz Augusto Bello Marques dos Anjos
// matricula: 202010242
// saidas no final do codigo

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
     fct    f;
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
 
    code[0].f = INT; code[0].l = 0; code[0].a = 6; // armazena 6 espacos
    code[1].f = LIT; code[1].l = 0; code[1].a = 4; // coloca 4 no topo da pilha
    code[2].f = STO; code[2].l = 0; code[2].a = 3; // guarda o 4 do topo no espaco 3 da pilha
    code[3].f = LIT; code[3].l = 0; code[3].a = 3; // coloca 3 no topo da pilha
    code[4].f = STO; code[4].l = 0; code[4].a = 4; // guarda o 3 do topo no espqco 4 da pilha
    code[5].f = LOD; code[5].l = 0; code[5].a = 3; // carrega o valor do espaco 3 da pilha no topo
    code[6].f = STO; code[6].l = 0; code[6].a = 9; // armazena o valor do topo da pilha no espaco 9 (fora dos espacos reservados) que e igual a topo+3
    code[7].f = LOD; code[7].l = 0; code[7].a = 4; // carrega o valor do espaco 4 da pilha no topo
    code[8].f = STO; code[8].l = 0; code[8].a = 10; // armazena o valor do topo da pilha no espaco 10 (fora dos espacos reservados) que e igual a topo+3+1
    code[9].f = CAL; code[9].l = 0; code[9].a = 11; // Faz chamada de novo bloco com endereco de retorno 11
    code[10].f = OPR; code[10].l = 0; code[10].a = 0; // operacao de retorno
    code[11].f = INT; code[11].l = 0; code[11].a = 6; // reserva mais 6 espacos para o novo bloco no topo da pilha
    code[12].f = LOD; code[12].l = 0; code[12].a = 3; // o valor armazenado no endereco 9 na linha 6 e carregado ao novo topo da pilha
    code[13].f = LOD; code[13].l = 0; code[13].a = 4; // o valor armazenado no endereco 10 na linha 8 e carregado ao novo topo da pilha
    code[14].f = OPR; code[14].l = 0; code[14].a = 2; // chamada da operacao de soma
    code[15].f = STO; code[15].l = 1; code[15].a = 5; // armazena o resultado da operacao no topo da pilha no espaco 5 do bloco no primeiro nivel lexico
    code[16].f = OPR; code[16].l = 0; code[16].a = 0; // operacao de retorno, encerrando a funcao
 
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
   1   0   5   LIT   0   4      s[] :    0   0   0   0   0   0   4
   2   0   6   STO   0   3      s[] :    0   0   0   4   0   0
   3   0   5   LIT   0   3      s[] :    0   0   0   4   0   0   3
   4   0   6   STO   0   4      s[] :    0   0   0   4   3   0
   5   0   5   LOD   0   3      s[] :    0   0   0   4   3   0   4
   6   0   6   STO   0   9      s[] :    0   0   0   4   3   0
   7   0   5   LOD   0   4      s[] :    0   0   0   4   3   0   3
   8   0   6   STO   0  10      s[] :    0   0   0   4   3   0
   9   0   5   CAL   0  11      s[] :    0   0   0   4   3   0
  11   6   5   INT   0   6      s[] :    0   0   0   4   3   0   0   0  10   4   3   0
  12   6  11   LOD   0   3      s[] :    0   0   0   4   3   0   0   0  10   4   3   0   4
  13   6  12   LOD   0   4      s[] :    0   0   0   4   3   0   0   0  10   4   3   0   4   3
  14   6  13   OPR   0   2      s[] :    0   0   0   4   3   0   0   0  10   4   3   0   7
  15   6  12   STO   1   5      s[] :    0   0   0   4   3   7   0   0  10   4   3   0
  16   6  11   OPR   0   0      s[] :    0   0   0   4   3   7
  10   0   5   OPR   0   0      s[] :
 === === ===   === === ===             === === === === === === === === === === === === === === ===
 p   b   t     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
 end pl/0

*/