#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <userlog.h>
#include <fml32.h>
#include <atmi.h>  
#include "biblioData.fml.h"

int cliAreaCirc(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2);
int cliRaicesEcSegGrado(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2);
int cliProdPunto(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2);

typedef int (*opera) (float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2);
opera selecOperacion(int ivA_oper);

int main(int argc, char **argv){
   int ivL_oper;
   float fvL_arg1;
   float fvL_arg2;
   float fvL_arg3;
   float fvL_arg4;
   float fvL_arg_resul;
   float fvL_arg_resul2;
   opera svL_obtOpera;

   if (argc < 3 || argc > 6) {
        printf("Modo de uso: clienteTarea3 OPERACION ARGUMENTOS");

        return -1;
    }
   
   ivL_oper = atoi(argv[1]);
   fvL_arg1 = (float) atof(argv[2]);
   fvL_arg2 = argc > 4 ? (float) atof(argv[3]) : 0;
   fvL_arg3 = argc > 4 ? (float) atof(argv[4]) : 0;
   fvL_arg4 = argc > 5 ? (float) atof(argv[5]) : 0;
 
   svL_obtOpera = selecOperacion(ivL_oper);
   svL_obtOpera(fvL_arg1, fvL_arg2, fvL_arg3, fvL_arg4, &fvL_arg_resul, &fvL_arg_resul2);
 
   printf("Resultado: %f, %f\n", fvL_arg_resul, fvL_arg_resul2);

   return 0;
}

opera selecOperacion(int ivA_oper) {
    opera svL_obtOpera;
    switch (ivA_oper)
    {
    case 1:
        svL_obtOpera = cliAreaCirc;
        break;
    case 2:
        svL_obtOpera = cliRaicesEcSegGrado;
        break;
    case 3:
        svL_obtOpera = cliProdPunto;
        break;
    default:
        break;
    }

    return svL_obtOpera;
}

int cliAreaCirc(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2) {
  int ivL_resLlamd;
  int lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, RADIO, (char *)&fvA_arg1, 0) < 0){
     printf ("Error insertando campo FML (RADIO)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  /* Invocamos servicio de calculo de area de circulo */
  printf("Llamada al servicio 'servCalcAreaCirculo'\n");
  if(tpcall("servCalcAreaCirculo", (char *) fbfr, 0, (char **)&fbfr, (long*)&lvL_tamLongt, 0L) == -1) {
    printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
    printf("Liberamos el buffer y desconectamos de la aplicacion\n");
    tpfree((char *)fbfr);
    tpterm(); 
    return (0); 
}
  /* Lectura de resultados */
  if(Fget32(fbfr, AREA, 0, (char *)&fvL_recValor, 0) < 0){
  userlog("No se leyo el resultado\n");
  tpreturn (TPFAIL, 0, (char*)fbfr, 0L,0) ;
  }

  *fvA_arg_resul = fvL_recValor;
  printf("Liberamos buffer y desconectamos de la aplicación\n");
  tpfree((char *)fbfr);
  tpterm();
  return 0;
}

int cliRaicesEcSegGrado(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2) {
  int ivL_resLlamd;
  int lvL_tamLongt;
  float fvL_recValorX1, fvL_recValorX2;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, CONSTA, (char *)&fvA_arg1, 0) < 0){
     printf ("Error insertando campo FML (CONSTA)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, CONSTB, (char *)&fvA_arg2, 0) < 0){
     printf ("Error insertando campo FML (CONSTB)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, CONSTC, (char *)&fvA_arg3, 0) < 0){
     printf ("Error insertando campo FML (CONST)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  /* Invocamos el servicio de calculo de area de circulo */
  printf("Llamada al servicio 'servCalcEcSegGrado'\n");
  if (tpcall("servCalcEcSegGrado", (char *)fbfr, 0, (char **)&fbfr, (long*) &lvL_tamLongt, 0L) == -1) {
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      printf("Liberamos buffer y desconectamos de la aplicacion\n");
      tpfree((char *)fbfr);
      tpterm();
      return (0);
  }
  if(Fget32(fbfr, RAIZX1, 0, (char *)&fvL_recValorX1, 0) < 0) {
  userlog("No se leyo el resultado raiz 1\n");
  tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
  }
  if(Fget32(fbfr, RAIZX2, 0, (char *)&fvL_recValorX2, 0) < 0) {
  userlog("No se leyo el resultado raiz 2\n");
  tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
  }
  
  *fvA_arg_resul = fvL_recValorX1;
  *fvA_arg_resul2 = fvL_recValorX2;
  
  tpfree((char*)fbfr);
  tpterm();
  return 0;  
}
int cliProdPunto(float fvA_arg1, float fvA_arg2, float fvA_arg3, float fvA_arg4, float *fvA_arg_resul, float *fvA_arg_resul2) {
  int ivL_resLlamd;
  long lvL_tamLongt;
  float fvL_recValor;
  FBFR32 *fbfr;

  /* Conectamos con la aplicación Tuxedo Server */
  printf("Conectamos con la aplicacion\n");
  if(tpinit((TPINIT *) NULL) == -1) {
    printf("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
    return(1);
  }
  /* Reservamos espacio para el buffer FML */
  printf ("Reservamos espacio para el buffer FML\n");
  if((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL){
     printf("Error reservando espacio para buffer FML\n");
     tpterm();
     return(1);
  }
  
  /* Manejo del buffer FML */
  printf("Insertamos datos en buffer FML\n");
  if(Fadd32 (fbfr, AX, (char *)&fvA_arg1, 0) < 0){
     printf ("Error insertando campo FML (AX)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, AY, (char *)&fvA_arg2, 0) < 0){
     printf ("Error insertando campo FML (AY)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, BX, (char *)&fvA_arg3, 0) < 0){
     printf ("Error insertando campo FML (BX)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  if(Fadd32 (fbfr, BY, (char *)&fvA_arg4, 0) < 0){
     printf ("Error insertando campo FML (BY)\n");
     printf ("Liberamos buffer y desconectamos de la aplicacion\n");
     tpfree((char *) fbfr);
     tpterm();
     return(1);   
  }
  /* Invocamos el servicio de calculo de producto punto */
  printf("Llamada al servicio 'servCalcProdPunto'\n");
  if (tpcall("servCalcProdPunto", (char *)fbfr, 0, (char **)&fbfr, (long*) &lvL_tamLongt, 0L) == -1) {
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      printf("Liberamos buffer y desconectamos de la aplicacion\n");
      tpfree((char *)fbfr);
      tpterm();
      return (0);
  }
  /* Lectura de resultados */
  if(Fget32(fbfr, PRODPUNTO, 0, (char *)&fvL_recValor, 0) < 0) {
  userlog("No se leyo el resultado\n");
  tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
  }
  
  *fvA_arg_resul = fvL_recValor; 
  
  printf ("Liberamos Buffer y desconectamos de la aplicación\n");
  tpfree((char*)fbfr);
  tpterm();
  return 0;  
}
