#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <userlog.h>
#include <fml32.h>
#include <atmi.h>  
#include "biblioData.fml.h"

tpsvrinit(int argc, char *argv[]) {
    userlog ("Iniciando servidorTarea3");
    return 0;
}

/* servicio para obtener datos de calcular área de círculo */
void servCalcAreaCirculo(TPSVCINFO * rqst) {
    float fvL_radio;
    float fvL_area;
    FBFR32* fbfr = (FBFR32*)rqst->data;
   
    userlog("Servicio servCalcAreaCirculo invocado.");
   
    /* Obtener campos FML del buffer de entrada */
    if (Fget32(fbfr, RADIO, 0, (char *)&fvL_radio, 0) < 0) {
        userlog("No se leyó el radio");
        tpreturn(TPFAIL, 0, (char *) fbfr, 0L, 0);
    }
    userlog("Radio: [%f]", fvL_radio);

    /* Realizar cálculo del área de círculo */
    fvL_area = 3.1416 * fvL_radio * fvL_radio;

    /* Insertar el área calculada en el buffer FML */
    Fadd32(fbfr, AREA, (char *)&fvL_area, 0);
    userlog("Área del círculo es: [%f]", fvL_area);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}

/* Servicio para calcular posibles raíces x1 y x2 de una ecuacion de 2°*/
void servCalcEcSegGrado(TPSVCINFO * rqst) {
   float fvL_constA;
   float fvL_constB;
   float fvL_constC;
   float fvL_raizX1;
   float fvL_raizX2;
   FBFR32 * fbfr = (FBFR32*)rqst->data;

   userlog ("Servicio servCalcEcSegGrado invocado.");
   /* Obtener campos FML del buffer de entrada */
   if (Fget32(fbfr, CONSTA, 0, (char *)&fvL_constA, 0) < 0) {
      userlog("No se leyo la constante A");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   userlog("Constante A: [%f]", fvL_constA);
   if (Fget32(fbfr, CONSTB, 0, (char *)&fvL_constB, 0) < 0) {
      userlog("No se leyo la constante B");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   userlog("Constante B: [%f]", fvL_constB);
   if (Fget32(fbfr, CONSTC, 0, (char *)&fvL_constC, 0) < 0) {
      userlog("No se leyo la constante C");
      tpreturn (TPFAIL, 0, (char *) fbfr, 0L, 0);
   }
   userlog("Constante C: [%f]", fvL_constC);

   /* Calcular raíces de la ecuación de 2° */
    float discriminante = fvL_constB * fvL_constB - 4 * fvL_constA * fvL_constC;

    if (discriminante < 0) {
        userlog("La ecuación no tiene raíces reales.");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    /* Calcular las raíces */
    float raizDiscriminante = 0.5 * discriminante;

    fvL_raizX1 = (-fvL_constB + raizDiscriminante) / (2 * fvL_constA);
    fvL_raizX2 = (-fvL_constB - raizDiscriminante) / (2 * fvL_constA);

    /* Insertar las raices calculadas en el buffer  FML*/
    Fadd32(fbfr, RAIZX1, (char *)&fvL_raizX1, 0);
    Fadd32(fbfr, RAIZX2, (char *)&fvL_raizX2, 0);
    userlog("La primera raíz es [%f]\n", fvL_raizX1);
    userlog("La segunda raíz es [%f]\n", fvL_raizX2);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);

}
/* Servicio para calcular producto punto*/
void servCalcProdPunto(TPSVCINFO *rqst) {
   float fvL_ax;
   float fvL_ay;
   float fvL_bx;
   float fvL_by;
   float fvL_prodpunto;
   FBFR32 *fbfr = (FBFR32 *)rqst->data;

   userlog ("Servicio servCalcProdPunto invocado.");
  
   /* Obtener los campos FML del buffer de entrada */
   if (Fget32(fbfr, AX, 0, (char *)&fvL_ax, 0) < 0) {
      userlog("No se leyo ax");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, AY, 0, (char *)&fvL_ay, 0) < 0) {
      userlog("No se leyo ay"); 
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, BX, 0, (char *)&fvL_bx, 0) < 0) {
      userlog("No se leyo bx");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   if (Fget32(fbfr, BY, 0, (char *)&fvL_by, 0) < 0) {
      userlog("No se leyo by");
      tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
   }
   userlog("AX: [%f]", fvL_ax);
   userlog("AY: [%f]", fvL_ay);
   userlog("BX: [%f]", fvL_bx);
   userlog("BY: [%f]", fvL_by);

   /* Realizar producto punto */
   fvL_prodpunto = fvL_ax * fvL_bx + fvL_ay * fvL_by;

   // Agregar el resultado del producto punto al buffer FML
   Fadd32(fbfr, PRODPUNTO, (char *)&fvL_prodpunto, 0);
   userlog("Resultado del producto punto: [%f]", fvL_prodpunto);

   tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}
